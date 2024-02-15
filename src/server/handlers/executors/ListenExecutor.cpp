#include "ListenExecutor.h"
#include <server/services/GateManager.h>

void ListenExecutor::startStarter(ActionWhenPass whenPass) {
    GateClient &starter = GateManager::getInstance().getStarter(); // TODO - Dedicated method
    this->startListen(GateManager::getInstance().getStarter(), whenPass);
}

void ListenExecutor::stopStarter() {
    GateClient &starter = GateManager::getInstance().getStarter(); // TODO - Dedicated method
    this->stopListen(starter);
}

void ListenExecutor::startGate(GateClient& gate, ActionWhenPass whenPass) {
    this->startListen(gate, whenPass);
}

void ListenExecutor::startGates(ActionWhenPass whenPass) {
    for (auto &gate : GateManager::getInstance().findAll()) {
        this->startListen(gate, whenPass);
    }
}

void ListenExecutor::stopGates() {
    for (auto &gate : GateManager::getInstance().findAll()) {
        this->stopListen(gate);
    }
}

void ListenExecutor::startListen(GateClient& gate, ActionWhenPass actionWhenPass) {
    // TODO send actionWhenPass too
    webUtils.post(gate.getIp(), "/api/gate/listen/start");
}

void ListenExecutor::stopListen(GateClient& gate) {
    webUtils.post(gate.getIp(), "/api/gate/listen/stop");
}