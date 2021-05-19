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



unsigned char byteOne;
unsigned char byteTwo;

//  - TODO -  Ask Asger about this -

struct Command *commandPointer = &command;
unsigned char *byteOnePointer = &byteOne;
unsigned char *byteTwoPointer = &byteTwo;



void setup()
{
    Serial.begin(9600);
}

void loop()
{

    byteOne = 50; 
    byteTwo = SPEED1;
    
    // TODO -- Ask Asger --
    readCommand(&command, "PRE");

    
    // readCommand(commandPointer, "PRE");
    // changeCommand(commandPointer, byteOne, byteTwo);
    changeCommand(&command, byteOne, byteTwo);
    delay(500);
    
    byteOne = 60; 
    byteTwo = SPEED6;

    readCommand(&command, "POST");
    changeCommand(&command, byteOne, byteTwo);

    
    delay(500);
}
