#pragma once
#include <server/services/GateManager.h>
#include <server/handlers/executors/ListenExecutor.h>
#include <server/services/GateManager.h>
#include <server/model/GateClient.h>
#include <ArduinoLog.h>

class HandlerBase {
    public:
        HandlerBase(): gateManager(GateManager::getInstance()), listenExecutor(listenExecutor) {}
        virtual void begin() = 0;
        virtual void end() = 0;

        virtual void reset() {};

        void onGatePassage(int id) { onGatePassage(GateManager::getInstance().findById(id)); };
        
    protected:
        GateManager& gateManager;
        ListenExecutor& listenExecutor;
        boolean isActive;

        virtual void onGatePassage(GateClient& gate) {};
};
