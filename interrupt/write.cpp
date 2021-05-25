#include "write.h"

// revert to c?
void convertToBinaryAndSend(unsigned char byte, unsigned char size, bool *bitIsOne, bool *hasBit)
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
            *bitIsOne = true;
            //Serial.print("1");
            *hasBit = true;
            delay(10);
        }
        else                // if the value after right shifting is 0 on position 1 then print 1
        {
            *bitIsOne = false;
            *hasBit = true;
            delay(10);
            //Serial.print("0");  
            //size -= 1;
        }
    }
    //Serial.print("\n");
}


void sendCommand(struct Command *command, bool *bitIsOne, bool *hasBit)
{
    for (char i = 0; i < 3; i++)
    {
        convertToBinaryAndSend(command->preamble1, 8, bitIsOne, hasBit);
        convertToBinaryAndSend(command->preamble2, 8, bitIsOne, hasBit);
        convertToBinaryAndSend(command->blank1, 1, bitIsOne, hasBit);
        convertToBinaryAndSend(command->byteOne, 8, bitIsOne, hasBit);
        convertToBinaryAndSend(command->blank2, 1, bitIsOne, hasBit);
        convertToBinaryAndSend(command->byteTwo, 8, bitIsOne, hasBit);
        convertToBinaryAndSend(command->blank3, 1, bitIsOne, hasBit);
        convertToBinaryAndSend(command->checksum, 8, bitIsOne, hasBit);
        convertToBinaryAndSend(command->endChar, 1, bitIsOne, hasBit);
    }
        
}

/*

void writeBit( bool *bitIsOne ) // Work In Progress, do not try to use it yet
{  
    unsigned char lastTimer;
    bool secondInterrupt = false;
    if (secondInterrupt) 
    {  // for every second interupt just toggle signal
        digitalWrite(DCC_PIN,1);
        secondInterrupt = false;    
        TCNT2 += lastTimer;
        //Serial.print("1");
    }
    else  
    {  // != every second interrupt, advance bit or state
        digitalWrite(DCC_PIN,0);
        secondInterrupt = true;
        //Serial.print("0");
    }


    if (bitIsOne)  
    {  // data = 1 short pulse
        TCNT2+=TIMER_SHORT;
        lastTimer=TIMER_SHORT;
        Serial.print('1');
    }  
    else  
    {   // data = 0 long pulse
        TCNT2 += TIMER_LONG; 
        lastTimer = TIMER_LONG;
        Serial.print('0');
    }
}

void convertPositionsToBinary(unsigned char *byte, unsigned short *position, bool *bitIsOne)
{
    unsigned char n = *byte;
    unsigned char c = *position;
    unsigned char k;

    k = n >> c-1;           //right shift by c ( -1 to correct the bit placement)
    if (k & 1)              // if the value after right shifting is 1 in position 1 then print 1
    {
        *bitIsOne = true;
        *position -= 1;
    }
    else                    // if the value after right shifting is 0 on position 1 then print 1
    {
        *bitIsOne = false;
        *position -= 1;
    }
    //Serial.print("\n");
}

void convertBitToBinary(unsigned char *byte, bool *bitIsOne)
{
    unsigned char n;
    unsigned char c;
    unsigned char k;
    n = *byte;
    k = n;              
    if (k & 1)              // if the value after right shifting is 1 in position 1 then print 1
    {
        *bitIsOne = true;
        delay(10);
        //Serial.print("1");
    }
    else 
    {
        *bitIsOne = false;
        delay(10);
        //Serial.print("0");  // if the value after right shifting is 0 on position 1 then print 1
    }
    Serial.print("\n");
}
*/