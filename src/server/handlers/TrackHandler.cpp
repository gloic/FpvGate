#include "TrackHandler.h"
#include <server/model/enums/ActionWhenPass.h>
#include <server/model/Track.h>
#include <memory>
#include <typeinfo>

void TrackHandler::begin() {
    listenExecutor.startStarter(ActionWhenPass::STOP);
}

void TrackHandler::end() {
    listenExecutor.stopStarter();
    listenExecutor.stopAll();
}

void TrackHandler::gatePassage(GateClient& gate) {
    if(gate.isStarter()) {
        handleStarterPassage(gate);
    } else {
        handleGatePassage(gate);
    }
}

void TrackHandler::handleStarterPassage(GateClient& gate) {
    // TODO - create a dedicated method
    if(trackManager.getCurrentTrack().getGates().size() == 0) {
        // Add Starter in the track and stop listening
        handleGatePassage(gate);
    } else {
        // End 
    }
}

void TrackHandler::handleGatePassage(GateClient& gate) {
    trackManager.addGate(gate);
    // TODO - once first gate passed, send listen to starter (do not send it at each passage)
    if(trackManager.getCurrentTrack().getGates().size() == 1) {
        listenExecutor.startStarter(ActionWhenPass::STOP);
    }
}

void TrackHandler::reset() {
    // TODO - clear track
    trackManager.clearTrack();
    begin();
}