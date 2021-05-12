#include <stdio.h>
#include "writeToTrain.h"
#include "write.h"

unsigned short accessoryDataGenerator(unsigned short address, unsigned char power, unsigned char direction)
{
    unsigned char byteOne = 128; // 128 = 0b 1000 0000
    unsigned char byteTwo = 128; // 128 = 0b 1000 0000
    power = power << 3;

    unsigned int accessoryAddress = address / 4 + 1;
    unsigned int registerAddress = (address % 4 - 1) << 1;

    // First byte: 10 + address(6)
    unsigned int tempByteOne = accessoryAddress << 10;
    tempByteOne = tempByteOne >> 10;
    byteOne += tempByteOne;
    
    // Second byte: 1 + address(3) + power(1) + registerAddress(2) + direction(1)
    unsigned int tempByteTwo = accessoryAddress >> 6;
    tempByteTwo = tempByteTwo ^ 7; // 7 = 0b 0000 0111
    tempByteTwo = tempByteTwo << 4;
    
    byteTwo += tempByteTwo + power + registerAddress + direction;

    unsigned short oneHappyGian = (byteOne << 8) + byteTwo;
    return oneHappyGian;
}
