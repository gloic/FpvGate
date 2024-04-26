#pragma once
#include "server/managers/TrackManager.h"
#include "HandlerBase.h"

class TrackHandler : public HandlerBase {
    public:
        TrackHandler() : HandlerBase(), trackManager(TrackManager::getInstance()) {}
        void begin() override;
        void end() override;
        void onGatePassage(GateClient& gate) override;
        void handleStarterPassage(GateClient& gate) override;
        void handleGatePassage(GateClient& gate) override;
        void reset() override;
        
        String getName() override { return "Track"; }
    private:
        TrackManager& trackManager;
};