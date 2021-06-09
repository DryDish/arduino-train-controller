#if !defined(TRAIN_CODE_C_SEND_COMMAND)
#define TRAIN_CODE_C_SEND_COMMAND

#include "command.h"
#include "bytesAndbools.h"
#include "definitions.h"
#include <Arduino.h>


void sendState(unsigned char *ptr_byteOne, unsigned char *ptr_sizeTwo, unsigned char *ptr_checksum, bool printoutState);

#endif // TRAIN_CODE_C_SEND_COMMAND
