/*
  Main controller for wireless potentiometer gadget.
*/

#include <arduino.h>
#include <EEPROM.h>
#include "MCP41100.h"
#include "AnalogPot.h"
#include "InfaredReceiver.h"

#define ANALOG_THRESHOLD 51
#define STEP_MODIFIER 20
const int DIGITAL_POT_PIN = 10;
const int ANALOG_POT_PIN = A5;
const int RECEIVER_PIN = 3;
const int LED_PIN= 5;

struct Config {
  Command volumeUpCode;
  Command volumeDownCode;
} config;

const int VOLUME_UP = 1;
const int VOLUME_DOWN = -1;

boolean useDigital = false;
int prevAnalogVolume = 0;
int analogVolume = 0;

int volume = 0;

AnalogPot* analogPot;
InfaredReceiver* infaredReceiver;
MCP41100* digitalPot;

void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  analogPot = new AnalogPot(ANALOG_POT_PIN);
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
  analogVolume = analogPot->read();
  
  // Check if Analog Potentiometer should take precedence over digital
  if (useDigital && isAlphaSignificant(analogVolume, prevAnalogVolume)) {
    useDigital = false;
    Serial.println("Master: ANALOG");
  }

  if (!useDigital) {
    volume = analogVolume;
    prevAnalogVolume = analogVolume;
  } 
  
  const int modifier = getModifierFromCommand();
  
  // Check if Digital should take precedence over analog
  if (modifier != 0) {
    useDigital = true;
    Serial.println("Master: DIGITAL");
    changeDigitalVolume(modifier);
  }
  
  // printVolume();

  delay(50);
  digitalPot->write(map(volume, 0, 1024, 0, 255));
}

int changeDigitalVolume(int alpha) {
  const int newVolume = volume + (alpha * STEP_MODIFIER);

  if (newVolume >= 1023) {
    volume = 1023;
  } else if (newVolume <= 0) {
    volume = 0;
  } else {
    volume = newVolume;
  }
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

void printVolume() {
  Serial.print("Volume (analog / digital): ");
  Serial.print(volume);
  Serial.print(" / ");
  Serial.println(map(volume, 0, 1024, 0, 255));
}

int getModifierFromCommand() {
  const Command results = infaredReceiver->read();

  if (results == config.volumeUpCode) {
    blink(LED_PIN);
    return VOLUME_UP;
  }

  if (results == config.volumeDownCode) {
    blink(LED_PIN);
    return VOLUME_DOWN;
  }

  return 0;
}

boolean isAlphaSignificant(int value, int prevValue) {
  return value < prevValue - ANALOG_THRESHOLD || value > prevValue + ANALOG_THRESHOLD;
}

void blink(int pin) {
  digitalWrite(pin, LOW);
  delay(100);
  digitalWrite(pin, HIGH);
}