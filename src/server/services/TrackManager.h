#pragma once
#include <server/model/Track.h>
#include <memory>

class TrackManager {
    public: 
        static TrackManager& getInstance(){if(!instance) {instance = new TrackManager();}return *instance;}
        void setCurrentTrack(const Track& track);
        Track& getCurrentTrack();
        void addGate(int id);
        void setStarter(GateClient& starterPtr);
    protected:
        TrackManager(): track(new Track()) {}
    private:
        static TrackManager* instance;
        std::unique_ptr<Track> track;
};