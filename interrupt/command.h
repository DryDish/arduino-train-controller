#ifndef TRAIN_CODE_C_COMMAND
#define TRAIN_CODE_C_COMMAND

struct Command
{
    unsigned short preamble;
    unsigned char blank1;
    unsigned char byteOne;
    unsigned char blank2;
    unsigned char byteTwo;
    unsigned char blank3;
    unsigned char checksum;
    unsigned char endChar;
};

#endif // TRAIN_CODE_C_COMMAND