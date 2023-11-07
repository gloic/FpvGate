#pragma once
#include "HandlerBase.h"
#include "server/services/TrackManager.h"

class RaceHandler : public HandlerBase {
    public:
        RaceHandler() : HandlerBase(), trackManager(TrackManager::getInstance()) {} 
        void begin() override;
        void end() override;
        void gatePassage(GateClient& gate) override;
        void reset() override;
    private:
        TrackManager& trackManager;
};