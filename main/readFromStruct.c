#include "readFromStruct.h"
/*
char* readStructData(struct Instruction instruction)
{
    unsigned char preamble1[8];
    *preamble1 = instruction.preamble[0];
    unsigned char preamble2[8];
    *preamble2 = instruction.preamble[1];
    unsigned char engineNumber[4];
    *engineNumber = instruction.engineNumber;
    unsigned char command[8];
    *command = instruction.command;
    unsigned char checksum[8];
    *checksum = instruction.checksum;

    //sscanf(engineNumber, "%d", &engineNumber); // Using sscanf


    char* stringToReturn;
    stringToReturn = malloc(14+strlen(preamble1)+strlen(preamble2)+20+strlen(engineNumber)+14+strlen(command)+15+strlen(checksum));
    strcpy(stringToReturn, "preamble is: ");
    strcat(stringToReturn, preamble1);
    strcat(stringToReturn, preamble2);
    strcat(stringToReturn, " engine number is: ");
    strcat(stringToReturn, engineNumber);
    strcat(stringToReturn, " command is: ");
    strcat(stringToReturn, command);
    strcat(stringToReturn, " checksum is: ");
    strcat(stringToReturn, checksum);
    //printf(stringToReturn);

    return stringToReturn;
    //return "The preamble is : " , (preamble1 + preamble2) , " engineNumber is: " , engineNumber , " command is: ", command ," checksum is: ", checksum;
}
*/
