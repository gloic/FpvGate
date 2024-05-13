#include "HandlerBase.h"

void HandlerBase::onGatePassage(int id) {
    GateClient& gate = gateManager.findById(id);
    if(gate.isStarter()) {
        handleStarterPassage(gate);
    } else {
        handleGatePassage(gate);
    }
}

