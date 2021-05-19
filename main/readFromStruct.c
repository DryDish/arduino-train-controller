#include "readFromStruct.h"
/*
char* readStructData(struct Instruction instruction)
{
    unsigned char preamble1[8];
    *preamble1 = instruction.preamble[0];
    unsigned char preamble2[8];
    *preamble2 = instruction.preamble[1];
    unsigned char byteOne[4];
    *byteOne = instruction.byteOne;
    unsigned char byteTwo[8];
    *byteTwo = instruction.byteTwo;
    unsigned char checksum[8];
    *checksum = instruction.checksum;

    //sscanf(byteOne, "%d", &byteOne); // Using sscanf


    char* stringToReturn;
    stringToReturn = malloc(14+strlen(preamble1)+strlen(preamble2)+20+strlen(byteOne)+14+strlen(byteTwo)+15+strlen(checksum));
    strcpy(stringToReturn, "preamble is: ");
    strcat(stringToReturn, preamble1);
    strcat(stringToReturn, preamble2);
    strcat(stringToReturn, " engine number is: ");
    strcat(stringToReturn, byteOne);
    strcat(stringToReturn, " byteTwo is: ");
    strcat(stringToReturn, byteTwo);
    strcat(stringToReturn, " checksum is: ");
    strcat(stringToReturn, checksum);
    //printf(stringToReturn);

    return stringToReturn;
    //return "The preamble is : " , (preamble1 + preamble2) , " byteOne is: " , byteOne , " byteTwo is: ", byteTwo ," checksum is: ", checksum;
}
*/
