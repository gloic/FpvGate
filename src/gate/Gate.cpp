#include "Gate.h"
#include <config/GateEndPoints.h>

Gate* Gate::instance = nullptr;

void Gate::loop() {
    if(!isListening) {
        return;
    }
    
    if(this->checkPass()) {
        Log.infoln("Passage detected");
        this->stopListen();
        this->doNotifyPassage();
    }
}

boolean Gate::checkPass() {
    return sonicSensor.checkPass();
}

int Gate::doRegister() {
    return webUtils.post(getIpStarter(), REGISTER).toInt();
}

void Gate::doNotifyPassage() {
    webUtils.post(getIpStarter(), PASSED).toInt();
}

void Gate::setupWifi() {
    Log.infoln("Setup Wifi for Gate");
    WiFi.begin(SECRET_SSID, SECRET_PASS);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
  
    Log.infoln("Wifi connected");
    Log.infoln("IP= %s", WiFi.localIP().toString());
    Log.infoln("Gateway=%s", WiFi.gatewayIP().toString());
}

void Gate::setupWebController(AsyncWebServer &webServer) {
    Log.infoln("Setup Web Controller for Gate");
    webServer.on(LISTEN_START, HTTP_POST, &Gate::onStartListen);
    webServer.on(LISTEN_STOP, HTTP_POST, &Gate::onStopListen);
}

void Gate::setupModules() {
    Log.infoln("Gate::setupModules");
    sonicSensor.setup();
    buzzer.setup();
    led.setup();
}

String Gate::getIpStarter() {
    if (DEV_MODE) {
        return DEV_IP_STARTER;
    } else {
        return WiFi.gatewayIP().toString();
    }
}

void Gate::onStartListen(AsyncWebServerRequest *request) {
    instance->startListen();
    request->send(200, "text/plain", "OK");
}

void Gate::onStopListen(AsyncWebServerRequest *request) {
    instance->stopListen();
    request->send(200, "text/plain", "OK");
}

void Gate::startListen() {
    Log.infoln("Start listen");
    if(!isListening) {
        Log.infoln("isListening = true");
        isListening = true;
        led.on();
    } else {
        Log.warningln("Already listening");
    }
}

void Gate::stopListen() {
    Log.infoln("Stop listen");
    if(isListening) {
        isListening = false;
        sonicSensor.stop();
        led.off();
        buzzer.beep();
    } else {
        Log.warningln("Already stopped listening");
    }
}