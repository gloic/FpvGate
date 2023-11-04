#include "TrackManager.h"

#include <server/services/GateManager.h>

TrackManager* TrackManager::instance = nullptr;
TrackManager::TrackManager(): currentTrack(new Track()) {}

TrackManager& TrackManager::getInstance() {
    if (!instance) {instance = new TrackManager();}
    return *instance;
}

void TrackManager::setCurrentTrack(const Track& track) {
    // TODO - incorrect
    currentTrack.reset(new Track(track));
}

Track& TrackManager::getCurrentTrack() {
    return *currentTrack;
}

void TrackManager::addGate(int id) {
    GateClient& gate = GateManager::getInstance().findById(id);
    currentTrack->addGate(gate);
}