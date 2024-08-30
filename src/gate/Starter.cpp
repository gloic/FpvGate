#include "Starter.h"
#include <server/managers/GateManager.h>
#include <server/FpvGateServer.h>

void Starter::setupWifi() {
    wifiUtils.createAccessPoint(SECRET_SSID, SECRET_PASS);
}

void Starter::setupWebController(AsyncWebServer &webServer) {
    Log.infoln("Setup Web Controller for Starter");
    webServer.on("/api/test", HTTP_POST, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "I'm starter !");
    });   
}

int Starter::doRegister() {
    return GateManager::getInstance().setStarter(*this, WiFi.softAPIP().toString());
}

void Starter::doNotifyPassage() {
    FpvGateServer::getInstance().onGatePassage(id);
}