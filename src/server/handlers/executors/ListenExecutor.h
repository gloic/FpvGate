#pragma once

#include <server/model/GateClient.h>
#include <utils/WebUtils.h>
#include <server/model/enums/ActionWhenPass.h>
#include <server/managers/GateManager.h>

class ListenExecutor {
    public:
        static ListenExecutor &getInstance();

        void startStarter(ActionWhenPass whenPass);
        void stopStarter();

        void startGate(GateClient& gate, ActionWhenPass whenPass);
        void startGates(ActionWhenPass whenPass);
        void stopGates();
        
    private:
        ListenExecutor(): gateManager(GateManager::getInstance()), webUtils() {}

        static ListenExecutor *instance;
        WebUtils webUtils;
        GateManager& gateManager;
        void startListen(GateClient& gate, ActionWhenPass whenPass);
        void stopListen(GateClient& gate);
};