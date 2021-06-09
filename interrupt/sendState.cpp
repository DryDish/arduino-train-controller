#include "sendState.h"

bool printout = false;
// Figure out how to send only 1 per interrupt.
void convertToBinaryAndSend(unsigned char *byte, unsigned char *size)
{
    //n = byte;                       //right shift by size ( -1 to correct the bit placement)
    if ((*byte >> *size - 1) & 1) // if the value after right shifting is 1 in position 1 then short pulse
    {
        TCNT2 += TIMER_SHORT;
        lastTimer = TIMER_SHORT;
        if (printout)
        {
            Serial.print(1);
        }
    }
    else // if the value after right shifting is 0 on position 1 then long pulse
    {
        TCNT2 += TIMER_LONG;
        lastTimer = TIMER_LONG;
        if (printout)
        {
            Serial.print(0);
        }
    }
}

void sendOne()
{
    TCNT2 += TIMER_SHORT;
    lastTimer = TIMER_SHORT;
    if (printout)
    {
        Serial.print(1);
    }
}

void sendZero()
{
    TCNT2 = TIMER_LONG;
    lastTimer = TIMER_LONG;
    if (printout)
    {
        Serial.print(0);
    }
}

unsigned char bitState = 1;
unsigned char size = 8;
unsigned char *ptr_size = &size;


void sendState(unsigned char *ptr_byteOne, unsigned char *ptr_byteTwo, unsigned char *ptr_checksum, bool printoutState)
{
    printout = printoutState;
    switch (bitState)
    {
    case 1: // preamble 1
        sendOne();
        size--;
        if (size == 0)
        {
            bitState = 2;
            size = 8;
            if (printout)
            {
                Serial.println();
            }
        }
        break;
    case 2: // preamble 2
        sendOne();
        size--;
        if (size == 0)
        {
            bitState = 3;
            size = 1;
            if (printout)
            {
                Serial.println();
            }
        }
        break;
    case 3: // blank 1
        sendZero();
        size--;
        if (size == 0)
        {
            bitState = 4;
            size = 8;
            if (printout)
            {
                Serial.println();
            }
        }
        break;
    case 4: // byte 1
        convertToBinaryAndSend(ptr_byteOne, ptr_size);
        size--;
        if (size == 0)
        {
            bitState = 5;
            size = 1;
            if (printout)
            {
                Serial.println();
            }
        }
        break;
    case 5: // blank 2
        sendZero();
        size--;
        if (size == 0)
        {
            bitState = 6;
            size = 8;
            if (printout)
            {
                Serial.println();
            }
        }
        break;
    case 6: // byte 2
        convertToBinaryAndSend(ptr_byteTwo, ptr_size);
        size--;
        if (size == 0)
        {
            bitState = 7;
            size = 1;
            if (printout)
            {
                Serial.println();
            }
        }
        break;
    case 7: // blank 3
        sendZero();
        size--;
        if (size == 0)
        {
            bitState = 8;
            size = 8;
            if (printout)
            {
                Serial.println();
            }
        }
        break;
    case 8: // checksum
        convertToBinaryAndSend(ptr_checksum, ptr_size);
        size--;
        if (size == 0)
        {
            bitState = 9;
            size = 1;
            if (printout)
            {
                Serial.println();
            }
        }
        break;
    case 9: // end bit
        sendOne();
        size--;
        if (size == 0)
        {
            bitState = 1;
            size = 8;
            if (printout)
            {
                Serial.println();
                Serial.println();
            }
            else
            {
                Serial.println("1");
            }
        }
        break;

    default:
        break;
    }
}
