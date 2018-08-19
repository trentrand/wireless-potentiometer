# Wireless Potentiometer

## About the project

This repository contains the code and schematics for an Arduino-based wireless potentiometer adapter.

Create this gadget to add wireless IR manipulation of a 100k ohm analog potentiometer. 

## Todo

### Software

* InfaredReceiver.ino needs the following:
  * utility to read next input, use it to pair remote
  * store pairing in non volatile memory, persist boot
  * callback pattern for IR communication?

* Utilize InfaredReceiver in main

* Status indicator leds?
  * When the device needs a pairing, blink orange with triple pattern
    * wait for up, then confirm, then down, then confirm
    * button to reset pairing? see if bean has room...
  * When the device receives a command, blink green

* Setup final behavior
  * AnalogPot overrides InfaredReceiver wiper value
  * Infared communication increments / decrements wiper value

* Make sure everythings documented

### Hardware

* Document finalized Uno schematic

* Create Lightblue Bean schematic based on Uno
  * Adjust library as necessary
  * _Can we match pins 1:1 or are we going to have device-dependent presets?_

* Assemble Lightblue Bean circuit

* Research powering Bean from speaker circuit

* Create installation document

* Enclose circuit in speaker housing

* Design PCB