/*
  AnalogPot.cpp - Library for reading an analog potentiometer

  Default Pinout:
  | PIN 1: PA0   >  ? (Potentiometer A )
  | PIN 2: PW0   >  ? (Potentiometer Wiper)
  | PIN 3: PB0   >  ? (Potentiometer B)
  ————————————————————
*/

#include "Arduino.h"
#include "AnalogPot.h"

AnalogPot::AnalogPot(int pin)
{
  pinMode(pin, OUTPUT); // input pin for the potentiometer
  _pin = pin; 
}

char AnalogPot::read() {
  return analogRead(_pin);
}