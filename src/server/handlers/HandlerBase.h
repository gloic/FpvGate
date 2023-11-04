#pragma once
#include <server/services/GateManager.h>

class HandlerBase {
    public:
        HandlerBase(): gateManager(GateManager::getInstance()) {}
        virtual void begin() = 0;
        virtual void end() = 0;
        virtual void gatePassage(int id) {};
    protected:
        GateManager& gateManager;
};
