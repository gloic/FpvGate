#pragma once
#include "server/managers/TrackManager.h"
#include "HandlerBase.h"

class TrackHandler : public HandlerBase {
    public:
        TrackHandler() : 
            HandlerBase(),
            trackManager(TrackManager::getInstance()) {}

        String getModeName() override { return "Track";}

        void begin() override;
        void end() override;
        void handleStarterPassage(GateClient& gate) override;
        void handleGatePassage(GateClient& gate) override;
        void reset() override;
        
    private:
        TrackManager& trackManager;
};