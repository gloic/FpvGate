#pragma once

#include "Gate.h"

class Starter : public Gate {
    public:
        Starter(): Gate() {}
        void setup();
    protected:
        void setupWifi();
        void setupWebController();
        void setupModules();
        
        void doRegister();
        void doNotifyPassage();
        void setupButton();
};