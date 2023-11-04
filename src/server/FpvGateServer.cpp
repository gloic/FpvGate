#include "FpvGateServer.h"
#include <ArduinoLog.h>

FpvGateServer* FpvGateServer::instance = nullptr;

// FpvGateServer::FpvGateServer() {}

// FpvGateServer& FpvGateServer::getInstance() {
//     if (!instance) {instance = new FpvGateServer();}
//     return *instance;
// }

void FpvGateServer::setMode(ServerMode newMode) {
    Log.infoln("Changing mode. Actual:%d  - New:%d",  static_cast<int>(mode), static_cast<int>(newMode));
    mode = newMode;
    currentHandler->end();
    currentHandler = handlers[newMode]; 
    currentHandler->begin();
}

String FpvGateServer::gatePassage(int id) {
    return currentHandler->gatePassage(id);
}