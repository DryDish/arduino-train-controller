#include "stateMachine.h"

// Had to set it to a static variable 14 or it wouldn't work.
void clearSensorCounters(unsigned int trackSensorAddresses[TOTAL_SENSORS][MAX_READINGS])
{
    // Serial.print("Before clean");
    // Serial.println(trackSensorAddresses[3][1]);
    // Serial.println("entered loop");
    for (unsigned short i = 0; i < 14; i++)
    {
        trackSensorAddresses[i][1] = 0;
    }
    // Serial.print("After clean");
    // Serial.println(trackSensorAddresses[3][1]);
}
// Had to set it to a static variable 14 or it wouldn't work.
void readSensorCounters(unsigned int (trackSensorAddresses[TOTAL_SENSORS][MAX_READINGS]))
{
    for (short i = 0; i < 14; i++)
    {
        Serial.print(trackSensorAddresses[i][0]);
        Serial.print(" - ");
        Serial.println(trackSensorAddresses[i][1]);
    }
}

void addCommandToList(struct Command *command, unsigned short address, unsigned char power, unsigned char direction)
{
    changeCommandAccessory(command, address, power, direction);
    addToList(command->byteOne, command->byteTwo);
}


unsigned char state = ORANGE_WAITING;


unsigned char advanceStateMachine(unsigned int trackSensorAddresses[TOTAL_SENSORS][MAX_READINGS], struct Command *command)
{
    if (state == ORANGE_WAITING)
    {
        // Sensor 4
        if (trackSensorAddresses[3][1] < 2)
        {
            return 0;
        }
        Serial.print("Sensor 4  -- index: ");
        Serial.println(trackSensorAddresses[3][0]);

        //readSensorCounters(trackSensorAddresses);
        clearSensorCounters(trackSensorAddresses);
        state = ORANGE_MOVING;
        return 1;
    }
    else if (state == ORANGE_MOVING)
    {
        if (trackSensorAddresses[11][1] < 2 || trackSensorAddresses[7][1] < 2)
        {
            return 0;
        }

        Serial.print("Sensor 11 -- index: ");
        Serial.println(trackSensorAddresses[11][0]);
        Serial.print("Sensor 7  -- index: ");
        Serial.println(trackSensorAddresses[7][0]);

        //readSensorCounters(trackSensorAddresses);
        // SOMETHING WEIRD HERE BOYS
        addCommandToList(command, 241, 1, 1);
        addCommandToList(command, 241, 0, 1);
        // SOMETHING WEIRD HERE BOYS
        addCommandToList(command, 249, 1, 0);
        addCommandToList(command, 249, 0, 0);

        addCommandToList(command, 101, 1, 0);

        addCommandToList(command,141 , 1, 0);

        addCommandToList(command, 42, 1, 1);

        state = ORANGE_RETURNED;
        return 2;
    }
    else if (state == ORANGE_RETURNED)
    {
        if (trackSensorAddresses[2][1] < 2)
        {
            return 0;
        }

        // SOMETHING WEIRD HERE BOYS
        addCommandToList(command, 241, 1, 0);
        addCommandToList(command, 241, 0, 0);
        // SOMETHING WEIRD HERE BOYS
        addCommandToList(command, 249, 1, 1);
        addCommandToList(command, 249, 0, 1);

        addCommandToList(command, 42, 1, 0);
        addCommandToList(command, 101, 1, 1);
        addCommandToList(command, 141, 1, 1);

        // Documentation states that we should clear sensors, but we dont?
        // I'll comment here a clear sensor method
        clearSensorCounters(trackSensorAddresses);

        state = ORANGE_WAITING;
        return 3;
    }
    else 
    {
        return 4;
    }
}
