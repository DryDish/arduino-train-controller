#include <stdio.h>
#include "writeToTrain.h"
#include "write.h"


int writeToTrain(unsigned char pin, struct Instruction instruction, unsigned short message)
{
    //printf("writing to train...\n");
    unsigned char tempByteTwo = message << 8;
    unsigned char byteOne= message >> 8;
    unsigned char byteTwo = tempByteTwo >> 8;
    
    
    
    

    writeByte(pin ,instruction.preamble[0]);
    writeByte(pin ,instruction.preamble[1]);
    writeBit(pin ,instruction.blank1);
    writeByte(pin ,byteOne);
    writeBit(pin ,instruction.blank2);
    writeByte(pin , byteTwo);
    writeBit(pin ,instruction.blank3);
    writeByte(pin ,instruction.checksum);
    writeBit(pin ,instruction.endChar);
    writeBit(pin ,instruction.endChar);
    return 0;
}