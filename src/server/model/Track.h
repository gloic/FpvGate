#pragma once
#include <vector>
#include "server/model/GateClient.h"
#include "memory"

class Track {
    public:
        Track() {};
        void addGate(GateClient& gate);
        std::vector<GateClient>& getGates();

        GateClient& getNextGate() {return gates[nextGateIndex];}
        void advanceToNextGate();
    private:
        std::vector<GateClient> gates;
        int nextGateIndex = 0;
};