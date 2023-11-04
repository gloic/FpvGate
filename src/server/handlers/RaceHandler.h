#pragma once
#include "HandlerBase.h"

class RaceHandler : public HandlerBase {
    public:
        void begin() override;
        void end() override;
        void gatePassage(int id) override;
};