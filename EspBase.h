#ifndef EspBase_H
#define EspBase_H

#include "Arduino.h"
#include <ESPAsyncWebServer.h>

class EspBase
{  
  public:  
    EspBase() : webServer(80), _version("1.0.b") {};
	void setupAPWifi(String ssid, String pwd);
	void setupWifi(String ssid, String pwd);	
    String getParamFromRequest(String paramName, AsyncWebServerRequest * request);    
	void onVersion(AsyncWebServerRequest * request);
	void onRestart(AsyncWebServerRequest * request);
	AsyncWebServer server();	
  protected:	
    void setupWebController();
    void startWebServer();
    virtual void setupGPIO();
  private:
	String getVersion();
    String _version;
    AsyncWebServer webServer;
};

#endif
