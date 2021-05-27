#include "readCommand.h"

// this HAS to be a cpp file in order for Serial to work, but code is written in C first.


// --- Does this benefit from being a pointer? should i pass by value? ---
void readCommand(struct Command *commandPointer, const char *prefix)
{
    if (commandPointer->byteOne != 0)
    {
        Serial.print(prefix);
        Serial.print(" < byteOne: ");
        Serial.print(commandPointer -> byteOne);
        Serial.print(" byteTwo: ");
        Serial.print(commandPointer -> byteTwo);
        Serial.print(" checksum: ");
        Serial.print(commandPointer -> checksum);
        Serial.println(" >");
    }
}
