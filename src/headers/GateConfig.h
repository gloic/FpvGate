#ifndef GateConfig_H
#define GateConfig_H
/*
 * If DEV_MODE 1 :
 * - wifi will connect to existing network
 * - no "listening" sent to gates *
 * - DEV_IP_STARTER will be used as starter's ip (use by gates in a local network)
 */
#define DEV_MODE 1
#define DEV_IP_STARTER "192.168.0.84"

// Starter
#define PIN_STARTER 15
#define PIN_STARTER_RESET 15

#define PIN_SONIC_SENSOR_TRIGGER 33
#define PIN_SONIC_SENSOR_ECHO 25
#define PIN_SONIC_SENSOR_POT_RANGE 36
#define PIN_SONIC_SENSOR_LED 18

#define PIN_BUZZER 27
#define PIN_STATE_LED 2

#endif