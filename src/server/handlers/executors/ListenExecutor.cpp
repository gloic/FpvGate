#include "ListenExecutor.h"
#include <server/services/GateManager.h>

void ListenExecutor::startStarter(ActionWhenPass whenPass) {
    this->sendToStarter("start", whenPass);
}

void ListenExecutor::stopStarter() {
    this->sendToStarter("stop", ActionWhenPass::STOP); 
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

void ListenExecutor::sendToGates(String state, ActionWhenPass actionWhenPass) {
    std::vector<GateClient> gates = GateManager::getInstance().findAll();
    for (auto &gate : gates) {
        this->listen(gate, state, actionWhenPass);
    }
}

void ListenExecutor::listen(GateClient& gate, String state, ActionWhenPass actionWhenPass) {
    webUtils.post(gate.getIp(), "/api/gate/listen/" + state);
}