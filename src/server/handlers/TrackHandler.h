#pragma once
#include "server/services/TrackManager.h"
#include "HandlerBase.h"

class TrackHandler : public HandlerBase {
    public:
        TrackHandler() : HandlerBase(), trackManager(TrackManager::getInstance()) {}
        void begin() override;
        void end() override;

        void onGatePassage(GateClient& gate) override;
        void reset() override;
    private:
        TrackManager& trackManager;

        void handleStarterPassage(GateClient& gate);
        void handleGatePassage(GateClient& gate);
};