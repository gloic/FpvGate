#pragma once

#include "../structs/GateMode.h"
#include "../structs/GateClient.h"

#include <vector>

class TrackManager {
public:
    TrackManager() {}

    void setTrackMode() { setMode(GateMode::TRACK); }
    void setRaceMode() { setMode(GateMode::RACE); }

    boolean isTrackMode() { return isMode(GateMode::TRACK); }
    boolean isRaceMode() { return isMode(GateMode::RACE); }

    long getLastLapTime() { return lastLapTime; }
    void setLastLapTime(long time) { lastLapTime = time; }
    long getBestLapTime() { return bestLapTime; }
    void setBestLapTime(long time) { bestLapTime = time; }
    long getStartTime() { return startTime; }
    void clearTrackGates() { trackGates.clear(); }

    boolean setLapTime(long time);
    void resetLap();
    void startLap();
    void stopLap();
    int getTrackGateSize() { return trackGates.size(); }
    GateClient &getNextGate() { return trackGates[nextGateIndex]; }
    boolean isNextGate(int gateId) { return getNextGate().id == gateId; }
    boolean hasNextGate() { return nextGateIndex < getTrackGateSize() - 1; }
    void incrementNextGateIndex() { nextGateIndex++; }
    int getNextGateIndex() { return nextGateIndex; }
    void resetNextGateIndex() { nextGateIndex = 0; }
    int addGateToTrack(GateClient &gate);

    boolean isRaceStarted() { return raceStarted; }

private:
    GateMode _mode = GateMode::INIT;
    long lastLapTime = 0;
    long bestLapTime = -1;
    long startTime = 0;
    int nextGateIndex = 0;
    long elapsedTime = 0;
    boolean raceStarted = false;

    std::vector<GateClient> trackGates;

    boolean isMode(GateMode mode) { return _mode == mode; };
    void setMode(GateMode mode) { _mode = mode; };
    GateMode getMode() { return _mode; };
};