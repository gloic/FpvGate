#include "RaceHandler.h"

void RaceHandler::begin() {
    /*
        From a TRACK:
            send listen to Starter (stop)
            once finished, restart
            
        when reset, restart track
    */
}

void RaceHandler::end() {
    // send listen/stop to all
}

void RaceHandler::gatePassage(int id) {
    // send listen to next gate etc...
    // once finished, restart
}