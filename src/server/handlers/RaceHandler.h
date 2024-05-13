#pragma once
#include "HandlerBase.h"
#include "server/managers/TrackManager.h"
#include "server/services/TimerService.h"

class RaceHandler : public HandlerBase {
    public:
        RaceHandler() : 
            HandlerBase(),
            trackManager(TrackManager::getInstance()),
            timerService(TimerService::getInstance()) {}

        String getModeName() override { return "Race";}

        void begin() override;
        void end() override;
        void handleStarterPassage(GateClient& gate) override;
        void handleGatePassage(GateClient& gate) override;
        void reset() override;
    private:
        TrackManager& trackManager;
        TimerService& timerService;
};