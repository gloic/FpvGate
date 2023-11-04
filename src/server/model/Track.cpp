#include "Track.h"

void Track::addGate(GateClient& gate) {
    gates.push_back(gate);
}

std::vector<GateClient>& Track::getGates() {
    return gates;
}  

std::shared_ptr<StarterClient>& Track::getStarter() {
    return starter;
}

boolean Track::isReadyToRace() {
    return gates.size() > 0;
}

void Track::setStarter(std::shared_ptr<StarterClient> starterPtr) {
    this->starter = starterPtr;
}