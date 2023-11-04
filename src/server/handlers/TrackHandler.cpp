#include "TrackHandler.h"
#include "server/services/TrackManager.h"
#include <server/model/enums/ActionWhenPass.h>
#include <server/model/Track.h>

void TrackHandler::begin() {
    listenExecutor.stopStarter();
    listenExecutor.startAll(ActionWhenPass::STOP);
}

void TrackHandler::end() {
    listenExecutor.stopStarter();
    listenExecutor.stopAll();
}

void TrackHandler::gatePassage(int id) {
    TrackManager::getInstance().addGate(id);

    // when first gate passed, send listen with stop to starter
    listenExecutor.startStarter(ActionWhenPass::STOP);

    // when starter is passed, the track is over and this is the end of this mode
}