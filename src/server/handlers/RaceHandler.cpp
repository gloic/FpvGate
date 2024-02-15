#include "RaceHandler.h"

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
    listenExecutor.stopGates();
}

void RaceHandler::onGatePassage(GateClient& gate) {
    if (gate.isStarter()) {
        /*
            if track over
                stop chrono
            if starting track
                start chrono
        */
    }
    
    GateClient& nextGate = trackManager.getNextGate();

    // if gate : listenExecutor.startListen(ActionWhenPass::STOP);
    // if starter : start on starter
    trackManager.advanceToNextGate();
}

void RaceHandler::reset() {

}