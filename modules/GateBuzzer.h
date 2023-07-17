#ifndef GateBuzzer_H
#define GateBuzzer_H
    
class GateBuzzer {
  public:
    GateBuzzer(int buzzerpin);
    void setup();
    void beep();
  private:
    int _buzzerPin;
};
#endif