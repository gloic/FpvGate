#pragma once

#include "Arduino.h"
#include <ESPAsyncWebServer.h>
#include "ServerRestController.h"
#include <server/model/enums/ServerMode.h>

#include <modules/LcdDisplay.h>
#include <server/handlers/HandlerBase.h>
#include <server/handlers/IdleHandler.h>
#include <server/handlers/CalibrationHandler.h>
#include <server/handlers/TrackHandler.h>
#include <server/handlers/RaceHandler.h>
#include <server/managers/LcdManager.h>

#include <map>

class FpvGateServer {
    public:
        static FpvGateServer& getInstance();

        void setup(AsyncWebServer &webServer) {
            webController.setup(webServer);
            setMode(ServerMode::IDLE);
        };
        void onGatePassage(int id);
        void reset() {setMode(ServerMode::IDLE);};
        void setTrackMode() {setMode(ServerMode::TRACK);};
        void setCalibrationMode() {setMode(ServerMode::CALIBRATION);};

        void selectNextMode();
        void confirmMode();

    private:
        static FpvGateServer* instance;
        FpvGateServer() : lcdManager(LcdManager::getInstance()) {};
        ServerRestController webController;
        ServerMode mode;
        LcdManager lcdManager;
        std::shared_ptr<HandlerBase> currentHandler;
        std::map<ServerMode, std::shared_ptr<HandlerBase>> handlers = {
            {ServerMode::IDLE, std::make_shared<IdleHandler>()},
            {ServerMode::CALIBRATION, std::make_shared<CalibrationHandler>()},
            {ServerMode::TRACK, std::make_shared<TrackHandler>()},
            {ServerMode::RACE, std::make_shared<RaceHandler>()},
        };
        void setMode(ServerMode newMode);
        void switchHandler(ServerMode newMode);
        // void refreshDisplay();


        static const ServerMode modes[4];
        int nextModeIdx = 0;
};