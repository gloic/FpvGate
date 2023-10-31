#pragma once

class GateBuzzer {
public:
    GateBuzzer(int buzzerpin): 
    buzzerPin(buzzerpin) {}
    void setup();
    void beep();
private:
    int buzzerPin;
};