#include "readCommand.h"
#include "bytesAndbools.h"

// revert to c?
void convertToBinaryAndSend(unsigned char byte, unsigned char size)
{
    unsigned char n;
    unsigned char c;
    unsigned char k;
    n = byte;
    for (c = size; c > 0; c--) //decrement 8 times (8 is 1 byte, the size of a byte)
    {
        k = n >> c-1;       //right shift by c ( -1 to correct the bit placement)
        if (k & 1)          // if the value after right shifting is 1 in position 1 then print 1
        {
            bitIsOne = true;
            hasBit = true;
            //delay(10);
        }
        else                // if the value after right shifting is 0 on position 1 then print 1
        {
            bitIsOne = false;
            hasBit = true;
            //delay(10);
        }
    }
}


void sendCommand(struct Command *command)
{
    if (command->byteOne != 1) // If its a normal instruction send it 3 times
    {
        for (char i = 0; i < 3; i++)
        {
            convertToBinaryAndSend(command->preamble1, 8);
            convertToBinaryAndSend(command->preamble2, 8);
            convertToBinaryAndSend(command->blank1, 1);
            convertToBinaryAndSend(command->byteOne, 8);
            convertToBinaryAndSend(command->blank2, 1);
            convertToBinaryAndSend(command->byteTwo, 8);
            convertToBinaryAndSend(command->blank3, 1);
            convertToBinaryAndSend(command->checksum, 8);
            convertToBinaryAndSend(command->endChar, 1);
        }
    } else {                    // if its a blank instruction send it only once per loop
        convertToBinaryAndSend(command->preamble1, 8);
        convertToBinaryAndSend(command->preamble2, 8);
        convertToBinaryAndSend(command->blank1, 1);
        convertToBinaryAndSend(command->byteOne, 8);
        convertToBinaryAndSend(command->blank2, 1);
        convertToBinaryAndSend(command->byteTwo, 8);
        convertToBinaryAndSend(command->blank3, 1);
        convertToBinaryAndSend(command->checksum, 8);
        convertToBinaryAndSend(command->endChar, 1);
    }

        
}
