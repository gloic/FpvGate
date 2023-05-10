#ifndef Gate_H
#define Gate_H

#include "EspBase.h"
#include "Secrets.h"
#include <HTTPClient.h>
#include <ESPAsyncWebServer.h>

class Gate : public EspBase {  
  public:
    void setup();
    void checkPass();
  protected:    
    void setupWifi();
    void setupWebController();
    void setupGPIO();
	void register();
    void notifyPass();
	//void setListening(bool value);
	AsyncWebServer server();
  private:
	void onStart(AsyncWebServerRequest * request);
	void onStop(AsyncWebServerRequest * request);
	void onLed(AsyncWebServerRequest * request);
};

#endif