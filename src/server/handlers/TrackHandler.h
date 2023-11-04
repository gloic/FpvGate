#pragma once

#include "HandlerBase.h"

class TrackHandler : public HandlerBase {
    public:
        void begin() override;
        void end() override;
        String gatePassage(int id) override;
};