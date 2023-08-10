#ifndef Starter_H
#define Starter_H

#include "Gate.h"
#include "./structs/GateClient.h"
#include "./modules/TrackHandler.h"
#include "headers/modules/StarterWebController.h"

class Starter : public Gate {
public:
    Starter() { instance = this; }
    void setup();
    void loop();
protected:
    void notifyPass();

private:
    static Starter *instance;
    StarterWebController webController;
    TrackHandler trackHandler {};
    
    void setupWifi();
    void setupWebController();
    void setupGPIO();
    void doRegister(String ip);
    int registerGate(String ip);

    void startListeningAll();
    void enableTrackMode();
    void enableRaceMode();
//    bool isMode(GateMode mode);
    void startLap();
    void stopLap();
    void resetLap();

    void handleGatePassed(int id);
    
    void gateStartListening(GateClient *gate);
    void gateStopListening(GateClient *gate);

    static void onRegisterGate(AsyncWebServerRequest *request);
    static void onGatePassed(AsyncWebServerRequest *request);
    static void onTrackMode(AsyncWebServerRequest *request);
    static void onRaceMode(AsyncWebServerRequest *request);
    static void onButtonResetPress();
};

#endif
