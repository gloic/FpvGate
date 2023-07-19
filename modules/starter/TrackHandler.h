#ifndef TrackHandler_H
#define TrackHandler_H

#include "Mode.h"

class TrackHandler {
public:
    TrackHandler() {}

    void setMode(Mode mode);
    Mode getMode();
    bool isTrackMode();
    bool isRaceMode();

private:
    Mode mode;

    bool isMode(Mode mode);
};

#endif TrackHandler_H
