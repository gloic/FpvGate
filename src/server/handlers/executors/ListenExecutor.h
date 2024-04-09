#pragma once

#include <server/model/GateClient.h>
#include <utils/WebUtils.h>
#include <server/model/enums/ActionWhenPass.h>
#include <server/services/GateManager.h>

class ListenExecutor {
    public:
        ListenExecutor(): gateManager(GateManager::getInstance()) {};

        void startStarter(ActionWhenPass whenPass);
        void stopStarter();

        void startGate(GateClient& gate, ActionWhenPass whenPass);
        void startGates(ActionWhenPass whenPass);
        void stopGates();
        
    private:
        WebUtils webUtils;
        GateManager& gateManager;
        void startListen(GateClient& gate, ActionWhenPass whenPass);
        void stopListen(GateClient& gate);
};