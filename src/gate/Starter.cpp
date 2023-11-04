#include "Starter.h"
#include <server/services/GateManager.h>
#include <server/FpvGateServer.h>

void Starter::setupWifi() {
    Log.infoln("Setting wifi as AP");
    WiFi.mode(WIFI_AP);
    WiFi.softAP(SECRET_SSID, SECRET_PASS);
    Log.infoln("Wifi AP created. IP=%s", WiFi.softAPIP());
}

void Starter::setupWebController(AsyncWebServer &webServer) {
    webServer.on("/api/test", HTTP_POST, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "I'm starter !");
    });   
}

int Starter::doRegister() {
    return GateManager::getInstance().setStarter(WiFi.softAPIP().toString());
}

void Starter::doNotifyPassage() {
    FpvGateServer::getInstance().gatePassage(id);
}

void Starter::setupModules() {
    Gate::setupModules();
}

void Starter::setupButton() {
    Log.infoln("Starter::setupButton");
    buttonReset = new OneButton(PIN_STARTER, false);
    buttonReset->attachClick(&Starter::onButtonResetPress);
    buttonReset->attachDoubleClick(&Starter::onButtonResetDoublePress);
    buttonReset->attachLongPressStart(&Starter::onButtonResetLongPress);
}

void Starter::onButtonResetPress() {
    Log.infoln("reset button pressed (single)");
    FpvGateServer::getInstance().reset();
}

void Starter::onButtonResetDoublePress() {
    Log.infoln("reset button pressed (double)");
    FpvGateServer::getInstance().setTrackMode();
}

void Starter::onButtonResetLongPress() {
    Log.infoln("reset button pressed (long)");
    FpvGateServer::getInstance().setCalibrationMode();
}