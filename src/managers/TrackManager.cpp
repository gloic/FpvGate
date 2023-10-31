#include "TrackManager.h"
#include "../structs/GateMode.h"

/**
 * Update lastTime and bestLapTime if needed
 * @param time
 * @return true if bestLapTime updated too.
 */
boolean TrackManager::setLapTime(long time) {
    lastLapTime = time;
    if (lastLapTime < bestLapTime || bestLapTime == -1) {
        bestLapTime = time;
        return true;
    }
    return false;
}

void TrackManager::resetLap() {
    Serial.println("Lap reset");
    raceStarted = true;
    startTime = millis();
    nextGateIndex = 0;
}

void TrackManager::startLap() {
    Serial.println("Start lap");
    startTime = millis();
    resetNextGateIndex();
    raceStarted = true;
}

void TrackManager::stopLap() {
    raceStarted = false;
    elapsedTime = (millis() - startTime) / 1000;
    Serial.print("Lap finished in ");
    Serial.print(elapsedTime);
    Serial.println("s");
    // Update last time
    boolean newRecord = setLapTime(elapsedTime);
    if(newRecord) {
        Serial.println("New record");
    }
    resetLap();
}

int TrackManager::addGateToTrack(GateClient &gate) {
    trackGates.push_back(gate);
    return getTrackGateSize();
}