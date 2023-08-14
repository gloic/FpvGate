#ifndef Gate_H
#define Gate_H

// #include "headers/modules/StateLed.h"
#include "headers/modules/GateWebController.h"

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
    // void setCalibrationMode(bool state);
    // void enableSensorCalibration();
    // void disableSensorCalibration();

    static void beep();

    static bool isListening() { return instance->_listening; };
    static void startListening() { Serial.println("Start listening"); instance->_listening = true; };
    static void stopListening() { Serial.println("Stop listening"); instance->_listening = false; };

private:
    static Gate *instance;
    // StateLed _stateLed {};
    GateWebController webController;

    bool _listening = false;
    String _id;

    void setupWifi();
    static void onStart(AsyncWebServerRequest *request);
    static void onStop(AsyncWebServerRequest *request);
    static void onLed(AsyncWebServerRequest *request);
};
#endif