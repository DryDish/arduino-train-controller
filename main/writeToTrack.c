#include <stdio.h>
#include "writeToTrain.h"
#include "write.h"

unsigned int writeToTrack(unsigned int address, unsigned char power)
{
    unsigned char byteOne = 128; // 0b 1000 0000
    unsigned char byteTwo = 0;

    unsigned int accessoryAddress = address / 4 + 1;
    unsigned int registerAddress = address % 4 - 1;

    unsigned int tempByteOne = accessoryAddress << 10;
    tempByteOne = tempByteOne >> 10;
    tempByteOne += byteOne;
    return tempByteOne;
}
