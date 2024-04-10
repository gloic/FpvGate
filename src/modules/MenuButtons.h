#pragma once

#include <config/GateConfig.h>
#include "OneButton.h"
#include "Module.h"

class MenuButtons : public Module {
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

        void setup() override;
        void loop() override;
        
    private:
        OneButton buttonUp;
        OneButton buttonDown;
        OneButton buttonOk;
        OneButton buttonCancel;

        static void onUpPressed();
        static void onDownPressed();
        static void onOkPressed();
        static void onCancelPressed();
};