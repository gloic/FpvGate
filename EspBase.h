#ifndef EspBase_H
#define EspBase_H

#include "Arduino.h"
#include <ESPAsyncWebServer.h>

class EspBase
{  
  public:  
    EspBase() : server(80), _version("1.0.b") {};
    void init(String ssid, String pwd);
    void setupBase();
	
    void setupAPWifi();
	  void setupWifi();	
	
    void setupWebController();
    void startWebServer();
    
    String getVersion();
    String getParamFromRequest(String paramName, AsyncWebServerRequest * request);
    
    AsyncWebServer server;
  private:
    String _ssid, _pwd, _version;
    
};

#endif
