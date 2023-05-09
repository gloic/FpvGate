#ifndef Starter_H
#define Starter_H

#include "Gate.h"

class Starter : public Gate {
  
  protected:
    void setupWebController();
    void setupGPIO();
  private:
    void onNotify(AsyncWebServerRequest * request);
    int registerGate(String ip);
};

#endif