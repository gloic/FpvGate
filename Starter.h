#ifndef Starter_H
#define Starter_H

#include "Gate.h"

class Starter : public Gate {
  public:
  protected:	
	void setupWifi();
    void setupWebController();
    void setupGPIO();	
	void notifyPass();
  private:
    int registerGate(String ip);
	void startListening(Gate * gate)
	void stopListening(Gate * gate);
	
	void onTrackMode(AsyncWebServerRequest * request);
	void onRaceMode(AsyncWebServerRequest * request);
};

#endif