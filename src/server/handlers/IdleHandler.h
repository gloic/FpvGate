#pragma once
#include "HandlerBase.h"

class IdleHandler : public HandlerBase {
    public:
        void begin() override;
        void end() override;
};