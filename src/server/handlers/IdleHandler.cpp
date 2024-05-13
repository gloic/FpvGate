#include "IdleHandler.h"
#include <ArduinoLog.h>

void IdleHandler::begin() {
    Log.infoln("start idle");
    this->refreshDisplay();
}

void IdleHandler::end() {
    Log.infoln("stop idle");
}

void IdleHandler::refreshDisplay() {
    this->lcdManager.setTitle(this->getModeName());
    
    String lines[] = {"Idle mode that does nothing", "Yeahhh"};
    this->lcdManager.setContent(lines, 2);
    this->lcdManager.show();
}
