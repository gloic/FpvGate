#include "headers/Gate.h"
#include "headers/modules/SonicSensor.h"
#include "headers/modules/GateBuzzer.h"
#include "headers/GateConfig.h"
#include "headers/structs/GateMode.h"

#include "OneButton.h"

const String ENDPOINT_REGISTER = "/api/gate/register";

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
    if (DEV_MODE == 1) {
        this->doRegister(WiFi.gatewayIP().toString());
    } else {
        this->doRegister(DEV_IP_STARTER);
    }
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
    request->send(200, "text/plain", "started");
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
    if (this->isListening()) {
        if (this->checkPass()) {
            this->stopListening();
            this->notifyPass();
        }
    }
}

boolean Gate::checkPass() {
    return sonicSensor.checkPass();
}

void Gate::notifyPass() {
    Serial.println("Notify pass to Starter");
    this->webController.notifyPass(this->_id);
}

void Gate::beep() {
    buzzer.beep();
}