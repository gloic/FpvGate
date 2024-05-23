#include "Starter.h"
#include <server/managers/GateManager.h>
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
    buttonNext->tick();
    buttonOk->tick();

    if (this->checkPass()) {
        Log.infoln("Starter : passage detected");
        buzzer.beep();
        // this->doNotifyPassage();
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

void Starter::setupButtons() {
    Log.infoln("Starter::setupButtons");
    buttonReset = new OneButton(PIN_STARTER);
    buttonReset->attachClick(&Starter::onButtonResetClick);
    buttonReset->attachDoubleClick(&Starter::onButtonResetDoubleClick);
    buttonReset->attachLongPressStart(&Starter::onButtonResetLongClick);

    buttonNext = new OneButton(PIN_MENU_UP);
    buttonOk = new OneButton(PIN_MENU_OK);

    buttonNext->attachClick(&Starter::onButtonNextClick);
    buttonOk->attachClick(&Starter::onButtonOkClick);
}

void Starter::onButtonResetClick() {
    Log.infoln("reset mode");
    FpvGateServer::getInstance().reset();
}

void Starter::onButtonResetDoubleClick() {
    Log.infoln("set track mode");
    FpvGateServer::getInstance().setTrackMode();
}

void Starter::onButtonResetLongClick() {
    Log.infoln("set calibration mode");
    FpvGateServer::getInstance().setCalibrationMode();
}

void Starter::onButtonNextClick() {
    Log.infoln("onButtonNextClick");
    FpvGateServer::getInstance().selectNextMode();
}

void Starter::onButtonOkClick() {
    Log.infoln("onButtonOkClick");
    FpvGateServer::getInstance().confirmMode();
}