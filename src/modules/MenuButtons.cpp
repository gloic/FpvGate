#include "MenuButtons.h"

#include <ArduinoLog.h>

void MenuButtons::setup() {
    // buttonUp.attachClick(&MenuButtons::onUpPressed);
}

void MenuButtons::loop() {

}

void MenuButtons::onUpPressed() {
    Log.infoln("onUpPressed");
}

void MenuButtons::onDownPressed() {
    Log.infoln("onDownPressed");
}

void MenuButtons::onOkPressed() {
    Log.infoln("onOkPressed");
}

void MenuButtons::onCancelPressed() {
    Log.infoln("onCancelPressed");
}