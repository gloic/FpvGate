#pragma once
#include <Arduino.h>

// using namespace std;

class StarterEntryPoints{
public:
    static const String START_LISTEN;
    static const String STOP_LISTEN;
};
const String StarterEntryPoints::START_LISTEN = "/api/gate/start";
const String StarterEntryPoints::STOP_LISTEN = "/api/gate/stop";