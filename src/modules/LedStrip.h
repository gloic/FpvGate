#pragma once

#include "Module.h"

class LedStrip : public Module {
    public:
        void setup() override;
        void loop() override;
};