/*
  Main controller for wireless potentiometer gadget.
*/

#include <arduino.h>
#include <EEPROM.h>
#include "MCP41100.h"
#include "AnalogPot.h"
#include "InfaredReceiver.h"

const int DIGITAL_POT_PIN = 10;
const int ANALOG_PIN = 5;
const int RECEIVER_PIN = 3;

struct Config {
  Command volumeUpCode;
  Command volumeDownCode;
} config;

const int VOLUME_UP = 1;
const int VOLUME_DOWN = -1;


int volume = 0;

AnalogPot* analogPot;
InfaredReceiver* infaredReceiver;
MCP41100* digitalPot;

void setup() {
  Serial.begin(9600);

  analogPot = new AnalogPot(ANALOG_PIN);
  infaredReceiver = new InfaredReceiver(RECEIVER_PIN);
  digitalPot = new MCP41100(DIGITAL_POT_PIN);

  volume = analogPot->read();

  Config c;

  config = EEPROM.get(0, c);

  if (config.volumeUpCode == 0 || config.volumeDownCode == 0) {
    pair();
  } else {
    printConfiguration();
  }
}

void loop() {
  volume = analogPot->read();
  delay(50);
  Serial.println(volume);
  digitalPot->write(map(volume, 0, 1024, 0, 255));
}

void pair() {
  Serial.println("Before using this device, you'll need to pair your IR remote.\n");

  Serial.println("Let's start by pairing the Volume Up button on your remote. Press it a few times until you see a green light.");
  config.volumeUpCode = (Command) infaredReceiver->registerCommand(VOLUME_UP);

  Serial.println("\nSaving volume up command...\n");
  delay(5000);
  
  Serial.println("Great! Now we'll pair the Volume Down button. Press it a few times until you see a green light.");
  config.volumeDownCode = (Command) infaredReceiver->registerCommand(VOLUME_DOWN);

  EEPROM.put(0, config);
  printConfiguration();

  Serial.println("\n Your remote has been successfully paired. To reset this pairing, press the reset button on your device.\n");
}

void printConfiguration() {
  Serial.print("Volume up: \t");
  Serial.println(config.volumeUpCode);
  
  Serial.print("Volume down: \t");
  Serial.println(config.volumeDownCode);
  Serial.println("\n------------------------\n");
}

}

