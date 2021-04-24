#include <stdio.h>
//#include "readFromStruct.h"
#include "write.h"
#include "writeToTrain.h"
#include "instruction.h"
#include "definitions.h"


#define ENGINE_NUMBER 40
#define COMMAND 137

#define ACTIVE_PIN1 4
#define ACTIVE_PIN2 0
#define ACTIVE_PIN3 0

void readStructData(struct Instruction instruction);

void function()
{
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
    
    readInstructionData(testInstruction);
    readInstructionData(blankInstruction);
    Serial.print("\n");
    //writeToTrain(ACTIVE_PIN1, testInstruction);
    Serial.println("\n--------------- test output ---------------\n");
    //writeToTrain(ACTIVE_PIN1, testInstruction);
}

void setup()
{
    //Serial Port begin
	Serial.begin(9600);
}

void loop()
{   
    function();
    delay(1000);
}


// TODO - Find out how to use Serial outside of main 
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
