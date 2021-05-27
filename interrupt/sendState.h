#if !defined(TRAIN_CODE_C_SEND_COMMAND)
#define TRAIN_CODE_C_SEND_COMMAND

#include "command.h"
#include "bytesAndbools.h"
#include "definitions.h"
#include <Arduino.h>


void sendState(struct Command *command);

#endif // TRAIN_CODE_C_SEND_COMMAND
