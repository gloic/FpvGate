#include "IdleHandler.h"
#include <ArduinoLog.h>

void IdleHandler::begin() {
    Log.infoln("start idle");
}

void IdleHandler::end() {
    Log.infoln("stop idle");
}

void IdleHandler::refreshDisplay() {
    this->lcdManager.setTitle(this->getName());
    
    String lines[] = {"Line 1", "Line 2", "Line 3"};
    this->lcdManager.setContent(lines);
}