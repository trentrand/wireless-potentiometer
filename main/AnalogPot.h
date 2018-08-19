/*
  AnalogPot.h - Library header for reading an analog potentiometer
*/
#ifndef AnalogPot_h
#define AnalogPot_h

class AnalogPot {
  public:
    AnalogPot(int pin);
    int read();
  private:
    int _pin;
};

#endif

