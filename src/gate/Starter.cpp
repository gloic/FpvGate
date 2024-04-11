#include "Starter.h"
#include <server/services/GateManager.h>
#include <server/FpvGateServer.h>

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

    if(!this->isListening) {
        return;
    }

    if (this->checkPass()) {
        Log.infoln("passage detected on starter");
        this->doNotifyPassage();
    }
}

int Starter::doRegister() {
    return GateManager::getInstance().setStarter(*this, WiFi.softAPIP().toString());
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
    Log.infoln("reset mode");
    FpvGateServer::getInstance().reset();
}

void Starter::onButtonResetDoublePress() {
    Log.infoln("set track mode");
    FpvGateServer::getInstance().setTrackMode();
}

void Starter::onButtonResetLongPress() {
    Log.infoln("set calibration mode");
    FpvGateServer::getInstance().setCalibrationMode();
}