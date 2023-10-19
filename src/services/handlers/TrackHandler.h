#ifndef TrackHandler_H
#define TrackHandler_H

#include "../../structs/GateMode.h"
#include "../../structs/GateClient.h"

#include <vector>

class TrackHandler {
public:
    TrackHandler() {}

    void setTrackMode() {this->setMode(GateMode::TRACK);}
    void setRaceMode() {this->setMode(GateMode::RACE);}
    
    bool isTrackMode() {return isMode(GateMode::TRACK);}
    bool isRaceMode() {return isMode(GateMode::RACE);}

    long getLastLapTime() {return this->lastLapTime;}
    void setLastLapTime(long time) {this->lastLapTime = time;}
    long getBestLapTime() {return this->bestLapTime;}
    void setBestLapTime(long time) {this->bestLapTime = time;}
    long getStartTime() {return this->startTime;}
    void clearTrackGates() {this->trackGates.clear();}

    bool setLapTime(long time);
    void resetLap();
    void startLap();
    void stopLap();
    int getTrackGateSize() {return this->trackGates.size();}
    GateClient* getNextGate() {return this->trackGates[nextGateIndex];}
    bool isNextGate(int gateId) {return this->getNextGate()->id == gateId;}
    bool hasNextGate() {return nextGateIndex < this->getTrackGateSize() - 1;}
    void incrementNextGateIndex() {nextGateIndex++;}
    int getNextGateIndex() {return nextGateIndex;}
    void resetNextGateIndex() {nextGateIndex = 0;}
    int addGateToTrack(GateClient *gate);

    bool isRaceStarted() { return this->raceStarted;}

private:
    GateMode _mode = GateMode::INIT;
    long lastLapTime;
    long bestLapTime = -1;
    long startTime = 0;
    int nextGateIndex = 0;
    long elapsedTime = 0;
    bool raceStarted = false;

    std::vector<GateClient*> trackGates;

    bool isMode(GateMode mode) {return this->_mode == mode;};
    void setMode(GateMode mode) {this->_mode = mode;};
    GateMode getMode() {return this->_mode;};
};

#endif
