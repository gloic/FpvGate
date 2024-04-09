#include "Starter.h"
#include <server/services/GateManager.h>
#include <server/FpvGateServer.h>

Starter* Starter::instance = nullptr;

Starter& Starter::getInstance() {
    if (!instance) {
        instance = new Starter();
    }
    return *instance;
}

void Starter::setupWifi() {
    Log.infoln("Setup Wifi for Starter");
    if (DEV_MODE) {
        Log.infoln("Setting wifi started (dev mode)");
        WiFi.mode(WIFI_STA);
        WiFi.begin(SECRET_SSID, SECRET_PASS);

        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }

        Log.infoln("Wifi connected");
        Log.infoln("IP= %s", WiFi.localIP().toString());
        Log.infoln("Gateway=%s", WiFi.gatewayIP().toString());
    } else {
        Log.infoln("Setting wifi as AP");
        WiFi.mode(WIFI_AP);
        WiFi.softAP(SECRET_SSID, SECRET_PASS);
        Log.infoln("Wifi AP created. IP=%s", WiFi.softAPIP().toString());
    }
}

void Starter::setupWebController(AsyncWebServer &webServer) {
    Log.infoln("Setup Web Controller for Starter");
    webServer.on("/api/test", HTTP_POST, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "I'm starter !");
    });   
}

void Starter::loop() {
    buttonReset->tick();

    if(!isListening) {
        return;
    }

    if (this->checkPass()) {
        this->doNotifyPassage();
    }
}

int Starter::doRegister() {
    // TODO - pass instance
    return GateManager::getInstance().setStarter(this->getInstance(), WiFi.softAPIP().toString());
}

void Starter::doNotifyPassage() {
    FpvGateServer::getInstance().onGatePassage(id);
}

void Starter::setupModules() {
    Gate::setupModules();
}

void Starter::setupButton() {
    Log.infoln("Starter::setupButton");
    buttonReset = new OneButton(PIN_STARTER);
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