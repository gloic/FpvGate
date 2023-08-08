#include "headers/modules/TrackHandler.h"

#include <Arduino.h>
#include "headers/structs/GateMode.h"


// unsigned long startTime = 0;
unsigned long elapsedTime = 0;
int nextGateIndex = -1;

void TrackHandler::setMode(GateMode mode) {
    this->_mode = mode;
}

bool TrackHandler::isTrackMode() {
    return isMode(GateMode::TRACK);
}

bool TrackHandler::isRaceMode() {
    return isMode(GateMode::RACE);
}

bool TrackHandler::isMode(GateMode mode) {
    return this->_mode == mode;
}

GateMode TrackHandler::getMode() {
    return this->_mode;
}

long TrackHandler::getLastLapTime() {
    return this->lastLapTime;
}

void TrackHandler::setLastLapTime(long time) {
    this->lastLapTime = time;
}

long TrackHandler::getBestLapTime() {
    return this->bestLapTime;
}

void TrackHandler::setBestLapTime(long time) {
    this->bestLapTime = time;
}

/**
 * Update lastTime and bestLapTime if needed
 * @param time
 * @return true if bestLapTime updated too.
 */
bool TrackHandler::setLapTime(long time) {
    this->lastLapTime = time;
    if (this->lastLapTime < this->bestLapTime) {
        this->bestLapTime = time;
        return true;
    }
    return false;
}

void TrackHandler::clearTrackGates() {
    this->trackGates.clear();
}

void TrackHandler::resetLap() {
    Serial.println("Lap reset");
    startTime = millis();
    //elapsedTime = 0;
    nextGateIndex = 0;
    
}

void TrackHandler::startLap() {
    Serial.println("Start lap");
    startTime = millis();
    nextGateIndex++;
}

void TrackHandler::stopLap() {
    elapsedTime = (millis() - startTime) / 1000;
    Serial.print("Lap finished in ");
    Serial.print(elapsedTime);
    Serial.println("s");

//     Update last time
    bool newRecord = this->setLapTime(elapsedTime);
    if(newRecord) {
        Serial.println("New record");
        // Gate::beep();
    }
    // Gate::beep();
    this->resetLap();
}

long TrackHandler::getStartTime() {
    return this->startTime;
}

int TrackHandler::getTrackGateSize() {
    return this->trackGates.size();
}

GateClient* TrackHandler::getNextGate() {
    return &this->trackGates[nextGateIndex];
}

bool TrackHandler::hasNextGate() {
    return nextGateIndex < this->getTrackGateSize() - 1;
}

void TrackHandler::incrementNextGateIndex() {
    nextGateIndex++;
}

void TrackHandler::addGateToTrack(GateClient &gate) {
    this->trackGates.push_back(gate);
}