#pragma once

#include "Arduino.h"
#include <ESPAsyncWebServer.h>
#include "ServerWebController.h"
#include <server/model/enums/ServerMode.h>

#include <server/handlers/HandlerBase.h>
#include <server/handlers/IdleHandler.h>
#include <server/handlers/CalibrationHandler.h>
#include <server/handlers/TrackHandler.h>
#include <server/handlers/RaceHandler.h>
#include <map>

class FpvGateServer {
    public:
        static FpvGateServer& getInstance();
        void setup(AsyncWebServer &webServer) {
            webController.setup(webServer);
        };
        void loop();
        void setMode(ServerMode newMode);
        void gatePassage(int id);
    protected:
        FpvGateServer();
    private:
        static FpvGateServer* instance;
        ServerWebController webController;

        ServerMode mode;
        std::shared_ptr<HandlerBase> currentHandler;
        std::map<ServerMode, std::shared_ptr<HandlerBase>> handlers = {
            {ServerMode::IDLE, std::make_shared<IdleHandler>()},
            {ServerMode::CALIBRATION, std::make_shared<CalibrationHandler>()},
            {ServerMode::TRACK, std::make_shared<TrackHandler>()},
            {ServerMode::RACE, std::make_shared<RaceHandler>()}
        };
};