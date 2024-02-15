#include "TimerService.h"
#include <sys/time.h>

TimerService* TimerService::instance = nullptr;

long currentTime() {
   struct timeval tv;
   gettimeofday(&tv, NULL);
   return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void TimerService::start() {
   startTime = currentTime();
}

void TimerService::stop() {
   if (isRunning()) {
       long endTime = currentTime();
       lastLapTime = endTime - startTime;
       startTime = 0;
       if (bestLapTime < 0 || lastLapTime < bestLapTime) {
           bestLapTime = lastLapTime;
       }
   }
}

long TimerService::getLastLapTime() {
   return lastLapTime;
}

long TimerService::getBestLapTime() {
   return bestLapTime;
}

bool TimerService::isRunning() {
   return startTime > 0;
}