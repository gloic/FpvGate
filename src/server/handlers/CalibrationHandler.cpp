#include "CalibrationHandler.h"
#include <ArduinoLog.h>
#include <server/model/enums/ActionWhenPass.h>

void CalibrationHandler::begin() {
    Log.infoln("Begin Calibration");
    listenExecutor.startStarter(ActionWhenPass::CONTINUE);
    //listenExecutor.startGates(ActionWhenPass::CONTINUE);
}

void CalibrationHandler::end() {
    Log.infoln("End Calibration");
    listenExecutor.stopStarter();
    // listenExecutor.stopGates();
}

void CalibrationHandler::reset() {
    Log.infoln("Reset CalibrationHandler");
    this->begin();
}

void CalibrationHandler::refreshDisplay() {
    this->lcdManager.setTitle(this->getModeName());
    
    String lines[] = {"This is calibration mode"};
    this->lcdManager.setContent(lines, 1);
    this->lcdManager.show();
}