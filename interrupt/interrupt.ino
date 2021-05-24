#include "definitions.h"
#include "command.h"
#include "changeCommand.h"
#include "readCommand.h"
#include "setupTimer2Overflow.h"
#include "write.h"


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
bool hardStop = false;
int counter = 0;

ISR(TIMER2_OVF_vect)
{
    
    if (hardStop == true)
    {
        byteTwo = HARDSTOP;
        hardStop = false;
        Serial.println(TCNT2);
    }  
    TCNT2 = TIMER_SHORT;
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

unsigned short position = 7;

void loop()
{
    
    byteOne = 50;
    byteTwo = SPEED1;
    changeCommand(&command, &byteOne, &byteTwo);
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
    /* -- read the entire byte in sequence --
    position = 8;
    convertByteToBinary(&command.byteOne, &position);
    position = 8;
    convertByteToBinary(&command.preamble2, &position);

    convertBitToBinary(&command.blank1);
    position = 8;
    convertByteToBinary(&command.byteOne, &position);

    convertBitToBinary(&command.blank2);
    position = 8;
    convertByteToBinary(&command.byteTwo, &position);
    
    convertBitToBinary(&command.blank3);
    position = 8;
    convertByteToBinary(&command.checksum, &position);
    convertBitToBinary(&command.endChar);
    */
    position = 8;
    Serial.print("Position at start: ");
    Serial.println(position);
    convertPositionsToBinary(&command.byteOne, &position);   // 8
    convertPositionsToBinary(&command.byteOne, &position);   // 7
    convertPositionsToBinary(&command.byteOne, &position);   // 6
    convertPositionsToBinary(&command.byteOne, &position);   // 5
    convertPositionsToBinary(&command.byteOne, &position);   // 4
    convertPositionsToBinary(&command.byteOne, &position);   // 3
    convertPositionsToBinary(&command.byteOne, &position);   // 2
    convertPositionsToBinary(&command.byteOne, &position);   // 1
    Serial.print("Position at end: ");
    Serial.println(position);
    Serial.println("-----------");
    delay(1000);
}
