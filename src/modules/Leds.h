#pragma once

class Leds {
  public:
    Leds(int numLeds, int dataPin);
    void setup();
    void blink();
  
  private:
    int numLeds;
    int dataPin; 
};