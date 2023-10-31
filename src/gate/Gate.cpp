#include "Gate.h"

#include "../structs/GateMode.h"

#include "OneButton.h"
#include <ArduinoLog.h>

String ipStarter;
Gate* Gate::instance = nullptr;

void Gate::setup() {
    this->setupWifi();
    this->setupWebController();
    this->setupGPIO();

    EspBase::startWebServer();
    this->stopListening();
}

void Gate::setupWifi() {
    EspBase::setupWifi(SECRET_SSID, SECRET_PASS);
    this->doRegister();
}

void Gate::setupWebController() {
    EspBase::setupWebController();
    Log.infoln("Gate::setupWebController");
    this->server().on("/api/gate/start", HTTP_POST, &Gate::onStart);
    this->server().on("/api/gate/stop", HTTP_POST, &Gate::onStop);
}

void Gate::setupGPIO() {
    Log.infoln("Gate setup GPIO");
    this->sonicSensor.setup();
    this->leds.setup();
    buzzer.setup();
}

void Gate::doRegister() {
    Log.infoln("Registering gate to Starter");
    this->_id = this->webController.registerOnStarter(this->getStarterIP());
}

void Gate::onStart(AsyncWebServerRequest *request) {
    instance->startListening();
    // TODO - Add calibration mode
    request->send(200, "text/plain", "started");
}

boolean Gate::isListening() {
    return this->listening;
}

void Gate::startListening() {
    Log.infoln("Start listening");
    this->listening = true;
    this->leds.on();
}

void Gate::stopListening() {
    Log.infoln("Stop listening");
    this->listening = false;
    
    this->sonicSensor.stop();
    this->leds.off();
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
    if (!this->listening) {
        return;
    }

    if (this->checkPass()) {
        // TODO : refactor in a private method
        if(this->notifyPass()) {
            this->stopListening();
        }
    }
    this->leds.loop();
}

boolean Gate::checkPass() {
    return this->sonicSensor.checkPass();
}

boolean Gate::notifyPass() {
    Log.infoln("Notify pass to Starter");
    // TODO : Add informations (height ?)
    return this->webController.notifyPass(this->getStarterIP());
}

void Gate::beep() {
    this->buzzer.beep();
}

String Gate::getStarterIP() {
    return WiFi.gatewayIP().toString(); 
}