#pragma once

#include <server/model/GateClient.h>
#include <utils/WebUtils.h>
#include <server/model/enums/ActionWhenPass.h>

class ListenExecutor {
    public:
        ListenExecutor() {};

        void startStarter(ActionWhenPass whenPass);
        void stopStarter();

        void startGate(GateClient& gate, ActionWhenPass whenPass);
        void startGates(ActionWhenPass whenPass);
        void stopGates();
        
    private:
        WebUtils webUtils;
        void startListen(GateClient& gate, ActionWhenPass whenPass);
        void stopListen(GateClient& gate);
};