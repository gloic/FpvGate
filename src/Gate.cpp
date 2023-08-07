#include "headers/Gate.h"
#include "headers/modules/StateLed.h"
#include "headers/modules/SonicSensor.h"
#include "headers/modules/GateBuzzer.h"
#include "headers/GateConfig.h"
#include "services/headers/RestWebController.h"
#include "headers/structs/GateMode.h"

const String ENDPOINT_REGISTER = "/api/gate/register";

SonicSensor sonicSensor = SonicSensor(PIN_SONIC_SENSOR_TRIGGER, PIN_SONIC_SENSOR_ECHO);
GateBuzzer buzzer = GateBuzzer(PIN_BUZZER);
StateLed stateLed;

OneButton buttonTest(PIN_BUTTON_TEST, true);

Gate *Gate::instance = nullptr;

String ipStarter;
String id;

auto webController = new RestWebController();

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
    this->server().on("/api/gate/led", HTTP_POST, &Gate::onLed);
}

void Gate::setupGPIO() {
    sonicSensor.setup();
    buzzer.setup();
    stateLed.setup();

    buttonReset.attachClick(instance->onButtonTestPress());
    buttonTest.attachLongPressStart(instance->onButtonTestPress());
}

void Gate::doRegister(String ip) {
    Serial.println("Registering gate to Starter");
    char url[100];
    snprintf(url, sizeof(url), "http://%s/api/gate/register", ip.c_str());
    http.begin(wifiClient, url);
    int httpCode = http.POST("");
    if (httpCode == HTTP_CODE_OK) {
        String responseBody = http.getString();
        id = responseBody.toInt();
        ipStarter = ip;
        Serial.print("id received = ");
        Serial.println(id);
    }
    http.end();
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
   // TODO
   Serial.println("LED");
   request->send(200, "text/plain", "led");
}

void Gate::loop() {
    if (this->isListening()) {
        if (this->checkPass()) {
            this->stopListening();
            this->notifyPass();
        }
    }
   stateLed.loop();

   buttonTest.tick();
}

boolean Gate::checkPass() {
    return sonicSensor.checkPass();
}

void Gate::notifyPass() {
    Serial.println("Notify pass to Starter");
    char url[100];
    snprintf(url, sizeof(url), "http://%s/api/gate/passed", ipStarter.c_str());
    
    http.begin(wifiClient, url);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String payload = "id=" + id;
    http.POST(payload);
    http.end();
}

void Gate::beep() {
    buzzer.beep();
}


void Gate::onButtonTestPress() {
    // 
}

void Gate::onButtonTestLongPress() {

}