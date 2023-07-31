#ifndef Starter_H
#define Starter_H

#include "Gate.h"
#include "headers/structs/GateClient.h"
#include "headers/modules/TrackHandler.h"

class Starter : public Gate {
public:
    Starter() { instance = this; }
    void setup();
    void loop();
protected:
    void notifyPass();

private:
    static Starter *instance;
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

    void gateStartListening(const GateClient *gate);
    void gateStopListening(const GateClient *gate);
    
    static void onRegisterGate(AsyncWebServerRequest *request);
    static void onGatePassed(AsyncWebServerRequest *request);
    static void onTrackMode(AsyncWebServerRequest *request);
    static void onRaceMode(AsyncWebServerRequest *request);
    static void onButtonResetPress();
};

#endif
