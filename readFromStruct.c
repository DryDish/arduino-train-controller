#include "readFromStruct.h"
#include <stdio.h>

char* readStructData(struct Instruction instruction)
{
    char preamble1 = instruction.preamble[0];
    char preamble2 = instruction.preamble[1];
    int engineNumber = instruction.engineNumber;
    int command = instruction.command;
    int checksum = instruction.checksum;

    return "test string return";
}