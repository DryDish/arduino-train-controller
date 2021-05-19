#include "changeCommand.h"

// this HAS to be a cpp file in order for interrupts() and noInterrupts() to work, but code is written in C first.
void changeCommand(struct Command *command, unsigned char byteOne, unsigned char byteTwo)
{
    noInterrupts();
    command -> byteOne = byteOne;
    command -> byteTwo = byteTwo;
    command -> checksum = byteOne ^ byteTwo;
    interrupts();
}