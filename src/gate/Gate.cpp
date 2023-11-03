#include "Gate.h"

Gate* Gate::instance = nullptr;

void Gate::setup() {
    setupWifi();
    setupWebController();
    doRegister();
    server.begin();
}

void Gate::setupWifi() {
    WiFi.begin(SECRET_SSID, SECRET_PASS);
    Log.infoln("Wifi connected");
    Log.infoln("IP= %s", WiFi.localIP().toString());
    Log.infoln("Gateway=%s", WiFi.gatewayIP().toString());
}

void Gate::setupWebController() {
    server.on("/api/gate/start", HTTP_POST, &Gate::onStartListen);
    server.on("/api/gate/stop", HTTP_POST, &Gate::onStopListen);
}

void Gate::setupModules() {
    Log.infoln("Gate::setupModules");
    sonicSensor.setup();
}

void Gate::setupService() {
    service.setIpStarter(WiFi.gatewayIP().toString());
}

void Gate::doRegister() {
    service.registerGate();
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
    isListening = true;
}

void Gate::stopListen() {
    Log.infoln("Stop listen");
    isListening = false;
    sonicSensor.stop();
}

void Gate::loop() {
    if(!isListening) {
        return;
    }

    if(sonicSensor.checkPass()) {
        Log.infoln("Passage detected");
        doNotifyPassage();
    }
}

void Gate::doNotifyPassage() {
    service.notifyPassage();
}