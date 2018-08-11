/*
  Main controller for wireless potentiometer gardget.
*/

#include <arduino.h>
#include "MCP41100.h"
#include "AnalogPot.h"
#include "InfaredReceiver.h"

const int DIGITAL_POT_PIN = 10;
const int ANALOG_PIN = 5;
const int RECEIVER_PIN = 3;

int volume = 0;

MCP41100 digitalPot(DIGITAL_POT_PIN);
AnalogPot analogPot(ANALOG_PIN);
InfaredReceiver irReceiver(RECEIVER_PIN);

void setup() {
  Serial.begin(9600);
}

void loop() {
  volume = analogPot.read();
  delay(50);
  Serial.println(volume);
  digitalPot.write(map(volume, 0, 1024, 0, 255));
}
