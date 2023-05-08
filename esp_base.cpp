#include "esp_base.h"
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

void EspBase::Init(String ssid, String pwd) {
  _ssid = ssid;
  _pwd = pwd;
}

void EspBase::SetupBase() {
  Serial.begin(115200);

  SetupWifi();
  SetupWebController();
}

void EspBase::SetupWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(_ssid.c_str(), _pwd.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
   
  Serial.print("WiFi connected : ");
  Serial.println(WiFi.localIP());
}

void EspBase::SetupWebController() {  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", "I'am alive");
  });

  server.on("/restart", HTTP_GET, [](AsyncWebServerRequest * request) {
      ESP.restart();
  });
}

void EspBase::StartWebServer() {
  AsyncElegantOTA.begin(&server);
  server.begin();
  Serial.println("Device ready!");
}

String EspBase::GetVersion() {
  return "EspBase v." + _version;
}

String EspBase::GetParamFromRequest(String paramName, AsyncWebServerRequest * request) {
  if (request->hasParam(paramName)) {
    return request->getParam(paramName)->value();
  }
  return "";
}
