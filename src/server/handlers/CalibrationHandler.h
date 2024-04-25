#pragma once
#include "HandlerBase.h"

class CalibrationHandler : public HandlerBase {
    public:
        void begin() override;
        void end() override;
        void reset() override;
        String getName() override { return "Calibration"; }
};