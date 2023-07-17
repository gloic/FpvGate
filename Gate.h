#ifndef Gate_H
#define Gate_H

#include "EspBase.h"
#include "Secrets.h"
#include "modules/StateLed.h"

#include <HTTPClient.h>
#include <ESPAsyncWebServer.h>

class Gate : public EspBase {
  public:
    //Gate() {instance = this;}
    Gate();
    void setup() override;
    void loop() override;

  protected:
    WiFiClient wifiClient;
    HTTPClient http;   
    StateLed stateLed;
    
    bool isListening;
    void setupWebController();
    void setupGPIO();
    void doRegister(String ip);
    boolean checkPass();
    void notifyPass();
    void led(bool state);
    void blinkLed();
    void beep();
  private:
    static Gate* instance;
    void setupWifi();
    static void onStart(AsyncWebServerRequest* request);
    static void onStop(AsyncWebServerRequest* request);
    static void onLed(AsyncWebServerRequest* request);
};

#endif
