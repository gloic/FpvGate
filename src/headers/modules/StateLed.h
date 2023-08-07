#ifndef StateLed_H
#define StateLed_H

#include "../structs/LedMode.h"
#include "../structs/LedColor.h"

class StateLed {
  public:
    StateLed();
    // StateLed(int pinRed, int pinGreen, int pinBlue);
    void setup();
    void loop();
    void setMode(LedMode mode);
    void setColor(uint8_t red, uint8_t green, uint8_t blue);
    //LedMode getMode();
    //LedColor getColor();

  private:
    int _pinRed;
    int _pinGreen;
    int _pinBlue;
    LedMode _ledMode;
    uint8_t _red;
    uint8_t _green;
    uint8_t _blue;
};

#endif
