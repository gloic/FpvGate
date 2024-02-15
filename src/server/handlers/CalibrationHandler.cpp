#include "CalibrationHandler.h"
#include <ArduinoLog.h>

#include <server/model/enums/ActionWhenPass.h>

void CalibrationHandler::begin() {
    Log.infoln("Begin Calibration");
    listenExecutor.startStarter(ActionWhenPass::CONTINUE);
    listenExecutor.startGates(ActionWhenPass::CONTINUE);
}

void CalibrationHandler::end() {
    Log.infoln("End Calibration");
    listenExecutor.stopStarter();
    listenExecutor.stopGates();
}

void CalibrationHandler::reset() {
    Log.infoln("Reset");
    this->begin();
}