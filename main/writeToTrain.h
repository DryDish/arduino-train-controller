#ifndef C_REPO_WRITETOTRAIN_H
#define C_REPO_WRITETOTRAIN_H

#ifdef __cplusplus
 extern "C" {
#endif


#include "instruction.h"

int writeToTrain(unsigned char pin, struct Instruction instruction);


#ifdef __cplusplus
}
#endif

#endif //C_REPO_WRITETOTRAIN_H
