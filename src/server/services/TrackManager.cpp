#include "TrackManager.h"
#include <server/services/GateManager.h>

TrackManager* TrackManager::instance = nullptr;

void TrackManager::setCurrentTrack(const Track& track) {
    // TODO - incorrect
    // track.reset(new Track(track));
}

Track& TrackManager::getCurrentTrack() {
    return *track;
}

void TrackManager::addGate(int id) {
    GateClient& gate = GateManager::getInstance().findById(id);
    track->addGate(gate);
}

void TrackManager::setStarter(GateClient& starter) {
    // track->setStarter(starter);
}