#ifndef SonicSensor_H
#define SonicSensor_H

class SonicSensor {
  public:
    SonicSensor(int triggerPin, int echoPin);
    void setup();
    bool checkPass();
    
  protected:
  
  private:
    int triggerPin;
    int echoPin;
    int thresholdDistance;
};

#endif
