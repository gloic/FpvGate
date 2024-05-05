#pragma once

#include "Gate.h"
#include "OneButton.h"

class Starter : public Gate {
    public:
        Starter(): Gate() {}
        void setup(AsyncWebServer &webServer) {
            setupWifi();
            setupWebController(webServer);
            setupButtons();
            setupModules();
            id = doRegister();
        }
        void loop();
        void startListen() { Gate::startListen(); }
    protected:
        void setupWifi();
        void setupWebController(AsyncWebServer &webServer);
        void setupModules();
        int doRegister();
        void doNotifyPassage();
    private:
        OneButton* buttonReset;
        OneButton* buttonNext;
        OneButton* buttonOk;

        void setupButtons();
        static void onButtonResetClick();
        static void onButtonResetDoubleClick();
        static void onButtonResetLongClick();

        static void onButtonNextClick();
        static void onButtonOkClick();
};