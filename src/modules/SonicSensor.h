#pragma once

class SonicSensor {
  public:
    SonicSensor(int triggerPin, int echoPin, int potPin, int ledPin);
    void setup();
    boolean checkPass();
    void stop();
    // void setCalibrationMode(boolean state) { this->calibrationMode = state;}
protected:
private:
    int triggerPin;
    int echoPin;
    int potPin;
    int ledPin;
    int _thresholdDistance = 0;
    long duration;
    float distance;
    boolean calibrationMode = false;

    void sendPulse();
    void refreshDistance();

    void ledOn();
    void ledOff();
};