/*
  MCP41100.cpp - Library header for MCP41100 (digital potentiometer)
*/
#ifndef MCP41100_h
#define MCP41100_h

class MCP41100 {
  public:
    MCP41100(int pin);
    void adjustResistance(char analogValue);
    void write(char analogValue);
  private:
    int _pin;
};

#endif

