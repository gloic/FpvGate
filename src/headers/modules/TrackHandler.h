#ifndef TrackHandler_H
#define TrackHandler_H

#include "headers/structs/GateMode.h"
#include <vector>
#include "headers/structs/GateClient.h"

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
    long getStartTime();

    bool setLapTime(long time);
    void clearTrackGates();
    void resetLap();
    void startLap();
    void stopLap();
    long getStartTime();
    int getTrackGateSize();
    GateClient& getNextGate();
    bool hasNextGate();
    void incrementNextGateIndex();
    void addGateToTrack(GateClient *gate);

private:
    GateMode _mode;
    long lastLapTime;
    long bestLapTime;
    long startTime;
    
    // Vector containing gates for track mode
    std::vector <GateClient> trackGates;

    bool isMode(GateMode mode);
};

#endif
