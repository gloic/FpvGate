#pragma once

#include "IModule.h"

class LedStrip : public IModule {
    public:
        void setup() override;
        void loop() override;
};