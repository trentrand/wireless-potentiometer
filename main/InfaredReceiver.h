/*
  InfaredReceiver.h - Library header for reading data using an AX-1838HS Infared Receiver
*/
#ifndef InfaredReceiver_h
#define InfaredReceiver_h

typedef long unsigned int Command; 

#include "IRremote.h"

class IRRecv;
class InfaredReceiver {
  public:
    InfaredReceiver(int pin);
    Command read();
  private:
    int _pin;
    decode_results results;
    IRrecv *receiver;
};


#endif

