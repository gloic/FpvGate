#pragma once
#include <server/model/Track.h>
#include <memory>
#include <server/services/GateManager.h>

class TrackManager {
    public: 
        static TrackManager& getInstance(){if(!instance) {instance = new TrackManager();}return *instance;}
        Track& getCurrentTrack() {return *track;};
        void addGate(GateClient& gate);
        void setStarter(GateClient& starter);

        GateClient& getNextGate() { return track->getNextGate();}
        void advanceToNextGate() {track->advanceToNextGate();}
        GateClient& getStarter() {return track->getStarter();}
    protected:
        TrackManager() {}
    private:
        static TrackManager* instance;
        std::unique_ptr<Track> track;
};