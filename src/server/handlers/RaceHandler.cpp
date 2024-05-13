#include "RaceHandler.h"
#include <ArduinoLog.h>

void RaceHandler::begin() {
    Log.infoln("RaceHandler Begin");
    listenExecutor.startStarter(ActionWhenPass::STOP);
}

void RaceHandler::end() {
    Log.infoln("RaceHandler End");
    timerService.stop();
    listenExecutor.stopStarter();
    listenExecutor.stopGates();
}

void RaceHandler::reset() {
    Log.infoln("RaceHandler Reset");
    this->end();
    this->begin();
}

void RaceHandler::handleStarterPassage(GateClient& gate) {
    if(timerService.isRunning()) {
        timerService.stop();
        
        Log.infoln("Lap ended in %l", timerService.getLastLapTime());
        if(timerService.getLastLapTime() == timerService.getBestLapTime()) {
            Log.infoln("  - It's a new record !");
        }
    } else {
        timerService.start();
    }
}

void RaceHandler::handleGatePassage(GateClient& gate) {
    trackManager.advanceToNextGate();
    GateClient& nextGate = trackManager.getNextGate();
    listenExecutor.startGate(nextGate, ActionWhenPass::STOP);
}