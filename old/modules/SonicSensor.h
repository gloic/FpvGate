#pragma once

#include <NewPing.h>


class SonicSensor {
  public:
    SonicSensor(int triggerPin, int echoPin, int potPin, int ledPin):
      sonar(triggerPin, echoPin, 200),
      potPin(potPin),
      ledPin(ledPin){}
    void setup();
    boolean checkPass();
    void stop();
protected:
private:
    NewPing sonar;

    int potPin;
    int ledPin;
    int thresholdDistance = 0;

    // long duration;
    // float distance;
    // boolean calibrationMode = false;

    long sendPulse();
    void updateThreshold();

    void ledOn() {digitalWrite(ledPin, HIGH);}
    void ledOff() {digitalWrite(ledPin, LOW);}
    ;
};