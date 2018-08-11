/*
  Main controller for wireless potentiometer gardget.
*/

#include <arduino.h>
#include "MCP41100.h"
#include "AnalogPot.h"

int volume = 0;

MCP41100 digitalPot(10); // LOW = receive commands from SI_PIN
AnalogPot analogPot(5);  // input pin for the potentiometer

void setup() {
  Serial.begin(9600);
}

void loop() {
  volume = analogPot.read();
  delay(50);
  Serial.println(volume);
  digitalPot.write(map(volume, 0, 1024, 0, 255));
}
