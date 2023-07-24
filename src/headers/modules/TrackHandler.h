#ifndef TrackHandler_H
#define TrackHandler_H

#include "headers/structs/GateMode.h"

class TrackHandler {
public:
    TrackHandler() {}

    void setMode(GateMode mode);
    bool isTrackMode();
    bool isRaceMode();
    GateMode getMode();

    long getLastLapTime();
    void setLastLapTime(long time);
    long getBestLapTime();
    void setBestLapTime(long time);

    bool setLapTime(long time);

private:
    GateMode mode;
    long lastLapTime;
    long bestLapTime;

    bool isMode(GateMode mode);
};

#endif
