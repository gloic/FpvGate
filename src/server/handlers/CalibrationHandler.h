#pragma once
#include "HandlerBase.h"

class CalibrationHandler : public HandlerBase {
    public:
        CalibrationHandler() : HandlerBase() {}
        String getModeName() override { return "Calibration";}

        void begin() override;
        void end() override;
        void reset() override;

        void refreshDisplay() override;

        void handleStarterPassage(GateClient& gate) override {};
        void handleGatePassage(GateClient& gate) override {};
};