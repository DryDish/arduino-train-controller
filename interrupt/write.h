#if !defined(TRAIN_CODE_C_WRITE)
#define TRAIN_CODE_C_WRITE

#include "definitions.h"
#include "command.h"
#include <Arduino.h>

void writeBit();
void convertByteToBinary(unsigned char *byte, unsigned short *position);
void convertBitToBinary(unsigned char *byte);
void convertPositionsToBinary(unsigned char *byte, unsigned short *position);

#endif // TRAIN_CODE_C_WRITE
