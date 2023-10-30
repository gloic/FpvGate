#pragma once

/*
 * If DEV_MODE 1 :
 * - wifi will connect to existing network
 * - no "listening" sent to gates
 * - DEV_IP_STARTER will be used as starter's ip (used by gates in a local network)
 */
#define DEV_MODE 0
#define DEV_IP_STARTER "192.168.0.84"
#define DEV_MOCK_PORT_WS "8080"

// Starter
#define PIN_STARTER 15
#define PIN_STARTER_RESET 15

#define PIN_SONIC_SENSOR_TRIGGER 33
#define PIN_SONIC_SENSOR_ECHO 25
#define PIN_SONIC_SENSOR_POT_RANGE 36
#define PIN_SONIC_SENSOR_LED 18

#define PIN_BUZZER 27
#define PIN_STATE_LED 2


// Gate
constexpr bool GATE_DEFAULT_CONTINUE_LISTENING = true;