#include "definitions.h"
#include "command.h"
#include "changeCommand.h"
#include "readCommand.h"
#include "setupTimer2Overflow.h"


struct Command command =
{
        PREAMBLE,           // preamble part 2
        SEPARATOR,          // -- Separating bit --
        BLANK_BYTE_ONE,     // Engine Number
        SEPARATOR,          // -- Separating bit --
        BLANK_BYTE_TWO,     // byteTwo
        SEPARATOR,          // -- Separating bit --
        command.byteOne ^ command.byteTwo,  // Checksum
        END_OF_MESSAGE        // --- End of message bit ---
};


unsigned char byteOne = 0;
unsigned char byteTwo = 0;
bool hardStop = false;
int counter = 0;

ISR(TIMER2_OVF_vect)
{
    if (hardStop ==  true)
    {
        byteTwo = HARDSTOP;
        hardStop = false;
    }  
    TCNT2 = TIMER_SHORT;
}

void setup()
{
    Serial.begin(9600);
    Serial.println("Setting up...");
    setupTimer2Overflow();

    Serial.println("Setup complete!\n");
}

void loop()
{
    
    byteOne = 50;
    byteTwo = SPEED1;
    
    readCommand(&command, "BEFORE");
    hardStop = true;

    changeCommand(&command, &byteOne, &byteTwo);

    readCommand(&command, "AFTER ");

    byteOne = 60;
    byteTwo = SPEED6;

    readCommand(&command, "BEFORE");
    hardStop = true;

    changeCommand(&command, &byteOne, &byteTwo);

    readCommand(&command, "AFTER ");
    Serial.println(++counter);

    delay(1000);
}
