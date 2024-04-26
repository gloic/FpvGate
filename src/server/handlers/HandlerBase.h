#pragma once
#include <server/managers/GateManager.h>
#include <server/handlers/executors/ListenExecutor.h>
#include <server/managers/LcdManager.h>
#include <server/model/GateClient.h>
#include <ArduinoLog.h>

class HandlerBase {
    public:
        HandlerBase(): 
            gateManager(GateManager::getInstance()), 
            listenExecutor(ListenExecutor::getInstance()), 
            lcdManager(LcdManager::getInstance()) { }
        virtual void begin() = 0;
        virtual void end() = 0;
        virtual void reset() {}
        virtual String getName() = 0;
        //virtual String* getContent() {}
        
        virtual void refreshDisplay() {} // TODO - Make it purely virtual

        void onGatePassage(int id) { onGatePassage(gateManager.findById(id)); }
    protected:
        GateManager& gateManager;
        ListenExecutor& listenExecutor;
        LcdManager& lcdManager;
        boolean isActive;

        virtual void onGatePassage(GateClient& gate) {}
        virtual void handleStarterPassage(GateClient& gate) {}
        virtual void handleGatePassage(GateClient& gate) {}
};
