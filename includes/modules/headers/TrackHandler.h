#ifndef TrackHandler_H
#define TrackHandler_H

#include "../../structs/Mode.h"

class TrackHandler {
public:
    TrackHandler() {}

    void setMode(Mode mode);
    bool isTrackMode();
    bool isRaceMode();

    long getLastLapTime();
    void setLastLapTime(long time);
    long getBestLapTime();
    void setBestLapTime(long time);

    bool setLapTime(long time);

private:
    Mode mode;
    long lastLapTime;
    long bestLapTime;

    bool isMode(Mode mode);
};

#endif TrackHandler_H
