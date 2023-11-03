#pragma once

#include "../services/web/GateWebController.h"
#include "../config/GateConfig.h"

#include "../modules/SonicSensor.h"
#include "../modules/GateBuzzer.h"
#include "../modules/Leds.h"

#include <EspBase.h>
#include "../Secrets.h"

#include <HTTPClient.h>
#include "ESPAsyncWebServer.h"

class Gate : public EspBase {
public:
    Gate(): sonicSensor(PIN_SONIC_SENSOR_TRIGGER, PIN_SONIC_SENSOR_ECHO, PIN_SONIC_SENSOR_POT_RANGE, PIN_SONIC_SENSOR_LED), buzzer(PIN_BUZZER) {
        Gate::instance = this;
    }
    void setup() override;
    void loop() override;

protected:
    WiFiClient wifiClient;
    HTTPClient http;
    Leds leds;
    
    void setupWebController();
    void setupGPIO();
    void doRegister();
    boolean checkPass();
    boolean notifyPass();
    void led(boolean state);
    void blinkLed();
    void startListening();
    void stopListening();
    void beep();

    boolean isListening();
private:
    static Gate * instance;
    GateWebController webController;
    SonicSensor sonicSensor;
    GateBuzzer buzzer;

    boolean listening = false;
    String id;

    void setupWifi();
    String getStarterIP();

    static void onStart(AsyncWebServerRequest *request);
    static void onStop(AsyncWebServerRequest *request);
    static void onLed(AsyncWebServerRequest *request);
};