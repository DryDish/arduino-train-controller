#include "sendState.h"

void sendOne(bool *printoutState)
{
    TCNT2 += TIMER_SHORT;
    lastTimer = TIMER_SHORT;
    if (*printoutState)
    {
        Serial.print("1");
    }
}

void sendZero(bool *printoutState)
{
    TCNT2 = TIMER_LONG;
    lastTimer = TIMER_LONG;
    if (*printoutState)
    {
        Serial.print("0");
    }
}

void convertToBinaryAndSend(unsigned char *byte, unsigned char *size, bool *printoutState)
{
    if ((*byte >> *size - 1) & 1) // if the value after right shifting is 1 in position 1 then short pulse
    {
        sendOne(printoutState);
    }
    else // if the value after right shifting is 0 on position 1 then long pulse
    {
        sendZero(printoutState);
    }
}



unsigned char bitState = 1;
unsigned char size = 16;
unsigned char *ptr_size = &size;
bool printout = false;

/**
 * Pass it a command and it will extract what it needs to send it via ISR
 * PrintoutState determines if it will print binary or not
 */ 
void sendState(struct Command *command, bool *printoutState)
{
    switch (bitState)
    {
    case 1: // preamble 1
        sendOne(printoutState);
        size--;
        if (size == 0)
        {
            bitState = 2;
            size = 8;
            if (*printoutState)
            {
                Serial.println();
            }
        }
        break;
    case 2: // preamble 2
        sendOne(printoutState);
        size--;
        if (size == 0)
        {
            bitState = 3;
            if (*printoutState)
            {
                Serial.println();
            }
        }
        break;
    case 3: // blank 1
        sendZero(printoutState);
        bitState = 4;
        size = 8;
        if (*printoutState)
        {
            Serial.println();
        }
        break;
    case 4: // byte 1
        convertToBinaryAndSend(&command->byteOne, ptr_size, printoutState);
        size--;
        if (size == 0)
        {
            bitState = 5;
            if (*printoutState)
            {
                Serial.println();
            }
        }
        break;
    case 5: // blank 2
        sendZero(printoutState);
        bitState = 6;
        size = 8;
        if (*printoutState)
        {
            Serial.println();
        }
        break;
    case 6: // byte 2
        convertToBinaryAndSend(&command->byteTwo, ptr_size, printoutState);
        size--;
        if (size == 0)
        {
            bitState = 7;
            if (*printoutState)
            {
                Serial.println();
            }
        }
        break;
    case 7: // blank 3
        sendZero(printoutState);
        bitState = 8;
        size = 8;
        if (*printoutState)
        {
            Serial.println();
        }
        break;
    case 8: // checksum
        convertToBinaryAndSend(&command->checksum, ptr_size, printoutState);
        size--;
        if (size == 0)
        {
            bitState = 9;
            if (*printoutState)
            {
                Serial.println();
            }
        }
        break;
    case 9: // end bit
        sendOne(printoutState);
        bitState = 1;
        size = 8;
        if (*printoutState)
        {
            Serial.println();
            Serial.println();
        }
        break;

    default:
        break;
    }
}

/*
// This was a tested alternative
// It ended up not being much faster, but it was much less readable
// So i scrapped it in favour of the more readable variant above
// Im keeping it here for reference though.

the array looked like this:

---- from interrupt.ino
unsigned char *commands[3] = {ptr_byteOne, ptr_byteTwo, ptr_checksum }
----


unsigned char index = 0;

void sendState(unsigned char *commands[3], unsigned int *stateCount) 
{    
    switch (bitState)
    {
        case 1: // Send 1
            if (index == 3)
            {
                sendOne();
                size = 16;
                index = 0;
                *stateCount+= 1;
                //Serial.println();
                //Serial.println();
                break;
            }
            sendOne();
            size--;
            if (size == 0)
            {
                size = 8;
                bitState = 2;
                //Serial.println();
            }
            break;

        case 2: // Send 0
            sendZero();
            bitState = 3;
            size = 8;
            //Serial.println();
            break;

        case 3: // Send Byte
            convertToBinaryAndSend(commands[index], ptr_size);
            size--;
            if (size == 0)
            {
                index++;
                bitState = 2;
                //Serial.println();
                if (index == 3)
                {
                    bitState = 1;
                    break;
                }
            }
            break;

        default:
            break;
    }
}
*/