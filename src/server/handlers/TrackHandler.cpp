#include "TrackHandler.h"

#include "server/services/TrackManager.h"

/* TRACK
    id
    // label
    StarterClient
    vector<GatesClient>

    timer
    nbLap
    best lap
    last lap
*/

void TrackHandler::begin() {
    Track& track = TrackManager::getInstance().getCurrentTrack();
    // Send listen/start to all gate with stop
    // wait to receive /pass from gates
    
}

void TrackHandler::end() {
    // Send listen/stop to starter
}

void TrackHandler::gatePassage(int id) {
    // Add gate to track 
    TrackManager::getInstance().addGate(id);
    // when first gate passed, send listen with stop to starter
}