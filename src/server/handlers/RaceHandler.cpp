#include "RaceHandler.h"
#include "server/services/TrackManager.h"

void RaceHandler::begin() {
    listenExecutor.startStarter(ActionWhenPass::STOP);
    /*
        From a TRACK:
            send listen to Starter (stop)
            once finished, restart
            
        when reset, restart track
    */
}

void RaceHandler::end() {
    listenExecutor.stopStarter();
    listenExecutor.stopAll();
}

void RaceHandler::gatePassage(int id) {
    GateClient& gate = TrackManager::getInstance().getNextGate();
    // if gate : listenExecutor.startListen(ActionWhenPass::STOP);
    // if starter : start on starter
    TrackManager::getInstance().advanceToNextGate();
}