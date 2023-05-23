#ifndef Leds_H
#define Leds_H
    
class Leds {
  public:
    Leds(int numLeds, int dataPin);
    void setup();
    void blink();
  
  private:
    int numLeds;
    int dataPin; 
};

#endif
