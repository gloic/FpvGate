#include "GateBase.h"
#include "Gate.h"

class GateWrapper : public GateBase {
private:
    Gate gate;

public:
    void setup() override {
        gate.setup();
    }

    void loop() override {
        gate.loop();
    }
};