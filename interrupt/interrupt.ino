#include "definitions.h"
#include "bytesAndbools.h"
#include "command.h"
#include "changeCommand.h"
#include "readCommand.h"
#include "setupTimer2Overflow.h"
#include "sendCommand.h"
#include "linkedList.h"

struct Command blankCommand =
    {
        PREAMBLE,                                    // preamble part 1
        PREAMBLE,                                    // preamble part 2
        SEPARATOR,                                   // -- Separating bit --
        BLANK_BYTE_ONE,                              // Engine Number
        SEPARATOR,                                   // -- Separating bit --
        BLANK_BYTE_TWO,                              // byteTwo
        SEPARATOR,                                   // -- Separating bit --
        blankCommand.byteOne ^ blankCommand.byteTwo, // Checksum
        END_OF_MESSAGE                               // --- End of message bit ---
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



unsigned char counter;
bool secondInterrupt = false;

ISR(TIMER2_OVF_vect)
{
    unsigned char lastTimer;
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
            //Serial.println();
            counter = 0;
        }

    }

}
unsigned char timerKinda = 0;
void setup()
{
    Serial.begin(9600);
    Serial.println("Setting up...");
    setupTimer2Overflow();
    pinMode(DCC_PIN, OUTPUT);                   // pin 4 this is for the DCC Signal
    pinMode(LED_BUILTIN, OUTPUT);


    addToList(135, 245);
    addToList(136, 246);
    addToList(137, 247);
    addToList(138, 248);
    addToList(139, 249);
    addToList(140, 250);
    Serial.println("Setup complete!\n");
}



void loop()
{        
    if ( timerKinda > 15)
    {
        changeCommandAccessory(&command, 276, 1, 1);
        addToList(command.byteOne, command.byteTwo);
        timerKinda = 0;
    }
    timerKinda++;

    regenerateCommand();
    sendCommand(&command);
    
    Serial.println("\n-----------");
    delay(400);
}

unsigned char regenerateCommand()
{
    if (isEmpty())
    {
        command = blankCommand;
        readCommand(&command, "is empty");
        return 1;
    }
    Node *item = retreiveFirstItemInList();
    changeCommandTrain(&command, item->byteOne, item->byteTwo);
    deleteFirstListItem();
    readCommand(&command, "not empty");
    return 0;
}
