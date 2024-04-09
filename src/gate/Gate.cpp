#include "Gate.h"

Gate* Gate::instance = nullptr;

void Gate::loop() {
    if(!isListening) {
        return;
    }

    if(this->checkPass()) {
        Log.infoln("Passage detected");
        doNotifyPassage();
    }
}

boolean Gate::checkPass() {
    return sonicSensor.checkPass();
}

int Gate::doRegister() {
    return webUtils.post(getIpStarter(), "/api/gate/register").toInt();
}

void Gate::doNotifyPassage() {
    webUtils.post(getIpStarter(), "/api/gate/passed").toInt();
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
    webServer.on("/api/gate/start", HTTP_POST, &Gate::onStartListen);
    webServer.on("/api/gate/stop", HTTP_POST, &Gate::onStopListen);
}

void Gate::setupModules() {
    Log.infoln("Gate::setupModules");
    sonicSensor.setup();
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
        isListening = true;
    } else {
        Log.warningln("Already listening");
    }
}

void Gate::stopListen() {
    Log.infoln("Stop listen");
    if(isListening) {
        isListening = false;
        sonicSensor.stop();
    } else {
        Log.warningln("Already stopped listening");
    }
}