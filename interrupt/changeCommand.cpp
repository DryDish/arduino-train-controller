#include "changeCommand.h"

// this HAS to be a cpp file in order for interrupts() and noInterrupts() to work, but code is written in C first.
void changeCommandTrain(struct Command *command, unsigned char newByteOne, unsigned char newByteTwo)
{
    // delay needed to ensure the ISR sequence is triggered in time
    // Anything lower than 6 will occasionally miss the changed bytes
    // If issues arise increase it to 7 or 8
    delay(6);
    noInterrupts();
    command -> byteOne = newByteOne;
    command -> byteTwo = newByteTwo;
    command -> checksum = (newByteOne ^ newByteTwo);
    interrupts();
}

// Due to the address potentially being larger than 255 i had to make this not use pointers for the values
void changeCommandAccessory(struct Command *command, unsigned short address, unsigned char power, unsigned char direction)
{
    unsigned char accByteOne = 128; // 128 = 0b 1000 0000
    unsigned char accByteTwo = 128; // 128 = 0b 1000 0000
    power = power << 3;

    unsigned int accessoryAddress;
    unsigned int registerAddress;
    if (address % 4 == 0)
    {
        accessoryAddress = ( address - 1 ) / 4 + 1;
        registerAddress = 3 << 1;
    }
    else
    {
        accessoryAddress = address / 4 + 1;
        registerAddress = (address % 4 - 1) << 1;
    }

    // First byte: 10 + address(6)
    unsigned int tempByteOne = accessoryAddress << 10;
    tempByteOne = tempByteOne >> 10;
    accByteOne += tempByteOne;

    // Second byte: 1 + address(3) + power(1) + registerAddress(2) + direction(1)
    unsigned int tempByteTwo = accessoryAddress >> 6;
    tempByteTwo = tempByteTwo ^ 7; // 7 = 0b 0000 0111
    tempByteTwo = tempByteTwo << 4;

    accByteTwo += tempByteTwo + power + registerAddress + direction;

    // delay needed to ensure the ISR sequence is triggered in time
    // Anything lower than 6 will occasionally miss the changed bytes
    // If issues arise increase it to 7 or 8
    delay(6);
    noInterrupts();
    command -> byteOne = accByteOne;
    command -> byteTwo = accByteTwo;
    command -> checksum = accByteOne ^ accByteTwo;
    interrupts();
}