#ifndef TRAIN_CODE_C_CHANGE_COMMAND
#define TRAIN_CODE_C_CHANGE_COMMAND

// for interrupts() and noInterrupts()
#include <Arduino.h> 
#include "command.h"

void changeCommandTrain(struct Command *command, unsigned char *byteOne, unsigned char *byteTwo);
void changeCommandAccessory(struct Command *command, unsigned short address, unsigned char power, unsigned char direction);

#endif // TRAIN_CODE_C_CHANGE_COMMAND
