#pragma once

class TimerService {
    public:
    static TimerService &getInstance() {
            if (!instance) {
                instance = new TimerService();
            }
            return *instance;
        }

    protected:
        TimerService() {}
        void start();
        void stop();
        long getLastLapTime();
        long getBestLapTime();
        bool isRunning();
        
    private:
        static TimerService* instance;

        long lastLapTime = 0;
        long bestLapTime = -1;
        long startTime = 0;
};