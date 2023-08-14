#ifndef SonicSensor_H
#define SonicSensor_H

class SonicSensor {
  public:
    SonicSensor(int triggerPin, int echoPin, int potPin, int ledPin);
    void setup();
    bool checkPass();

    
  protected:
  
  private:
    int _triggerPin;
    int _echoPin;
    int _potPin;
    int _ledPin;
    int _thresholdDistance;
    long duration;
    float distance;
    void sendPulse();
    void refreshDistance();

    void ledOn();
    void ledOff();
};

#endif
