#include "TrackManager.h"
#include <server/services/GateManager.h>

TrackManager* TrackManager::instance = nullptr;

void TrackManager::addGate(GateClient& gate) {
    track->addGate(gate);
}

void TrackManager::setStarter(GateClient& starter) {
    auto starterPtr = std::make_shared<GateClient>(starter);
    track->setStarter(starterPtr);
}