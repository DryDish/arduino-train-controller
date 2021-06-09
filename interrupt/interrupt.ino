#include "definitions.h"
#include "bytesAndbools.h"
#include "command.h"
#include "changeCommand.h"
#include "readCommand.h"
#include "setupTimer2Overflow.h"
#include "sendState.h"
#include "linkedList.h"
#include "stateMachine.h"
#include "readAccessoryData.h"

// ------------------------------------------------------ STRUCTS ------------------------------------------------------

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
        PREAMBLE,                          // preamble part 1
        PREAMBLE,                          // preamble part 2
        SEPARATOR,                         // -- Separating bit --
        BLANK_BYTE_ONE,                    // Engine Number
        SEPARATOR,                         // -- Separating bit --
        BLANK_BYTE_TWO,                    // byteTwo
        SEPARATOR,                         // -- Separating bit --
        command.byteOne ^ command.byteTwo, // Checksum
        END_OF_MESSAGE                     // --- End of message bit ---
};

unsigned char *ptr_byteOne = &command.byteOne;
unsigned char *ptr_byteTwo = &command.byteTwo;
unsigned char *ptr_checksum = &command.checksum;

// ------------------------------------------------------ ARRAYS ------------------------------------------------------

// Pins for getting track sensor inputs
unsigned int trackSensorAddresses[TOTAL_SENSORS][MAX_READINGS] = {{13, 0}, {12, 0}, {11, 0}, {10, 0}, {9, 0}, {8, 0}, {7, 0}, {6, 0}, {5, 0}, {A0, 0}, {A1, 0}, {A2, 0}, {A3, 0}, {A4, 0}};

// Light addresses mapped up starting with 12 and going down the track on the schematic
unsigned short lightAddresses[28] = {12, 52, 21, 51, 62, 22, 61, 11, 14, 42, 82, 81, 31, 32, 91, 92, 111, 112, 102, 101, 122, 121, 131, 132, 151, 152, 142, 141};

// Switch addresses mapped up starting with 12 and going down the track on the schematic
unsigned short switchAddresses[16] = {221, 222, 234, 233, 224, 223, 231, 232, 242, 250, 249, 241, 243, 251, 244, 252};

// Static engine number of the trains
unsigned char trainNumbers[3] = {11, 8, 40};

// -------------------------------------------------- METHODS DECLARATIONS ---------------------------------------------------

void addSensorPins();
void prepareTrackCommands();
unsigned char regenerateCommand();
void addCommandToListInSetup(struct Command *command, unsigned short address, unsigned char power, unsigned char direction);

// ------------------------------------------------------ SETUP METHODS ------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------------

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

        changeCommandAccessory(&command, switchAddresses[i], 0, 1);
        addToList(command.byteOne, command.byteTwo);
    }

    addCommandToListInSetup(&command, 42, 1, 0);

    addCommandToListInSetup(&command, 101, 1, 1);
    addCommandToListInSetup(&command, 141, 1, 1);

    addCommandToListInSetup(&command, 223, 1, 0);
    addCommandToListInSetup(&command, 224, 1, 1);
    addCommandToListInSetup(&command, 223, 0, 0);
    addCommandToListInSetup(&command, 224, 0, 1);

    addCommandToListInSetup(&command, 233, 1, 1);
    addCommandToListInSetup(&command, 234, 1, 1);
    addCommandToListInSetup(&command, 233, 0, 1);
    addCommandToListInSetup(&command, 234, 0, 1);

    addCommandToListInSetup(&command, 231, 1, 0);
    addCommandToListInSetup(&command, 232, 1, 1);
    addCommandToListInSetup(&command, 231, 0, 0);
    addCommandToListInSetup(&command, 232, 0, 1);
}

// ------------------------------------------------------ LOOP METHODS ---------------------------------------------
// -----------------------------------------------------------------------------------------------------------------

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

void addCommandToListInSetup(struct Command *command, unsigned short address, unsigned char power, unsigned char direction)
{
    changeCommandAccessory(command, address, power, direction);
    addToList(command->byteOne, command->byteTwo);
}

// ------------------------------------------------------ ISR ------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
bool printouts = false;
bool flag;
bool *ptr_flag = &flag;
bool secondInterrupt = false;
ISR(TIMER2_OVF_vect)
{

    if (secondInterrupt)
    { // for every second interupt just toggle signal
        digitalWrite(DCC_PIN, 1);
        secondInterrupt = false;
        TCNT2 += lastTimer;
    }
    else
    { // != every second interrupt, advance bit or state

        digitalWrite(DCC_PIN, 0);
        secondInterrupt = true;
        sendState(ptr_byteOne, ptr_byteTwo, ptr_checksum, printouts);
    }
}

// ------------------------------------------------------ SETUP ------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------

void setup()
{
    Serial.begin(9600);
    Serial.print("Setting up...");
    setupTimer2Overflow();
    pinMode(DCC_PIN, OUTPUT); // pin 4 this is for the DCC Signal
    pinMode(LED_BUILTIN, OUTPUT);
    addSensorPins();

    prepareTrackCommands();

    // Start all of the trains
    for (short i = 0; i < 3; i++)
    {
        changeCommandTrain(&command, trainNumbers[i % 3], SPEED8);
        addToList(command.byteOne, command.byteTwo);
    }
    delay(100);
    Serial.println("Setup complete!\n");
}

// ------------------------------------------------------  LOOP ------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
unsigned char loopCounter = 0;
void loop()
{    
    if (loopCounter > 150)
    {
        changeCommandTrain(&command, 150, 250);
        addToList(command.byteOne, command.byteTwo);
        loopCounter = 0;
    }
    readAccessoryData(trackSensorAddresses);

    advanceStateMachine(trackSensorAddresses, &command);

    regenerateCommand();

    //readCommand(&command, "the loop sent:");

    //the sendState(&command) is in ISR loop;
    if (!printouts)
    {
        Serial.println("-");
    }
    loopCounter++;
    delay(1200);
}

// ------------------------------------------------------ END LOOP ------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------
