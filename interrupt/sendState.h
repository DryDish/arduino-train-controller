#if !defined(TRAIN_CODE_C_SEND_COMMAND)
#define TRAIN_CODE_C_SEND_COMMAND

#include "command.h"
#include "definitions.h"
#include <Arduino.h>

extern unsigned char lastTimer;
void sendState(struct Command *command, bool *printoutState);

#endif // TRAIN_CODE_C_SEND_COMMAND
