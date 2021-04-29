#include <stdio.h>
#include "writeToTrain.h"
#include "write.h"


int writeToTrain(unsigned char pin, struct Instruction instruction)
{
    //printf("writing to train...\n");

    writeByte(pin ,instruction.preamble[0]);
    writeByte(pin ,instruction.preamble[1]);
    writeBit(pin ,instruction.blank1);
    writeByte(pin ,instruction.byteOne);
    writeBit(pin ,instruction.blank2);
    writeByte(pin ,instruction.byteTwo);
    writeBit(pin ,instruction.blank3);
    writeByte(pin ,instruction.checksum);
    writeBit(pin ,instruction.endChar);
    writeBit(pin ,instruction.endChar);
    return 0;
}