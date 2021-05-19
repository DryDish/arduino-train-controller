#include "definitions.h"
#include "command.h"
#include "changeCommand.h"
#include "readCommand.h"


struct Command command =
{
        PREAMBLE,           // preamble part 2
        SEPARATOR,          // -- Separating bit --
        BLANK_BYTE_ONE,     // Engine Number
        SEPARATOR,          // -- Separating bit --
        BLANK_BYTE_TWO,     // byteTwo
        SEPARATOR,          // -- Separating bit --
        command.byteOne ^ command.byteTwo,  // Checksum
        END_OF_MESSAGE        // --- End of message bit ---
};
Command *commandPointer = &command;

unsigned char byteOne;
unsigned char *byteOnePointer = &byteOne;
unsigned char byteTwo;
unsigned char *byteTwoPointer = &byteTwo;


void setup()
{
    Serial.begin(9600);
}

void loop()
{

    byteOne = 50; 
    byteTwo = SPEED1;
    
    readCommand(commandPointer, "PRE");
    changeCommand(commandPointer, byteOnePointer, byteTwoPointer);
    delay(500);
    
    
    byteOne = 60; 
    byteTwo = SPEED6;

    readCommand(commandPointer, "POST");
    changeCommand(commandPointer, byteOnePointer, byteTwoPointer);

    
    delay(500);
}
