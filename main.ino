#include <stdio.h>
#include "readFromStruct.h"
#include "write.h"
#include "writeToTrain.h"
#include "instruction.h"
#include "definitions.h"


#define ENGINE_NUMBER 40
#define COMMAND 137

#define ACTIVE_PIN1 4
#define ACTIVE_PIN2 0
#define ACTIVE_PIN3 0

void setup()
{
    //Serial Port begin
	Serial.begin(9600);


}

void loop()
{   
    /*
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
    */
    //Serial.print(readStructData(blankInstruction));
    //writeToTrain(ACTIVE_PIN1, testInstruction);
    Serial.println("test");
    //Serial.print(readStructData(testInstruction));
    //writeToTrain(ACTIVE_PIN1, testInstruction);
    
    delay(1000);
    
}
