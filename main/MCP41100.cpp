/*
  MCP41100.cpp - Library for MCP41100 (digital potentiometer)

  Default Pinout:
  | PIN 1: CS    >  D10 (Chip Select)
  | PIN 2: SCLK  >  D13 (Serial Clock )
  | PIN 3: SI    >  D11 (Serial Data Input )
  | PIN 4: V     >  GND (Ground)
  | PIN 5: PA0   >  P0A (Potentiometer A )
  | PIN 6: PW0   >  P0W (Potentiometer Wiper)
  | PIN 7: PB0   >  P0B (Potentiometer B)
  | PIN 8: Vdd   >  VCC (5V)
  ————————————————————
*/

#include "MCP41100.h"
#include "SPI.h"

byte address = 0x11;
int CS_PIN = 10; // LOW = receive commands from SI_PIN
int POT_PIN = 5; // input pin for the potentiometer

MCP41100::MCP41100(int pin = CS_PIN) {
  pinMode(pin, OUTPUT); // set the SPI CS pin as output
  _pin = pin;
  
  SPI.begin();

  adjustResistance(0x00); // adjust max resistance
  adjustResistance(0x80); // adjust wiper to midpoint
  adjustResistance(0xFF); // adjust min resistance
  
}

void MCP41100::adjustResistance(char analogValue) {
  write(analogValue);
  delay(1000);
}

void MCP41100::write(char value) {
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(CS_PIN, HIGH);
}