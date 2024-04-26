#include "FpvGateServer.h"
#include <ArduinoLog.h>
#include <server/managers/GateManager.h>

FpvGateServer* FpvGateServer::instance = nullptr;

FpvGateServer& FpvGateServer::getInstance() {
    if (!instance) {
        instance = new FpvGateServer();
    }
    return *instance;
}

void FpvGateServer::setMode(ServerMode newMode) {
    Log.infoln("Changing mode. Actual:%d  - New:%d",  static_cast<int>(mode), static_cast<int>(newMode));
    this->mode = newMode;
    this->switchHandler(newMode);
}

void FpvGateServer::onGatePassage(int id) {
    // auto& gate = GateManager::getInstance().findById(id);
    // currentHandler->onGatePassage(gate);
    currentHandler->onGatePassage(id);
}

void FpvGateServer::switchHandler(ServerMode newMode) {
    if(currentHandler) {
        currentHandler->end();
    }
    currentHandler = handlers[newMode];
    currentHandler->begin();
}

