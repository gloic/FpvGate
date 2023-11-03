#pragma once 
#include "web/GateWebController.h"
#include "Arduino.h"

class GateService {
    public:
        void setIpStarter(String ip);
        int registerGate();
        void notifyPassage();
    private:
        String ipStarter;
        GateWebController webController;
};