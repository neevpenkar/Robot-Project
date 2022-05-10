#ifndef Motor_h
#define Motor_h
#include "Arduino.h"


class Motor {
  public:
    Motor (byte direction_pin, byte signal_pin);
    void drive(int val);
    
  private:
  byte dir_pin, sig_pin;
};

class InfraRed {
  public:
    String type;
    int pin;
    
    InfraRed(int sensor_pin, String _type);
    int reading();
    int TimedaverageFunction();
    void setBias(int bias);
  private:
  int Cbias; // Calibrated bias
};
#endif
