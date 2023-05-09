#ifndef EspBase_H
#define EspBase_H

#include "Arduino.h"
#include <ESPAsyncWebServer.h>

class EspBase
{  
  public:  
    EspBase() : webServer(80), _version("1.0.b") {};
    void init(String ssid, String pwd);
    void setupBase();
	  void setupAPWifi();
	  void setupWifi();	
	  String getVersion();
    String getParamFromRequest(String paramName, AsyncWebServerRequest * request);
    AsyncWebServer server();    
  protected:
    void setupWebController();
    void startWebServer();
    void setupGPIO();
  private:
    String _version;
    AsyncWebServer webServer;
};

#endif
