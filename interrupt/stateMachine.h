#if !defined(TRAIN_CODE_C_STATE_MACHINE)
#define TRAIN_CODE_C_STATE_MACHINE

#include <Arduino.h>
#include "linkedList.h"
#include "changeCommand.h"

// Orange is waiting. If sensor 4 is triggered 
// clear all sensors  and advance state
const unsigned char ORANGE_WAITING = 1;

// Orange is moving.
// When both sensor 13 and 9 get triggered
// turn switches 241, 249 and set lights
// 101, 141 red and 42 green
const unsigned char ORANGE_MOVING = 2;

// Orange has returned.
// Wait until sensor 3 is triggered, then
// turn switches 241, 249 straight, turn light 42 red
// and turn 101, 141 green.
// Reset all sensors readings.
// State is now reset.
const unsigned char ORANGE_RETURNED = 3;


unsigned char advanceStateMachine(unsigned int trackSensorAddresses[TOTAL_SENSORS][MAX_READINGS], struct Command *command);


#endif // TRAIN_CODE_C_STATE_MACHINE
