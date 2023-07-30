#ifndef StateLed_H
#define StateLed_H

#include <Led.h>

class StateLed {
  public:
    StateLed();
    void setup();
    void loop();
    void setMode(int mode);  
  private:
    int _ledMode;
    Led* _led;
};

#endif
