#pragma once

#include "Arduino.h"
#include <ESPAsyncWebServer.h>
#include "ServerRestController.h"
#include <server/model/enums/ServerMode.h>

#include <server/handlers/HandlerBase.h>
#include <server/handlers/IdleHandler.h>
#include <server/handlers/CalibrationHandler.h>
#include <server/handlers/TrackHandler.h>
#include <server/handlers/RaceHandler.h>
#include <map>

class FpvGateServer {
    public:
        static FpvGateServer& getInstance(){if (!instance) {instance = new FpvGateServer();} return *instance;};
        void setup(AsyncWebServer &webServer) {
            webController.setup(webServer);
        };
        void onGatePassage(int id);
        void reset() {setMode(ServerMode::IDLE);};
        void setTrackMode() {setMode(ServerMode::TRACK);};
        void setCalibrationMode() {setMode(ServerMode::CALIBRATION);};
    protected:
        FpvGateServer(){};
    private:
        static FpvGateServer* instance;
        ServerRestController webController;
        ServerMode mode;
        std::shared_ptr<HandlerBase> currentHandler;
        std::map<ServerMode, std::shared_ptr<HandlerBase>> handlers = {
            {ServerMode::IDLE, std::make_shared<IdleHandler>()},
            {ServerMode::CALIBRATION, std::make_shared<CalibrationHandler>()},
            {ServerMode::TRACK, std::make_shared<TrackHandler>()},
            {ServerMode::RACE, std::make_shared<RaceHandler>()},
        };
        void setMode(ServerMode newMode);
};