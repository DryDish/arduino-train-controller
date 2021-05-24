#include "write.h"
bool bitIsOne;

void writeBit() // Work In Progress, do not try to use it yet
{   /*
    unsigned char lastTimer;
    bool secondInterrupt = false;
    if (secondInterrupt) 
    {  // for every second interupt just toggle signal
        digitalWrite(DCC_PIN,1);
        secondInterrupt = false;    
        TCNT2 += lastTimer; 
    }
    else  
    {  // != every second interrupt, advance bit or state
        digitalWrite(DCC_PIN,0);
        secondInterrupt = true;
    }


    if (bitIsOne)  
    {  // data = 1 short pulse
        TCNT2+=TIMER_SHORT;
        lastTimer=TIMER_SHORT;
        //Serial.print('1');
    }  
    else  
    {   // data = 0 long pulse
        TCNT2 += TIMER_LONG; 
        lastTimer = TIMER_LONG;
        // Serial.print('0');
    }
    */
}



void convertByteToBinary(unsigned char *byte, unsigned short *position)
{
    unsigned char n;
    unsigned char c;
    unsigned char k;
    n = *byte;
    for (c = *position; c > 0; c--) //decrement 8 times (8 is 1 byte, the size of a byte)
    {
        k = n >> c-1;         //right shift by c ( -1 to correct the bit placement)
        if (k & 1)          // if the value after right shifting is 1 in position 1 then print 1
        {
            Serial.print("1");
            *position -= 1;
        }
        else 
        {
            Serial.print("0");  // if the value after right shifting is 0 on position 1 then print 1
            *position -= 1;
        }
    }
    Serial.print("\n");
}

void convertPositionsToBinary(unsigned char *byte, unsigned short *position)
{
    unsigned char n = *byte;
    unsigned char c = *position;
    unsigned char k;

    k = n >> c-1;         //right shift by c ( -1 to correct the bit placement)
    if (k & 1)          // if the value after right shifting is 1 in position 1 then print 1
    {
        Serial.print("1");
        *position -= 1;
    }
    else 
    {
        Serial.print("0");  // if the value after right shifting is 0 on position 1 then print 1
        *position -= 1;
    }
    Serial.print("\n");
}

void convertBitToBinary(unsigned char *byte)
{
    unsigned char n;
    unsigned char c;
    unsigned char k;
    n = *byte;
    k = n >> 1;         //right shift by c
    if (k & 1)          // if the value after right shifting is 1 in position 1 then print 1
    {
        Serial.print("1");
    }
    else 
    {
        Serial.print("0");  // if the value after right shifting is 0 on position 1 then print 1
    }
    Serial.print("\n");
}