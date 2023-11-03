#include "CalibrationHandler.h"
#include <ArduinoLog.h>

void CalibrationHandler::begin() {
    Log.infoln("Begin Calibration");
    // TODO - Send /listen/start to all gates with continue + starter'
}

void CalibrationHandler::end() {
    Log.infoln("End Calibration");
    // TODO - Send /listen/stop to all gates with continue + starter'
}