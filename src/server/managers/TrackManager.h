#pragma once
#include <server/model/Track.h>
#include <memory>
#include <server/managers/GateManager.h>

class TrackManager {
    public:
        static TrackManager &getInstance() {
            if (!instance) {
                instance = new TrackManager();
            }
            return *instance;
        }

        Track& getCurrentTrack() { return *track; };
        void addGate(GateClient& gate);

        GateClient& getNextGate() { return track->getNextGate(); }
        void advanceToNextGate() { track->advanceToNextGate(); }

        void clearTrack() { track.reset();};
        bool isTrackEmpty();
        int getTrackSize();
    protected:
        TrackManager() {}
    private:
        static TrackManager* instance;
        std::unique_ptr<Track> track;
};