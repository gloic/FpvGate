#pragma once

/*
 * If DEV_MODE 1 :
 * - wifi will connect to existing network
 * - no "listening" sent to gates
 * - DEV_IP_STARTER will be used as starter's ip (used by gates in a local network)
 */

#define DEV_MODE                    0
#define DEV_IP_STARTER              "192.168.0.84"
#define DEV_MOCK_PORT_WS            "8080"
#define DEV_MUTE_BUZZER             true

// Starter
#define PIN_STARTER                 15
#define PIN_STARTER_RESET           15

// Sonic sensor
#define PIN_SONIC_SENSOR_POT_RANGE  36
#define PIN_SONIC_SENSOR_TRIGGER    33
#define PIN_SONIC_SENSOR_ECHO       25
#define PIN_SONIC_SENSOR_LED        18
#define PIN_STATE_LED               2

// Buzzer
#define PIN_BUZZER                  27

// Leds
#define PIN_STRIP_LEDS              14
#define NUM_LEDS                    20

// Menu buttons
#define PIN_MENU_UP                 32
#define PIN_MENU_OK                 35
#define PIN_MENU_DOWN               34 // not used
#define PIN_MENU_CANCEL             32 // not used

// Lcd display
#define PIN_SDA                     21
#define PIN_SCL                     22
#define PIN_OLED_RESET              -1          // -1 if sharing ESP32 reset pin
#define SCREEN_ADDRESS              0x3C
#define SCREEN_WIDTH                128
#define SCREEN_HEIGHT               64

// Gate
constexpr bool GATE_DEFAULT_CONTINUE_LISTENING = true;