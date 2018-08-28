# Wireless Potentiometer

## About the project

This repository contains the code and schematics for an Arduino-based wireless potentiometer adapter.

Create this gadget to add wireless IR manipulation of a 100k ohm analog potentiometer. 

## Todo

### Software

* InfaredReceiver.ino needs the following:
  * store last command and relay it when #FFFFFFFF repeat command is received

* Status indicator leds?
  * When the device needs a pairing, blink orange with triple pattern
    * wait for up, then confirm, then down, then confirm
    * button to reset pairing? see if bean has room...
  * When the device receives a command, blink green

* Make sure everything is documented

### Hardware

* Document finalized Uno schematic

* Create Lightblue Bean schematic based on Uno
  * Adjust library as necessary
  * _Can we match pins 1:1 or are we going to have device-dependent presets?_

* Assemble Lightblue Bean circuit

* Research powering Bean from speaker circuit

* Create installation document

* Enclose circuit in speaker housing