#include "Starter.h"

#include <server/services/GateManager.h>

void Starter::setup(AsyncWebServer &webServer) {
    setupWifi();
    setupWebController(webServer);
    doRegister();
}

void Starter::setupWifi() {
    if (DEV_MODE == 1) {
        Log.infoln("Connecting to existing network");
        WiFi.mode(WIFI_STA);
        WiFi.begin(SECRET_SSID, SECRET_PASS);   
    } else {
        Log.infoln("Setting wifi as AP");
        WiFi.mode(WIFI_AP);
        WiFi.softAP(SECRET_SSID, SECRET_PASS);
    }

    Log.infoln("Wifi AP created. IP=%s", WiFi.softAPIP());
}

void Starter::setupWebController(AsyncWebServer &webServer) {
    webServer.on("/api/test", HTTP_POST, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "I'm starter !");
    });   
}

void Starter::doRegister() {
    GateManager::getInstance().setStarter(WiFi.softAPIP().toString());
}

void Starter::doNotifyPassage() {
    // TODO
}

void Starter::setupModules() {
    Gate::setupModules();

}