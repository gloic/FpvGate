#include "Starter.h"

void Starter::setup() {
    setupWifi();
    setupWebController();
    doRegister();
    server.begin();
}

void Starter::setupWifi() {
    Log.infoln("Setting wifi as AP");
    WiFi.mode(WIFI_AP);
    WiFi.softAP(SECRET_SSID, SECRET_PASS);
    Log.infoln("Wifi AP created. IP=%s", WiFi.softAPIP());
}

void Starter::setupWebController() {
    Gate::setupWebController();
    server.on("/api/test", HTTP_POST, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "I'm starter !");
    });   
}

void Starter::doRegister() {
    service.registerGate(WiFi.softAPIP().toString());
}

void Starter::doNotifyPassage() {
    service.notifyPassage();
}