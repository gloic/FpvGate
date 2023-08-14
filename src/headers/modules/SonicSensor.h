#ifndef SonicSensor_H
#define SonicSensor_H

class SonicSensor {
  public:
    SonicSensor(int triggerPin, int echoPin, int potPin, int ledPin);
    void setup();
    bool checkPass();
    // void setCalibrationMode(bool state) { this->calibrationMode = state;}
  protected:
  
  private:
    int _triggerPin;
    int _echoPin;
    int _potPin;
    int _ledPin;
    int _thresholdDistance = 0;
    long duration;
    float distance;
    bool calibrationMode = false;

    void sendPulse();
    void refreshDistance();

    void ledOn();
    void ledOff();
};

#endif
