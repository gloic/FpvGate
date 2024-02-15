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
    listenExecutor.stopGates();
}

void TrackHandler::onGatePassage(GateClient& gate) {
    if (gate.isStarter()) {
        this->handleStarterPassage(gate);
    } else {
        this->handleGatePassage(gate);
    }
}

void TrackHandler::handleStarterPassage(GateClient& gate) {
    if (trackManager.isTrackEmpty()) {
        trackManager.addGate(gate);
        listenExecutor.startGates(ActionWhenPass::STOP);
    } else {
        this->end();
    }
}

void TrackHandler::handleGatePassage(GateClient& gate) {
    trackManager.addGate(gate);
    // TODO - once first gate passed, send listen to starter (do not send it at each passage)
    if (trackManager.getTrackSize() == 1) {
        listenExecutor.startStarter(ActionWhenPass::STOP);
    }
}

void TrackHandler::reset() {
    trackManager.clearTrack();
    this->begin();
}