#pragma once

#include <config/GateConfig.h>
#include "OneButton.h"
#include "Module.h"

class MenuButtons : public Module {
    public:
        MenuButtons(int pinBtnNext, int pinBtnOk);
        void setup() override;
        void loop() override;        
    private:
        OneButton* buttonNext;
        OneButton* buttonOk;

        static void onNext();
        static void onPrevious();
        static void onOk();
        static void onCancel();
};