#include "Track.h"

void Track::addGate(GateClient& gate) {
    gates.push_back(gate);
}

std::vector<GateClient>& Track::getGates() {
    return gates;
}

void Track::advanceToNextGate() {
    if(nextGateIndex == gates.size() - 1) {
        nextGateIndex = 0;
    } else {
        nextGateIndex++;
    }
}