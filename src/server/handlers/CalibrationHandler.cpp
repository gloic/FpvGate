#include "CalibrationHandler.h"
#include <ArduinoLog.h>

#include <server/model/enums/ActionWhenPass.h>

void CalibrationHandler::begin() {
    Log.infoln("Begin Calibration");
    listenExecutor.startStarter(ActionWhenPass::CONTINUE);
    listenExecutor.startAll(ActionWhenPass::CONTINUE);
}

void CalibrationHandler::end() {
    Log.infoln("End Calibration");
    listenExecutor.stopStarter();
    listenExecutor.stopAll();
}