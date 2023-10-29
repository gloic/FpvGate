#pragma once

#include "../structs/LedMode.h"
#include "../structs/LedColor.h"

class StateLed {
  public:
    StateLed();
    // StateLed(int pinRed, int pinGreen, int pinBlue);
    void setup();
    void loop();
    void setMode(LedMode mode);
    void setColor(int red, int green, int blue);
    //LedMode getMode();
    //LedColor getColor();

  private:
    int _pinRed;
    int _pinGreen;
    int _pinBlue;
    LedMode _ledMode;
    int _red;
    int _green;
    int _blue;
};