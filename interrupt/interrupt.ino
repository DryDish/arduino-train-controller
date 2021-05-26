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

// pins for getting track sensor inputs
unsigned int trackSensorAddresses[14][2] = {{13, 0}, {12, 0}, {11, 0}, {10, 0}, {9, 0}, {8, 0}, {7, 0}, {6, 0}, {5, 0}, {A0, 0}, {A1, 0}, {A2, 0}, {A3, 0}, {A4, 0}};
// Light addresses mapped up starting with 12 and going down the track on the schematic
unsigned short lightAddresses[28] = {12, 52, 21, 51, 62, 22, 61, 11, 14, 42, 82, 81, 31, 32, 91, 92, 111, 112, 102, 101, 122, 121, 131, 132, 151, 152, 142, 141};
// Switch addresses mapped up starting with 12 and going down the track on the schematic
unsigned short switchAddresses[16] = {221, 222, 234, 233, 224, 223, 231, 232, 242, 250, 249, 241, 243, 251, 244, 252};
// This is the (fixed) address of the trains
unsigned char trainNumbers[3] = {11, 8, 40}; 

bool secondInterrupt = false;

void addSensorPins();
void prepareTrackCommands();

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
        }
        else  
        {   // data = 0 long pulse
            TCNT2 += TIMER_LONG; 
            lastTimer = TIMER_LONG;
            //Serial.print('0');
            hasBit = false;
        }

    }

}

// ----------------- SETUP ------------------------


unsigned char timerKinda = 0;
void setup()
{
    Serial.begin(9600);
    Serial.println("Setting up...");
    setupTimer2Overflow();
    pinMode(DCC_PIN, OUTPUT);                   // pin 4 this is for the DCC Signal
    pinMode(LED_BUILTIN, OUTPUT);

    addSensorPins();
    prepareTrackCommands();

    Serial.println("Setup complete!\n");
}

// ----------------- START LOOP ------------------------

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
    readCommand(&command, "loop sent");
    sendCommand(&command);

    Serial.println("\n-----------");
    //delay(1000);
}

// ------------------- END LOOP -------------------------



// ----------------- LOOP METHODS ------------------------

unsigned char regenerateCommand()
{
    if (isEmpty())
    {
        command = blankCommand;
        return 1;
    }
    Node *item = retreiveFirstItemInList();
    changeCommandTrain(&command, item->byteOne, item->byteTwo);
    deleteFirstListItem();
    return 0;
}


// ----------------- SETUP METHODS ------------------------

void addSensorPins()
{
    pinMode(13, INPUT); // corresponds to trackSensorAddresses[0]
    pinMode(12, INPUT);
    pinMode(11, INPUT);
    pinMode(10, INPUT);
    pinMode(9, INPUT);
    pinMode(8, INPUT);
    pinMode(7, INPUT);
    pinMode(6, INPUT);
    pinMode(5, INPUT);
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);
    pinMode(A4, INPUT); // corresponds to trackSensorAddresses[13]
}

void prepareTrackCommands()
{
    // Tell all trains to hard stop
    for (unsigned char i = 0; i < (sizeof(trainNumbers) / sizeof(trainNumbers[0])); i++)
    {
        changeCommandTrain(&command, trainNumbers[i], HARDSTOP);
        addToList(command.byteOne, command.byteTwo);
    }

    // Set all lights to red
    for (unsigned short i = 0; i < (sizeof(lightAddresses) / sizeof(lightAddresses[0])); i++)
    {
        changeCommandAccessory(&command, lightAddresses[i], 1, 1);
        addToList(command.byteOne, command.byteTwo);
    }

    // Set all switches to forward
    for (short i = 0; i < (sizeof(switchAddresses) / sizeof(switchAddresses[0])); i++)
    {
        changeCommandAccessory(&command, switchAddresses[i], 1, 1);
        addToList(command.byteOne, command.byteTwo);
    }
}