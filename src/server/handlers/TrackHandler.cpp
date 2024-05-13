#include "TrackHandler.h"
#include <server/model/enums/ActionWhenPass.h>
#include <server/model/Track.h>

void TrackHandler::begin() {
    listenExecutor.startStarter(ActionWhenPass::STOP);
}

void TrackHandler::end() {
    listenExecutor.stopStarter();
    listenExecutor.stopGates();
}

void TrackHandler::handleStarterPassage(GateClient& gate) {
    Log.infoln("TrackHandler::handleStarterPassage");

    if (trackManager.isTrackEmpty()) {
        trackManager.addGate(gate);
        listenExecutor.startGates(ActionWhenPass::STOP);
    } else {
        this->end();
    }
}

void TrackHandler::handleGatePassage(GateClient& gate) {
    Log.infoln("TrackHandler::handleGatePassage");

    trackManager.addGate(gate);
    // TODO - once first gate passed, send listen to starter (do not send it at each passage)
    if (trackManager.getTrackSize() == 1) {
        listenExecutor.startStarter(ActionWhenPass::STOP);
    }
}

void TrackHandler::reset() {
    Log.infoln("TrackHandler::reset");
    trackManager.clearTrack();
    this->begin();
}