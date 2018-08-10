/*
  Main controller for wireless potentiometer gardget.
*/

#include <Arduino.h>
#include "AnalogPot.h";

int volume = 0;

AnalogPot analogPot(5);  // input pin for the potentiometer

void setup() {
  Serial.begin(9600);
}

void loop() {
  volume = analogPot.read();
  delay(50);
  Serial.println(volume);
}
