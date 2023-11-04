#pragma once
#include <server/model/Track.h>
#include <memory>

class TrackManager {
    public: 
        static TrackManager& getInstance();
        void setCurrentTrack(const Track& track);
        Track& getCurrentTrack();
        void addGate(int id);
    protected:
        TrackManager();
    private:
        static TrackManager* instance;
        std::unique_ptr<Track> currentTrack;
};