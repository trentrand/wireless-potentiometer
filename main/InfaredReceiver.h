/*
  InfaredReceiver.h - Library header for reading data using an AX-1838HS Infared Receiver
*/
#ifndef InfaredReceiver_h
#define InfaredReceiver_h

typedef long unsigned int Command; 

#include "IRremote.h"

#define COMMANDS_TO_CONFIRM 3

class IRRecv;

class InfaredReceiver {
  public:
    InfaredReceiver(int pin);
    Command read();
    Command registerCommand(byte command);
    Command getMostFrequentCommand(Command commands[]);
    static int compare(const void * a, const void * b);
  private:
    int _pin;
    decode_results results;
    IRrecv *receiver;
};


#endif

