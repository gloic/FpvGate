#pragma once
#include "HandlerBase.h"
#include "server/managers/TrackManager.h"
#include "server/services/TimerService.h"

class RaceHandler : public HandlerBase {
    public:
        RaceHandler() : HandlerBase(), 
            trackManager(TrackManager::getInstance()), 
            timerService(TimerService::getInstance()) {} 
            
        void begin() override;
        void end() override;
        void onGatePassage(GateClient& gate) override;
        void handleStarterPassage(GateClient& gate) override;
        void handleGatePassage(GateClient& gate) override;
        void reset() override;

        String getModeName() override { return "Race"; };
        
    private:
        TrackManager& trackManager;
        TimerService& timerService;
};