#include "headers/Gate.h"
#include "headers/modules/SonicSensor.h"
#include "headers/modules/GateBuzzer.h"
#include "headers/GateConfig.h"
#include "headers/structs/GateMode.h"

#include "OneButton.h"

const String ENDPOINT_REGISTER = "/api/gate/register";

SonicSensor sonicSensor = SonicSensor(PIN_SONIC_SENSOR_TRIGGER, PIN_SONIC_SENSOR_ECHO, PIN_SONIC_SENSOR_POT_RANGE, PIN_SONIC_SENSOR_LED);
GateBuzzer buzzer = GateBuzzer(PIN_BUZZER);

OneButton buttonTest(PIN_BUTTON_TEST, true);

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
    // Notify Starter
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
    // this->server().on("/api/gate/led", HTTP_POST, &Gate::onLed);
}

void Gate::setupGPIO() {
    sonicSensor.setup();
    buzzer.setup();
    this->_stateLed.setup();

    buttonTest.attachClick(&Gate::onButtonTestPress);
    buttonTest.attachLongPressStart(&Gate::onButtonTestPress);
}

void Gate::doRegister(String ip) {
    Serial.println("Registering gate to Starter");
    this->webController.registerOnStarter(ip.c_str());
}

void Gate::onStart(AsyncWebServerRequest *request) {
    instance->startListening();
//    instance->stateLed.setMode(2);
    request->send(200, "text/plain", "started");
}

void Gate::onStop(AsyncWebServerRequest *request) {
    instance->stopListening();
//    instance->stateLed.setMode(1);
    request->send(200, "text/plain", "stopped");
}

void Gate::onLed(AsyncWebServerRequest *request) {
   Serial.println("LED");
   int state = instance->getParamFromRequest("state", request).toInt();
//    instance->_stateLed.setMode();
//    instance->stateLed.setColor();

   request->send(200, "text/plain", "led");
}

void Gate::loop() {
    if (this->isListening()) {
        if (this->checkPass()) {
            this->stopListening();
            this->notifyPass();
        }
    }
   this->_stateLed.loop();

   buttonTest.tick();
}

boolean Gate::checkPass() {
    return sonicSensor.checkPass();
}

void Gate::notifyPass() {
    Serial.println("Notify pass to Starter");
    this->webController.notifyPass(ipStarter.c_str(), _id);
}

void Gate::beep() {
    buzzer.beep();
}


void Gate::onButtonTestPress() {
    // 
}

void Gate::onButtonTestLongPress() {

}