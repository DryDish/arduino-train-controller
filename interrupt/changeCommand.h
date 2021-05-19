#ifndef TRAIN_CODE_C_CHANGE_COMMAND
#define TRAIN_CODE_C_CHANGE_COMMAND

// for interrupts() and noInterrupts()
#include <Arduino.h> 
#include "command.h"

void changeCommand(struct Command *command, unsigned char *byteOne, unsigned char *byteTwo);

#endif // TRAIN_CODE_C_CHANGE_COMMAND
