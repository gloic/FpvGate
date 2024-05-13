#pragma once
#include "HandlerBase.h"

class IdleHandler : public HandlerBase {
    public:
        IdleHandler() : HandlerBase() {}
        String getModeName() override { return "Idle"; }
        
        void begin() override;
        void end() override;

        void refreshDisplay() override;

    protected:
        void handleStarterPassage(GateClient& gate) override {};
        void handleGatePassage(GateClient& gate) override {};
};