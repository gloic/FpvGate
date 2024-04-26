#pragma once
#include "HandlerBase.h"

class IdleHandler : public HandlerBase {
    public:
        void begin() override;
        void end() override;
        void refreshDisplay() override;
        String getName() override { return "Idle"; };
};