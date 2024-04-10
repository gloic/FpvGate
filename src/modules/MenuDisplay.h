#pragma once

#include <config/GateConfig.h>
#include "Module.h"

class MenuDisplay : public Module {
    public:
        void setup() override;
        void loop() override;

        void menuUp();
        void menuDown();
        void ok();
        void cancel();
    protected:

    private:

};