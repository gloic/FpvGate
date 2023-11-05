#include "FpvGateServer.h"
#include <ArduinoLog.h>
#include <server/services/GateManager.h>

FpvGateServer* FpvGateServer::instance = nullptr;

void FpvGateServer::setMode(ServerMode newMode) {
    Log.infoln("Changing mode. Actual:%d  - New:%d",  static_cast<int>(mode), static_cast<int>(newMode));
    mode = newMode;
    currentHandler->end();
    currentHandler = handlers[newMode]; 
    currentHandler->begin();
}

void FpvGateServer::gatePassage(int id) {
    auto& gate = GateManager::getInstance().findById(id);
    currentHandler->gatePassage(gate);
}