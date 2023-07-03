#ifndef LedStatut_H
#define LedStatut_H

class LedStatut {
  public:
    LedStatut();
    void setup();
    void loop();
    void setMode(int mode);  
  private:
    int ledMode;
};

#endif
