#include "IdleHandler.h"
#include <ArduinoLog.h>
#include <server/managers/LcdManager.h>

void IdleHandler::begin() {
    Log.infoln("start idle");
}

void IdleHandler::end() {
    Log.infoln("stop idle");
}