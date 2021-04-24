#include <stdio.h>
#include "writeToTrain.h"
#include "write.h"


int writeToTrain(unsigned char pin, struct Instruction instruction)
{
    printf("writing to train...\n");

    writeByte(pin ,instruction.preamble[0]);
    writeByte(pin ,instruction.preamble[1]);
    writeByte(pin ,instruction.blank1);
    writeByte(pin ,instruction.engineNumber);
    writeByte(pin ,instruction.blank2);
    writeByte(pin ,instruction.command);
    writeByte(pin ,instruction.blank3);
    writeByte(pin ,instruction.checksum);
    writeByte(pin ,instruction.endChar);
    return 0;
}