#include "headers/modules/TrackHandler.h"

#include "headers/structs/GateMode.h"

void TrackHandler::setMode(GateMode mode) {
    this->mode = mode;
}

bool TrackHandler::isTrackMode() {
    return isMode(GateMode::TRACK);
}

bool TrackHandler::isRaceMode() {
    return isMode(GateMode::RACE);
}

bool TrackHandler::isMode(GateMode mode) {
    return this->mode == mode;
}

GateMode TrackHandler::getMode() {
    return this->mode;
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
