#pragma once
#include "HandlerBase.h"

class CalibrationHandler : public HandlerBase {
    public:
        void begin() override;
        void end() override;
        void reset() override;

        String getModeName() override { return "Calibration"; }
        
        void refreshDisplay() override;

        void onGatePassage(int id) override {}
};