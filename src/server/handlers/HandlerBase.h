#pragma once
#include <server/services/GateManager.h>
#include <server/handlers/executors/ListenExecutor.h>
#include <server/services/GateManager.h>

class HandlerBase {
    public:
        HandlerBase(): gateManager(GateManager::getInstance()), listenExecutor(listenExecutor) {}
        virtual void begin() = 0;
        virtual void end() = 0;
        virtual String gatePassage(int id) {return "";};
    protected:
        GateManager& gateManager;
        ListenExecutor& listenExecutor;
};
