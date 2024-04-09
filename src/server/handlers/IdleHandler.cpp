#include "IdleHandler.h"
#include <ArduinoLog.h>

void IdleHandler::begin() {
    Log.infoln("start idle");
}

void IdleHandler::end() {
    Log.infoln("stop idle");
}