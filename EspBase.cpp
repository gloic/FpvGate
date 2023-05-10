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

void EspBase::setupAPWifi(String ssid, String pwd) {
	Serial.println("Setting wifi as AP");
	WiFi.mode(WIFI_AP);
	#if defined(ESP8266)
	  WiFi.softAP(ssid, pwd);
	#elif defined(ESP32)
	  WiFi.softAP(ssid.c_str(), pwd.c_str());
	#endif
	
	Serial.print("AP IP address: ");
	Serial.println(WiFi.softAPIP());
}

void EspBase::setupWifi(String ssid, String pwd) {
	Serial.println("Setting wifi");
	#if defined(ESP8266)
		WiFi.begin(ssid, pwd);
	#elif defined(ESP32)
		WiFi.mode(WIFI_STA);
		WiFi.begin(ssid.c_str(), pwd.c_str());
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
  webServer.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", "I'am alive");
  });

  webServer.on("/restart", HTTP_GET, onRestart);
  webServer.on("/version", HTTP_GET, onVersion);
}

void EspBase::onVersion(AsyncWebServerRequest * request) {
	request->send(200, "text/plain", this->getVersion());
}

void EspBase:onRestart(AsyncWebServerRequest * request) {
	ESP.restart();
}

void EspBase::startWebServer() {
  AsyncElegantOTA.begin(&webServer);
  webServer.begin();
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

AsyncWebServer EspBase::server() {
  return webServer;
}
