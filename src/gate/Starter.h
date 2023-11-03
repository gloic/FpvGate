#pragma once

#include <services/StarterService.h>
#include "Gate.h"

class Starter : public Gate {
    public:
        Starter(): Gate() {}
        void setup();
    protected:
        void setupWifi();
        void setupWebController();

        void doRegister();
        void doNotifyPassage();
    private:
        StarterService service;
};