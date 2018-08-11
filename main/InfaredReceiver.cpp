/*
  InfaredReceiver.cpp - Library for reading data using an AX-1838HS Infared Receiver

  Default Pinout:
  | PIN 1: ?   >  ? (?)
  ————————————————————
*/

#include "arduino.h"
#include "IRremote.h"
#include "InfaredReceiver.h"

InfaredReceiver::InfaredReceiver(int pin) {
  _pin = pin;
  receiver = new IRrecv(_pin);
  receiver->enableIRIn();
}

char InfaredReceiver::read() {
  if (receiver->decode(&(this->results))) {
    receiver->resume(); // Receive the next value
    return results.value;
  }
  delay(100);
}