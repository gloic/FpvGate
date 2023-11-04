#include "FpvGateServer.h"

FpvGateServer* FpvGateServer::instance = nullptr;

FpvGateServer::FpvGateServer() {}

FpvGateServer& FpvGateServer::getInstance() {
    if (!instance) {instance = new FpvGateServer();}
    return *instance;
}

void FpvGateServer::setMode(ServerMode newMode) {
    mode = newMode;
    currentHandler = handlers[newMode]; 
}

void FpvGateServer::loop() {

}

void FpvGateServer::gatePassage(int id) {
    currentHandler->gatePassage(id);
}