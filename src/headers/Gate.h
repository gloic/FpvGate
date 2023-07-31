#ifndef Gate_H
#define Gate_H

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
    void notifyPass();
    void led(bool state);
    void blinkLed();
    static void beep();

    static bool isListening() { return instance->listening; };
    static void startListening() { instance->listening = true; };
    static void stopListening() { instance->listening = false; };

private:
    static Gate *instance;
    bool listening;

    void setupWifi();
    static void onStart(AsyncWebServerRequest *request);
    static void onStop(AsyncWebServerRequest *request);
    static void onLed(AsyncWebServerRequest *request);
};
#endif