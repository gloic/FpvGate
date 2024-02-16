#pragma once

#include <config/GateConfig.h>
#include "IModule.h"

class MenuDisplay : public IModule {
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