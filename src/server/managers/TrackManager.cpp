#include "TrackManager.h"
#include <server/managers/GateManager.h>

TrackManager* TrackManager::instance = nullptr;

void TrackManager::addGate(GateClient& gate) {
    track->addGate(gate);
}

bool TrackManager::isTrackEmpty() {
    return this->getCurrentTrack().getGates().size() == 0;
}

int TrackManager::getTrackSize() {
    return this->getCurrentTrack().getGates().size();
}