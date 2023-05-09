#ifndef Gate_H
#define Gate_H

#include "EspBase.h"
#include "Secrets.h"
#include <HTTPClient.h>
#include <ESPAsyncWebServer.h>

class Gate : public EspBase {  
  public:
    void setup();
    void notifyStarter();
    void notifyPass();
    void checkPass();
    AsyncWebServer server();
  protected:    
    void setupWebController();
    void setupGPIO();
};

#endif