#include "sendState.h"


// Figure out how to send only 1 per interrupt.
void convertToBinaryAndSend(unsigned char byte, unsigned char size)
{
    if (size> 0)
    {
        unsigned char n;
        unsigned char c;
        unsigned char k;
        n = byte;
        
        k = n >> size-1;       //right shift by size ( -1 to correct the bit placement)
        if (k & 1)          // if the value after right shifting is 1 in position 1 then short pulse
        {
            TCNT2 += TIMER_SHORT;
            lastTimer=TIMER_SHORT;
        }
        else                // if the value after right shifting is 0 on position 1 then long pulse
        {
            TCNT2 += TIMER_LONG; 
            lastTimer = TIMER_LONG;
    } 
    }
}
unsigned char bitState = 1;
unsigned char size = 8;
void sendState(struct Command *command)
{
    
    switch (bitState)
    {
    case 1: // preamble 1
        convertToBinaryAndSend(command->preamble1, size);
        size--;
        if (size == 0 )
        {
            bitState = 2;
            size = 8;
        }
        break;
    case 2: // preamble 2
        convertToBinaryAndSend(command->preamble2, size);
        size--;
        if (size == 0 )
        {
            bitState = 3;
            size = 1;
        }
        break;
    case 3: // blank 1
        convertToBinaryAndSend(command->blank1, size);
        size--;
        if (size == 0 )
        {
            bitState = 4;
            size = 8;
        }
        break;
    case 4: // byte 1
        convertToBinaryAndSend(command->byteOne, size);
        size--;       
        if (size == 0 )
        {
            bitState = 5;
            size = 1;
        }
        break;
    case 5: // blank 2
        convertToBinaryAndSend(command->blank2, size);
        size--;
        if (size == 0 )
        {
            bitState = 6;
            size = 8;
        }
        break;
    case 6: // byte 2
        convertToBinaryAndSend(command->byteTwo, size);
        size--;
        if (size == 0 )
        {
            bitState = 7;
            size = 1;
        }
        break;
    case 7: // blank 3
        convertToBinaryAndSend(command->blank3, size);
        size--;
        if (size == 0 )
        {
            bitState = 8;
            size = 8;
        }
        break;
    case 8: // checksum
        convertToBinaryAndSend(command->checksum, size);
        size--;
        if (size == 0 )
        {
            bitState = 9;
            size = 1;
        }
        break;
    case 9: // end bit
        convertToBinaryAndSend(command->endChar, size);
        size--;
        if (size == 0 )
        {
            bitState = 1;
            size = 8;
        }
        break;

    default:
        break;
    }
}
