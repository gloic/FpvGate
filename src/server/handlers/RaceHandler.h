#pragma once
#include "HandlerBase.h"

class RaceHandler : public HandlerBase {
    public:
        void begin() override;
        void end() override;
        String gatePassage(int id) override;
};