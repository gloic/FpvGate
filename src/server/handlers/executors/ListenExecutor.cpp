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
    this->sendToGates("start", whenPass);
}

void ListenExecutor::stopGates() {
    this->sendToGates("stop", ActionWhenPass::STOP);
}

void ListenExecutor::sendToStarter(String state, ActionWhenPass actionWhenPass) {
    GateClient &starter = GateManager::getInstance().getStarter();
    this->listen(starter, state, actionWhenPass);
}

void ListenExecutor::sendToGate(GateClient& gate, String state, ActionWhenPass actionWhenPass) {
    this->listen(gate, state, actionWhenPass);
}

void ListenExecutor::sendToGates(String state, ActionWhenPass actionWhenPass) {
    std::vector<GateClient> gates = GateManager::getInstance().findAll();
    for (auto &gate : gates) {
        this->sendToGate(gate, state, actionWhenPass);
    }
}

// void ListenExecutor::listen(GateClient& gate, String state, ActionWhenPass actionWhenPass) {
//     webUtils.post(gate.getIp(), "/api/gate/listen/" + state);
// }

void ListenExecutor::startListen(GateClient& gate, ActionWhenPass actionWhenPass) {
    // TODO send actionWhenPass too
    webUtils.post(gate.getIp(), "/api/gate/listen/start");
}

void ListenExecutor::stopListen(GateClient& gate, String state) {
    webUtils.post(gate.getIp(), "/api/gate/listen/stop");
}