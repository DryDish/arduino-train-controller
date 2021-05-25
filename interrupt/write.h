#if !defined(TRAIN_CODE_C_WRITE)
#define TRAIN_CODE_C_WRITE

#include "definitions.h"
#include "command.h"
#include <Arduino.h>

//void writeBit();
//void convertByteToBinary(unsigned char byte, unsigned char *position, bool *bitIsOne, bool *hasBit);
//void convertBitToBinary(unsigned char *byte, bool *bitIsOne);
//void convertPositionsToBinary(unsigned char *byte, unsigned char *position, bool *bitIsOne);
void sendCommand(struct Command *command, bool *bitIsOne, bool *hasBit);

#endif // TRAIN_CODE_C_WRITE
