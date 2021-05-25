#include "definitions.h"
#include "command.h"
#include "changeCommand.h"
#include "readCommand.h"
#include "setupTimer2Overflow.h"
#include "write.h"

struct Command blankCommand =
{
        PREAMBLE,           // preamble part 1
        PREAMBLE,           // preamble part 2
        SEPARATOR,          // -- Separating bit --
        BLANK_BYTE_ONE,     // Engine Number
        SEPARATOR,          // -- Separating bit --
        BLANK_BYTE_TWO,     // byteTwo
        SEPARATOR,          // -- Separating bit --
        blankCommand.byteOne ^ blankCommand.byteTwo,  // Checksum
        END_OF_MESSAGE        // --- End of message bit ---
};

struct Command command =
{
        PREAMBLE,           // preamble part 1
        PREAMBLE,           // preamble part 2
        SEPARATOR,          // -- Separating bit --
        BLANK_BYTE_ONE,     // Engine Number
        SEPARATOR,          // -- Separating bit --
        BLANK_BYTE_TWO,     // byteTwo
        SEPARATOR,          // -- Separating bit --
        command.byteOne ^ command.byteTwo,  // Checksum
        END_OF_MESSAGE        // --- End of message bit ---
};

unsigned char byteOne = 40;
unsigned char byteTwo = SPEED11;
unsigned char counter;

//unsigned char position = 0;
bool bitIsOne = false;
bool hasBit = false;

ISR(TIMER2_OVF_vect)
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
    
    while (hasBit)
    {
        if (bitIsOne)  
        {  // data = 1 short pulse
            TCNT2+=TIMER_SHORT;
            lastTimer=TIMER_SHORT;
            //Serial.print('1');
            bitIsOne = false;
            hasBit = false;
            counter++;
        }
        else  
        {   // data = 0 long pulse
            TCNT2 += TIMER_LONG; 
            lastTimer = TIMER_LONG;
            //Serial.print('0');
            hasBit = false;
            counter++;
        }
        if (counter > 7)
        {
            Serial.println();
            counter = 0;
        }
    }

}

void setup()
{
    Serial.begin(9600);
    Serial.println("Setting up...");
    setupTimer2Overflow();
    pinMode(DCC_PIN, OUTPUT);                   // pin 4 this is for the DCC Signal
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.println("Setup complete!\n");
}

void loop()
{
    /*
    byteOne = 50;
    byteTwo = SPEED1;
    */
    changeCommandTrain(&command, &byteOne, &byteTwo);
    //changeCommandAccessory(&command, 101, 1, 1);
    
    
    sendCommand(&command, &bitIsOne, &hasBit);

    delay(1000);
    Serial.println("\n-----------");
    /*
    readCommand(&command, "BEFORE");
    hardStop = true;

    changeCommand(&command, &byteOne, &byteTwo);

    readCommand(&command, "AFTER ");

    byteOne = 60;
    byteTwo = SPEED6;

    readCommand(&command, "BEFORE");
    hardStop = true;

    changeCommand(&command, &byteOne, &byteTwo);

    //readCommand(&command, "AFTER ");
    */

}
