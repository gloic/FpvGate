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