#include "changeCommand.h"

// this HAS to be a cpp file in order for interrupts() and noInterrupts() to work, but code is written in C first.
void changeCommand(struct Command *command, unsigned char *byteOne, unsigned char *byteTwo)
{
    // delay needed to ensure the ISR sequence is triggered in time
    // Anything lower than 6 will occasionally miss the changed bytes
    // If issues arise increase it to 7 or 8
    delay(6);
    noInterrupts();
    command -> byteOne = *byteOne;
    command -> byteTwo = *byteTwo;
    command -> checksum = *byteOne ^ *byteTwo;
    interrupts();
}
