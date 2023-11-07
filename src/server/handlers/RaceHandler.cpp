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
    listenExecutor.stopAll();
}

void RaceHandler::gatePassage(GateClient& gate) {
    /* When starter pass :
        - start chrono
        - send listen to next gate (first of list)
    */
    
    GateClient& nextGate = trackManager.getNextGate();
    // if gate : listenExecutor.startListen(ActionWhenPass::STOP);
    // if starter : start on starter
    trackManager.advanceToNextGate();
}

void RaceHandler::reset() {

}