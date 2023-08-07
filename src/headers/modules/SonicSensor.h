#ifndef SonicSensor_H
#define SonicSensor_H

class SonicSensor {
  public:
    SonicSensor(int triggerPin, int echoPin, int potPin);
    void setup();
    bool checkPass();
    
  protected:
  
  private:
    int _triggerPin;
    int _echoPin;
    int _potPin;
    int _thresholdDistance;

    void refreshDistance();
};

#endif
