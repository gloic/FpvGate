#pragma once

#include "Gate.h"
#include "OneButton.h"

class Starter : public Gate {
    public:
        Starter(): Gate() {}
        void setup(AsyncWebServer &webServer) {
            setupWifi();
            setupWebController(webServer);
            setupButton();
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
        static Starter *instance;
        static Starter& getInstance();
        
        OneButton* buttonReset;

        void setupButton();
        static void onButtonResetPress();
        static void onButtonResetDoublePress();
        static void onButtonResetLongPress();
};