#ifndef Gate_H
#define Gate_H

#include "EspBase.h"
#include "Secrets.h"
#include <HTTPClient.h>
#include <ESPAsyncWebServer.h>

class Gate : public EspBase {
public:
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
private:
  void setupWifi();
  static void onStart(AsyncWebServerRequest* request);
  static void onStop(AsyncWebServerRequest* request);
  static void onLed(AsyncWebServerRequest* request);
};

#endif
