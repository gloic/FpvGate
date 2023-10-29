#pragma once

#include "../services/web/GateWebController.h"

#include <EspBase.h>
#include "Secrets.h"

#include <HTTPClient.h>
#include "ESPAsyncWebServer.h"

class Gate : public EspBase {
public:
    Gate() {instance = this;}
    void setup() override;
    void loop() override;

protected:
    WiFiClient wifiClient;
    HTTPClient http;
    
    void setupWebController();
    void setupGPIO();
    void doRegister(String ip);
    boolean checkPass();
    boolean notifyPass();
    void led(boolean state);
    void blinkLed();
    void startListening();
    void stopListening();

    static void beep();

    boolean isListening();
private:
    static Gate *instance;
    GateWebController webController;

    boolean listening = false;
    String _id;

    void setupWifi();
    static void onStart(AsyncWebServerRequest *request);
    static void onStop(AsyncWebServerRequest *request);
    static void onLed(AsyncWebServerRequest *request);
};