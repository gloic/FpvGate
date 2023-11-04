#pragma once
#include <vector>
#include "server/model/GateClient.h"
#include "server/model/StarterClient.h"
#include "memory"

class Track {
    public:
        Track() : starter(nullptr) {};
        void addGate(GateClient& gate);
        std::vector<GateClient>& getGates();        
        std::shared_ptr<StarterClient>& getStarter();
        void setStarter(std::shared_ptr<StarterClient> starterPtr);
        boolean isReadyToRace();
    private:
        std::shared_ptr<StarterClient> starter;
        std::vector<GateClient> gates;
};