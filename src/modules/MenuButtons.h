#pragma once

#include <config/GateConfig.h>
#include "OneButton.h"

class MenuButtons {
    public:
     MenuButtons(): 
        buttonUp(PIN_MENU_UP),
        buttonDown(PIN_MENU_DOWN),
        buttonOk(PIN_MENU_OK),
        buttonCancel(PIN_MENU_CANCEL) {
            buttonUp.attachClick(&MenuButtons::onUpPressed);
            buttonDown.attachClick(&MenuButtons::onDownPressed);
            buttonOk.attachClick(&MenuButtons::onOkPressed);
            buttonCancel.attachClick(&MenuButtons::onCancelPressed);
        };
        
    private:
        OneButton buttonUp;
        OneButton buttonDown;
        OneButton buttonOk;
        OneButton buttonCancel;

        void setup();

        static void onUpPressed();
        static void onDownPressed();
        static void onOkPressed();
        static void onCancelPressed();
};