#include "ListenExecutor.h"
#include <server/services/GateManager.h>

void ListenExecutor::starterListen(String action, ActionWhenPass actionWhenPass) {
    GateClient& starter = GateManager::getInstance().getStarter();
    listen(starter, action, actionWhenPass);
}

void ListenExecutor::listen(GateClient& gate, String action, ActionWhenPass actionWhenPass) {
    webUtils.post(gate.getIp(), "/api/gate/listen/" + action);
}

void ListenExecutor::listenAll(String action, ActionWhenPass actionWhenPass) {
    std::vector<GateClient> gates = GateManager::getInstance().findAll();
    for(auto& gate : gates) {
        listen(gate, "stop", actionWhenPass);
    }
}