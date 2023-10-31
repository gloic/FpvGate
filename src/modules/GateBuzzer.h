#pragma once

class GateBuzzer {
public:
    explicit GateBuzzer(int buzzerpin): 
    buzzerPin(buzzerpin) {}
    void setup();
    void beep();
private:
    int buzzerPin;
};