#pragma once

class GateBuzzer {
public:
    GateBuzzer(int buzzerpin);

    void setup();

    void beep();

private:
    int _buzzerPin;
};