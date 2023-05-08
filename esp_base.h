#ifndef EspBase_H
#define EspBase_H

#include "Arduino.h"
#include <ESPAsyncWebServer.h>

class EspBase
{  
  public:  
    EspBase() : server(80), _version("1.0.b") {};
    void Init(String ssid, String pwd);
    void SetupBase();
    void SetupWifi();
    void SetupWebController();
    void StartWebServer();
    
    String GetVersion();
    String GetParamFromRequest(String paramName, AsyncWebServerRequest * request);
    
    AsyncWebServer server;
  private:
    String _ssid, _pwd, _version;
    
};

#endif
