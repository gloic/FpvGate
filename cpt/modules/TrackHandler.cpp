#include "../headers/TrackHandler.h"

void TrackHandler::setMode(Mode mode) {
    this->mode = mode;
}

bool TrackHandler::isTrackMode() {
    return isMode(Mode::TRACK);
}

bool TrackHandler::isRaceMode() {
    return isMode(Mode::RACE);
}

bool TrackHandler::isMode(Mode mode) {
    return this.mode == mode;
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
 * Update lastTime and bestLapTime is needed
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
