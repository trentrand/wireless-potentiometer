/*
  Main controller for wireless potentiometer gadget.
*/

#include <arduino.h>
#include "MCP41100.h"
#include "AnalogPot.h"
#include "InfaredReceiver.h"

const int DIGITAL_POT_PIN = 10;
const int ANALOG_PIN = 5;
const int RECEIVER_PIN = 3;

int volume = 0;

AnalogPot* analogPot;
InfaredReceiver* infaredReceiver;
MCP41100* digitalPot;

void setup() {
  Serial.begin(9600);

  analogPot = new AnalogPot(ANALOG_PIN);
  infaredReceiver = new InfaredReceiver(RECEIVER_PIN);
  digitalPot = new MCP41100(DIGITAL_POT_PIN);
}

void loop() {
  volume = analogPot->read();
  delay(50);
  Serial.println(volume);
  digitalPot->write(map(volume, 0, 1024, 0, 255));
}
