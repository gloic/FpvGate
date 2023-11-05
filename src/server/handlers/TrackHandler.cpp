#include "TrackHandler.h"
#include "server/services/TrackManager.h"
#include <server/model/enums/ActionWhenPass.h>
#include <server/model/Track.h>
#include <memory>
#include <typeinfo>

void TrackHandler::begin() {
    listenExecutor.stopStarter();
    listenExecutor.startAll(ActionWhenPass::STOP);
}

void TrackHandler::end() {
    listenExecutor.stopStarter();
    listenExecutor.stopAll();
}

void TrackHandler::gatePassage(GateClient& gate) {
    if(gate.isStarter()) {
        TrackManager::getInstance().setStarter(gate);
        // when starter is passed, the track is over and this is the end of this mode

    } else {
        TrackManager::getInstance().addGate(gate);
        // when first gate passed, send listen to starter
        listenExecutor.startStarter(ActionWhenPass::STOP);
    }
}