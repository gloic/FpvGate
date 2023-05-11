#ifndef EspBase_H
#define EspBase_H

#include "Arduino.h"
#include <ESPAsyncWebServer.h>

class EspBase {
public:
  AsyncWebServer webServer;

  EspBase() : webServer(80), _version("1.0.c"){};
  virtual void setup();
  virtual void loop();
  
  //void setup(String ssid, String pwd);
  void setupAPWifi(String ssid, String pwd);
  void setupWifi(String ssid, String pwd);
  String getParamFromRequest(String paramName, AsyncWebServerRequest* request);
  static void onVersion(AsyncWebServerRequest* request);
  static void onRestart(AsyncWebServerRequest* request);  
protected:
  AsyncWebServer server();
  void setupWebController();
  void startWebServer();
  void setupGPIO();
private:
  String getVersion();
  String _version;
  
};

#endif
