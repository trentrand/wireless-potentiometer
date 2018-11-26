# Wireless Potentiometer

## About the project

This repository contains the code and schematics for an Arduino-based wireless potentiometer adapter.

Create this gadget to add wireless IR manipulation of a 100k ohm analog potentiometer. 

## Project Breakdown

### Software

* Pairing mode for pairing your infared controller's volume up/down commands to this gadget.
* Persists paired commands to EEPROM for saving between reboots.
* Maintains precedence between analog / digital operation
 * Allows user to modify volume using both the analog potentiometer and/or an IR remote.

### Hardware

* Arduino device 
* MCP41100 digital potentiometer
* 100k analog potentiometer
