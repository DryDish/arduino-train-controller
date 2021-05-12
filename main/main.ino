#include <stdio.h>
//#include "readFromStruct.h"
#include "definitions.h"
#include "instruction.h"
#include "write.h"
#include "writeToTrain.h"
#include "writeToTrack.h"

// 1001 1010 -- 154
// 1111 1001 -- 249 // straight

// 1001 1010 -- 154
// 1111 1001 -- 248 // turn
#define ENGINE_NUMBER 11
#define COMMAND SPEED4
#define ACTIVE_PIN_A 4

// 1001 1010 -- 154
// 1111 0001 -- 241 // straight off

// 1001 1010 -- 154
// 1111 0001 -- 240 // turn off


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

unsigned short testerShort;
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
    testerShort = writeToTrack(102, 0, 1);
    writeToTrain(ACTIVE_PIN_A, testInstruction, testerShort);

    testerShort = writeToTrack(102, 1, 1);
    writeToTrain(ACTIVE_PIN_A, testInstruction, testerShort);
    // accessory address, power, direction, *byteOne, *byteTwo
    //Serial.print(writeToTrack(101, 1, 1));
    //Serial.println();
    //readInstructionData(testInstruction);
    //writeToTrain(ACTIVE_PIN_A, testInstruction);
    //writeToTrain(ACTIVE_PIN_A, testInstruction2);

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
    Serial.print(" The byteOne: ");
    Serial.print(instruction.byteOne);
    Serial.print(" The byteTwo is: ");
    Serial.print(instruction.byteTwo);
    Serial.print(" The checksum is: ");
    Serial.print(instruction.checksum); 
    Serial.println();
}
