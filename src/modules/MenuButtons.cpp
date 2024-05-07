#include "MenuButtons.h"

#include <ArduinoLog.h>

MenuButtons::MenuButtons(int pinBtnNext, int pinBtnOk) {
    buttonNext = new OneButton(pinBtnNext);
    buttonOk = new OneButton(pinBtnOk);
}

void MenuButtons::setup() {
    buttonNext->attachClick(&MenuButtons::onNext);
    buttonNext->attachLongPressStop(&MenuButtons::onPrevious);
    buttonOk->attachClick(&MenuButtons::onOk);
    buttonOk->attachLongPressStop(&MenuButtons::onCancel);
}

void MenuButtons::loop() {
    buttonNext->tick();
    buttonOk->tick();
}

void MenuButtons::onNext() {
    Log.infoln("onNext");
}

void MenuButtons::onPrevious() {
    Log.infoln("onPrevious");
}

void MenuButtons::onOk() {
    Log.infoln("onOk");
}

void MenuButtons::onCancel() {
    Log.infoln("onCancel");
}