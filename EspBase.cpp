#include "EspBase.h"

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#elif defined(ESP32)
  #include <WiFi.h>
  #include <AsyncTCP.h>
#endif

#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

void EspBase::init(String ssid, String pwd) {
  _ssid = ssid;
  _pwd = pwd;
}

void EspBase::setupBase() {
  Serial.begin(115200);
}

void EspBase::setupAPWifi() {
	Serial.println("Setting wifi as AP");
	WiFi.mode(WIFI_AP);
	#if defined(ESP8266)
	  WiFi.softAP(_ssid, _pwd);
	#elif defined(ESP32)
	  WiFi.softAP(_ssid.c_str(), _pwd.c_str());
	#endif
	
	Serial.print("AP IP address: ");
	Serial.println(WiFi.softAPIP());
}
void EspBase::setupWifi() {
	Serial.println("Setting wifi");
	#if defined(ESP8266)
		WiFi.begin(_ssid, _pwd);
	#elif defined(ESP32)
		WiFi.mode(WIFI_STA);
		WiFi.begin(_ssid.c_str(), _pwd.c_str());
	#endif

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
   
  Serial.print("WiFi connected : ");
  Serial.println(WiFi.localIP());
  
  Serial.println("Gateway IP address: ");
  Serial.println(WiFi.gatewayIP());
}

void EspBase::setupWebController() {  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", "I'am alive");
  });

  server.on("/restart", HTTP_GET, [](AsyncWebServerRequest * request) {
      ESP.restart();
  });
}

void EspBase::startWebServer() {
  AsyncElegantOTA.begin(&server);
  server.begin();
  Serial.println("Device ready!");
}

String EspBase::getVersion() {
  return "EspBase v." + _version;
}

String EspBase::getParamFromRequest(String paramName, AsyncWebServerRequest * request) {
  if (request->hasParam(paramName)) {
    return request->getParam(paramName)->value();
  }
  return "";
}
