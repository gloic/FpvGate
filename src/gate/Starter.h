#pragma once

#include "Gate.h"

class Starter : public Gate {
    public:
        Starter(): Gate() {}
        void setup(AsyncWebServer &webServer);
    protected:
        void setupWifi();
        void setupWebController(AsyncWebServer &webServer);
        void setupModules();
        
        void doRegister();
        void doNotifyPassage();
        void setupButton();
};