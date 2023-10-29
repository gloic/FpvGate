#include "Gate.h"
#include "../modules/SonicSensor.h"
#include "../modules/GateBuzzer.h"
#include "../config/GateConfig.h"
#include "../structs/GateMode.h"

#include "OneButton.h"

SonicSensor sonicSensor = SonicSensor(PIN_SONIC_SENSOR_TRIGGER, PIN_SONIC_SENSOR_ECHO, PIN_SONIC_SENSOR_POT_RANGE, PIN_SONIC_SENSOR_LED);
GateBuzzer buzzer = GateBuzzer(PIN_BUZZER);

Gate *Gate::instance = nullptr;

String ipStarter;

void Gate::setup() {
    this->setupWifi();
    this->setupWebController();
    this->setupGPIO();

    EspBase::startWebServer();
    this->stopListening();
}

void Gate::setupWifi() {
    EspBase::setupWifi(SECRET_SSID, SECRET_PASS);
    this->doRegister(WiFi.gatewayIP().toString());
}

void Gate::setupWebController() {
    EspBase::setupWebController();
    Serial.println("Gate::setupWebController");
    this->server().on("/api/gate/start", HTTP_POST, &Gate::onStart);
    this->server().on("/api/gate/stop", HTTP_POST, &Gate::onStop);
}

void Gate::setupGPIO() {
    Serial.println("SonicGate setup GPIO");
    sonicSensor.setup();
    buzzer.setup();
}

void Gate::doRegister(String ip) {
    Serial.println("Registering gate to Starter");
    this->webController.setIpStarter(ip.c_str());
    this->_id = this->webController.registerOnStarter();
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
    Serial.println("Start listening");
    this->listening = true;
}

void Gate::stopListening() {
    Serial.println("Stop listening");
    this->listening = false;
    sonicSensor.stop();
}

void Gate::onStop(AsyncWebServerRequest *request) {
    instance->stopListening();
    request->send(200, "text/plain", "stopped");
}

void Gate::onLed(AsyncWebServerRequest *request) {
   Serial.println("LED");
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
}

boolean Gate::checkPass() {
    return sonicSensor.checkPass();
}

boolean Gate::notifyPass() {
    Serial.println("Notify pass to Starter");
    // TODO : Add informations (height)
    return this->webController.notifyPass(this->_id);

}

void Gate::beep() {
    buzzer.beep();
}