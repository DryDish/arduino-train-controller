#include <stdio.h>
//#include "readFromStruct.h"
#include "definitions.h"
#include "instruction.h"
#include "write.h"
#include "writeToTrain.h"


#define ENGINE_NUMBER 11
#define COMMAND HARDSTOP


#define ACTIVE_PIN_A 4
#define ACTIVE_PIN_B 0
#define ACTIVE_PIN_C 0

void readStructData(struct Instruction instruction);

struct Instruction blankInstruction =
{
        blankPreamble,      // preamble part 1
        blankPreamble,      // preamble part 2
        blankSeparator,     // -- Separating bit --
        blankEngineNumber,  // Engine Number
        blankSeparator,     // -- Separating bit --
        blankCommand,       // Command
        blankSeparator,     // -- Separating bit --
        blankInstruction.command ^ blankInstruction.engineNumber,  // Checksum
        blankEndOfMessage   // --- End of message bit ---
};

struct Instruction testInstruction =
{
        PREAMBLE,           // preamble part 1
        PREAMBLE,           // preamble part 2
        SEPARATOR,          // -- Separating bit --
        ENGINE_NUMBER,      // Engine Number
        SEPARATOR,          // -- Separating bit --
        COMMAND,            // Command
        SEPARATOR,          // -- Separating bit --
        testInstruction.command ^ testInstruction.engineNumber,  // Checksum
        END_OF_MESSAGE        // --- End of message bit ---
};


void setup()
{
    // Enable the LED of the arduino
    pinMode(LED_BUILTIN, OUTPUT);
    // Enable a pin as output
    pinMode(ACTIVE_PIN_A,OUTPUT);
    
    // Serial Port for printouts
	//Serial.begin(9600);
}

void loop()
{   
    //Serial.println("\n--------------- test output ---------------\n");
    //readInstructionData(blankInstruction);
    //writeToTrain(ACTIVE_PIN_A, blankInstruction);
    //delay(1000);
    //Serial.println("\n--------------- test output ---------------\n");
    //readInstructionData(testInstruction);
    writeToTrain(ACTIVE_PIN_A, testInstruction);
    //delay(1000);

}


// TODO - Find out how to use Serial outside of main, for now, it lives here
void readInstructionData(struct Instruction instruction)
{
    char* preambleFixed = "whoops";
    int total = (instruction.preamble[0] + instruction.preamble[1]);
    if (total == 510)
    {
        preambleFixed = "0xFFFF";
    }
    if (total == 0)
    {
        preambleFixed = "0x0000";
    }

    Serial.print("The preamble is: ");
    Serial.print(preambleFixed);
    Serial.print(" The engine number is: ");
    Serial.print(instruction.engineNumber);
    Serial.print(" The command is: ");
    Serial.print(instruction.command);
    Serial.print(" The checksum is: ");
    Serial.print(instruction.checksum); 
    Serial.println();
}
