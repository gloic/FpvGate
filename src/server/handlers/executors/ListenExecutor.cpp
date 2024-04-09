#include "ListenExecutor.h"
#include <server/services/GateManager.h>
#include <config/GateEndPoints.h>

void ListenExecutor::startStarter(ActionWhenPass whenPass) {
    this->gateManager.starterStartListen();
}

void ListenExecutor::stopStarter() {
    this->gateManager.starterStopListen();
}

void ListenExecutor::startGate(GateClient& gate, ActionWhenPass whenPass) {
    this->startListen(gate, whenPass);
}

void ListenExecutor::startGates(ActionWhenPass whenPass) {
    for (auto &gate : this->gateManager.findAll()) {
        this->startListen(gate, whenPass);
    }
}

void ListenExecutor::stopGates() {
    for (auto &gate : this->gateManager.findAll()) {
        this->stopListen(gate);
    }
}

void ListenExecutor::startListen(GateClient& gate, ActionWhenPass actionWhenPass) {
    // TODO send actionWhenPass too
    webUtils.post(gate.getIp(), LISTEN_START);
}

void ListenExecutor::stopListen(GateClient& gate) {
    webUtils.post(gate.getIp(), LISTEN_STOP);
}