#include "Gate.h"

#include "../structs/GateMode.h"

#include "OneButton.h"
#include <ArduinoLog.h>

String ipStarter;
Gate* Gate::instance = nullptr;

void Gate::setup() {
    setupWifi();
    setupWebController();
    setupGPIO();

    EspBase::startWebServer();
    stopListening();
}

void Gate::setupWifi() {
    EspBase::setupWifi(SECRET_SSID, SECRET_PASS);
    doRegister();
}

void Gate::setupWebController() {
    EspBase::setupWebController();
    Log.infoln("Gate::setupWebController");
    server().on("/api/gate/start", HTTP_POST, &Gate::onStart);
    server().on("/api/gate/stop", HTTP_POST, &Gate::onStop);
}

void Gate::setupGPIO() {
    Log.infoln("Gate setup GPIO");
    sonicSensor.setup();
    leds.setup();
    buzzer.setup();
}

void Gate::doRegister() {
    Log.infoln("Registering gate to Starter");
    id = webController.registerOnStarter(getStarterIP());
}

void Gate::onStart(AsyncWebServerRequest *request) {
    instance->startListening();
    // TODO - Add calibration mode
    request->send(200, "text/plain", "started");
}

boolean Gate::isListening() {
    return listening;
}

void Gate::startListening() {
    Log.infoln("Start listening");
    listening = true;
    leds.on();
}

void Gate::stopListening() {
    Log.infoln("Stop listening");
    listening = false;
    
    sonicSensor.stop();
    leds.off();
}

void Gate::onStop(AsyncWebServerRequest *request) {
    instance->stopListening();
    request->send(200, "text/plain", "stopped");
}

void Gate::onLed(AsyncWebServerRequest *request) {
   Log.infoln("LED");
   int state = instance->getParamFromRequest("state", request).toInt();
   request->send(200, "text/plain", "led");
}

void Gate::loop() {
    if (!listening) {
        return;
    }

    if (checkPass()) {
        // TODO : refactor in a private method
        if(notifyPass()) {
            stopListening();
        }
    }
    leds.loop();
}

boolean Gate::checkPass() {
    return sonicSensor.checkPass();
}

boolean Gate::notifyPass() {
    Log.infoln("Notify pass to Starter");
    // TODO : Add informations (height ?)
    return webController.notifyPass(getStarterIP());
}

void Gate::beep() {
    buzzer.beep();
}

String Gate::getStarterIP() {
    return WiFi.gatewayIP().toString(); 
}