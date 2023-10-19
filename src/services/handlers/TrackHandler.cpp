#include "TrackHandler.h"
#include "../../structs/GateMode.h"

// unsigned long startTime = 0;

/**
 * Update lastTime and bestLapTime if needed
 * @param time
 * @return true if bestLapTime updated too.
 */
bool TrackHandler::setLapTime(long time) {
    this->lastLapTime = time;
    if (this->lastLapTime < this->bestLapTime || this->bestLapTime == -1) {
        this->bestLapTime = time;
        return true;
    }
    return false;
}

void TrackHandler::resetLap() {
    Serial.println("Lap reset");
    this->raceStarted = true;
    this->startTime = millis();
    this->nextGateIndex = 0;
}

void TrackHandler::startLap() {
    Serial.println("Start lap");
    this->startTime = millis();
    this->resetNextGateIndex();
    this->raceStarted = true;
}

void TrackHandler::stopLap() {
    this->raceStarted = false;
    elapsedTime = (millis() - startTime) / 1000;
    Serial.print("Lap finished in ");
    Serial.print(elapsedTime);
    Serial.println("s");
    // Update last time
    bool newRecord = this->setLapTime(elapsedTime);
    if(newRecord) {
        Serial.println("New record");
        // Gate::beep();
    }
    // Gate::beep();
    this->resetLap();
}

int TrackHandler::addGateToTrack(GateClient *gate) {
    this->trackGates.push_back(gate);
    return this->getTrackGateSize();
}