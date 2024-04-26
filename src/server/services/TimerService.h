#pragma once

class TimerService {
    public:
        static TimerService &getInstance() {
            if (!instance) {
                instance = new TimerService();
            }
            return *instance;
        }

        void start();
        void stop();
        long getLastLapTime();
        long getBestLapTime();
        bool isRunning();
        
    protected:
        TimerService() {}
        
    private:
        static TimerService* instance;

        long lastLapTime = 0;
        long bestLapTime = -1;
        long startTime = 0;
};