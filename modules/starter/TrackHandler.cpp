#include "TrackHandler.h"

void TrackHandler::setMode(Mode mode) {
    this->mode = mode;
}

Mode TrackHandler::getMode() {
    return this->mode;
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
