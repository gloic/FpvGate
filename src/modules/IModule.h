#pragma once

class IModule {
    public:
        virtual void setup() {};
        virtual void loop() {};
};