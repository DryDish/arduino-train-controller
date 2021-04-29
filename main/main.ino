#include <stdio.h>
//#include "readFromStruct.h"
#include "definitions.h"
#include "instruction.h"
#include "write.h"
#include "writeToTrain.h"

// 1001 1010 -- 154
// 1111 1001 -- 249 // straight

// 1001 1010 -- 154
// 1111 1001 -- 248 // turn
#define ENGINE_NUMBER 154
#define COMMAND 248


// 1001 1010 -- 154
// 1111 0001 -- 241 // straight off

// 1001 1010 -- 154
// 1111 0001 -- 240 // turn off
#define ENGINE_NUMBER2 154
#define COMMAND2 240

#define ACTIVE_PIN_A 4
#define ACTIVE_PIN_B 0
#define ACTIVE_PIN_C 0

void readStructData(struct Instruction instruction);

struct Instruction blankInstruction =
{
        blankPreamble,      // preamble part 1
        blankPreamble,      // preamble part 2
        blankSeparator,     // -- Separating bit --
        blankByteOne,  // Engine Number
        blankSeparator,     // -- Separating bit --
        blankByteTwo,       // byteTwo
        blankSeparator,     // -- Separating bit --
        blankInstruction.byteOne ^ blankInstruction.byteTwo,  // Checksum
        blankEndOfMessage   // --- End of message bit ---
};

struct Instruction testInstruction =
{
        PREAMBLE,           // preamble part 1
        PREAMBLE,           // preamble part 2
        SEPARATOR,          // -- Separating bit --
        ENGINE_NUMBER,      // Engine Number
        SEPARATOR,          // -- Separating bit --
        COMMAND,            // byteTwo
        SEPARATOR,          // -- Separating bit --
        testInstruction.byteOne ^ testInstruction.byteTwo,  // Checksum
        END_OF_MESSAGE        // --- End of message bit ---
};


struct Instruction testInstruction2 =
{
        PREAMBLE,           // preamble part 1
        PREAMBLE,           // preamble part 2
        SEPARATOR,          // -- Separating bit --
        ENGINE_NUMBER2,      // Engine Number
        SEPARATOR,          // -- Separating bit --
        COMMAND2,            // byteTwo
        SEPARATOR,          // -- Separating bit --
        testInstruction.byteOne ^ testInstruction.byteTwo,  // Checksum
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
    writeToTrain(ACTIVE_PIN_A, testInstruction2);
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
    Serial.print(instruction.byteOne);
    Serial.print(" The byteTwo is: ");
    Serial.print(instruction.byteTwo);
    Serial.print(" The checksum is: ");
    Serial.print(instruction.checksum); 
    Serial.println();
}



//
/*
void cangeTrack()
{
    writeBit()
}
*/