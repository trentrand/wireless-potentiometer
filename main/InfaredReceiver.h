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
    static int comparator(const void *cmp1, const void *cmp2);
    Command getMostFrequentCommand(Command commands[]);
  private:
    int _pin;
    decode_results results;
    IRrecv *receiver;
};


#endif

