#pragma once

#include "Gate.h"
#include "../structs/GateClient.h"
#include "../managers/TrackManager.h"
#include "../managers/GatesManager.h"
#include "../services/web/StarterWebController.h"
#include "../services/web/StarterRestController.h"

class Starter : public Gate {
public:
    Starter() { instance = this; };
    void setup();
    void loop();
protected:
    void notifyPass();

private:
    static Starter *instance;
    boolean isCalibrationMode = false;
    StarterWebController webController;
    StarterRestController restController;

    GatesManager gatesManager; // TODO - Remove this dependency
    TrackManager trackHandler {};
    
    void setupWifi();
    void setupWebController();
    void setupGPIO();
    void doRegister(String ip);
    
    void handleStarterPassage();
    
    void enableTrackMode();
    void enableRaceMode();
    void startLap();
    void stopLap();
    void resetLap();

    void gateStartListening(GateClient &gate);
    void gateStopListening(GateClient &gate);
    void handleGatePassed(GateClient &gate);

    void enableCalibrationMode();

    // static void onRegisterGate(AsyncWebServerRequest *request);
    // static void onGatePassed(AsyncWebServerRequest *request);
    static void onButtonResetPress();

};