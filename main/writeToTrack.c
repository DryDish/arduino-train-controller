#include <stdio.h>
#include "writeToTrain.h"
#include "write.h"

void writeToTrack(unsigned int address, unsigned char power, unsigned char direction, unsigned char *byteOne, unsigned char *byteTwo)
{
    *byteOne = 128; // 128 = 0b 1000 0000
    *byteTwo = 128; // 128 = 0b 1000 0000
    power = power << 3;

    unsigned int accessoryAddress = address / 4 + 1;
    unsigned int registerAddress = (address % 4 - 1) << 1;

    // First byte 01 + 0b address 
    unsigned int tempByteOne = accessoryAddress << 10;
    tempByteOne = tempByteOne >> 10;
    *byteOne += tempByteOne;
    
    // Second byte 
    unsigned int tempByteTwo = accessoryAddress >> 6;
    tempByteTwo = tempByteTwo ^ 7; // 7 = 0b 0000 0111
    tempByteTwo = tempByteTwo << 4;
    
    *byteTwo += tempByteTwo + power + registerAddress + direction;
}
