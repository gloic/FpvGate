#pragma once
#include <Arduino.h>

class StarterEntryPoints{
public:
    static constexpr char const* START_LISTEN = "/api/gate/start";
    static constexpr char const* STOP_LISTEN = "/api/gate/stop";
};