#include "FpvGateServer.h"
#include <ArduinoLog.h>
#include <server/managers/GateManager.h>

FpvGateServer* FpvGateServer::instance = nullptr;

const ServerMode FpvGateServer::modes[] = {ServerMode::IDLE, ServerMode::CALIBRATION, ServerMode::TRACK, ServerMode::RACE};

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


void FpvGateServer::selectNextMode() {
    Log.infoln("selectNextMode");
    nextModeIdx = (nextModeIdx + 1) % 4;
    Log.infoln("nextModeIdx=%d", nextModeIdx);
    lcdManager.clear();
    String tempTitle = "(" + handlers[modes[nextModeIdx]]->getModeName() + ") OK ?";
    lcdManager.setTitle(tempTitle);
    lcdManager.show();
}

void FpvGateServer::confirmMode() {
    Log.infoln("confirmMode");
    Log.infoln("nextModeIdx=%d", nextModeIdx);
    setMode(modes[nextModeIdx]);
}
