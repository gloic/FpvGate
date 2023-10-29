#pragma once

class GateBase {
    public:
        virtual void setup() = 0;
        virtual void loop() = 0;
        virtual ~GateBase() {}
};