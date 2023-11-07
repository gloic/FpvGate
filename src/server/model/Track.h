#pragma once
#include <vector>
#include "server/model/GateClient.h"
#include "memory"

class Track {
    public:
        Track() {}
        // Track() : starter(nullptr) {}
        // explicit Track(std::shared_ptr<GateClient> starter = nullptr) : starter(starter) {}

        std::vector<GateClient>& getGates();
        // GateClient& getStarter() {return *starter;};
        GateClient& getNextGate();
        void advanceToNextGate();
        void addGate(GateClient& gate);
        // void setStarter(std::shared_ptr<GateClient> starter) {this->starter = starter; };
        void reset() {gates.clear();};
    private:
        std::vector<GateClient> gates;
        // std::shared_ptr<GateClient> starter;
        int nextGateIndex = 0;
};