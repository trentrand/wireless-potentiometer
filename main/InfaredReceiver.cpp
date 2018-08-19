/*
  InfaredReceiver.cpp - Library for reading data using an AX-1838HS Infared Receiver

  Default Pinout:
  | PIN 1: ?   >  ? (?)
  ————————————————————
*/

#include "arduino.h"
#include "IRremote.h"
#include "InfaredReceiver.h"

InfaredReceiver::InfaredReceiver(int pin) {
  _pin = pin;

  receiver = new IRrecv(_pin);
  receiver->enableIRIn();
}

Command InfaredReceiver::read() {
  if (receiver->decode(&results)) {
    receiver->resume(); // Receive the next value
    return results.value;
  }

  delay(100);
  return -1; // no command received, don't register this read.
}

Command InfaredReceiver::registerCommand(byte command) {
  Command commandsReceived[COMMANDS_TO_CONFIRM];

  for (byte count = 0; count < COMMANDS_TO_CONFIRM;) {
    Command command = read();

    if (command != REPEAT && command != -1) {
      Serial.print("Received potential command: ");
      Serial.println(command, DEC);

      commandsReceived[count] = command;
      count++;
    }
  }

  return getMostFrequentCommand(commandsReceived);
}

static int InfaredReceiver::comparator(const void *cmp1, const void *cmp2) {
  Command a = *((Command *)cmp1);
  Command b = *((Command *)cmp2);
  return b - a;
}

Command InfaredReceiver::getMostFrequentCommand(Command commands[]) {
  Command prevCommand = commands[0]; // 0
  byte currentCount = 1; // c1 c2

  Command mostFrequentCommand;
  byte maxCount;

  qsort(commands, COMMANDS_TO_CONFIRM, sizeof(commands[0]), comparator);


  for (byte i = 1; i < COMMANDS_TO_CONFIRM; i++) {
    if (commands[i] == prevCommand) {
      currentCount++;
    } else {
      if (currentCount > maxCount) {
        mostFrequentCommand = prevCommand;
        maxCount = currentCount;
      }

      prevCommand = commands[i];
      currentCount = 0;
    }
  }

  return mostFrequentCommand;
}


