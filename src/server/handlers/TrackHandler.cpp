#include "TrackHandler.h"

void TrackHandler::begin() {
    // Send listen/start to all gate with stop
    // wait to receive /pass from gates
    // when first gate passed, send listen with stop to starter
    /*
    build track : 
        TRACK
            id
            // label
            StarterClient
            vector<GatesClient>

            timer
            nbLap
            best lap
            last lap
    */
}

void TrackHandler::end() {
    // Send listen/stop to starter
}