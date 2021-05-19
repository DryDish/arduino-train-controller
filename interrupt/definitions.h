#ifndef TRAIN_CODE_C_DEFINITIONS
#define TRAIN_CODE_C_DEFINITIONS

// These externs fix the missing declaration errors
// It essentially promises the compiler that they are/will be filled soon
/*
extern int TIMSK2;
extern int TCCR2A;
extern int TCCR2B;
extern int TOIE2;
extern int TCNT2;
*/

// Static variables
#define BLANK_PREAMBLE 0x0000
#define BLANK_BYTE_ONE 0
#define BLANK_BYTE_TWO 0
#define PREAMBLE 0xFFFF
#define SEPARATOR 0
#define END_OF_MESSAGE 1

// Speed
#define SPEED0 0x60
#define HARDSTOP 0x61
#define SPEED1 0x62
#define SPEED2 0x63
#define SPEED3 0x64
#define SPEED4 0x65
#define SPEED5 0x66
#define SPEED6 0x67
#define SPEED7 0x68
#define SPEED8 0x69
#define SPEED9 0x6A
#define SPEED10 0x6B
#define SPEED11 0x6C
#define SPEED12 0x6D
#define SPEED13 0x6E
#define SPEED14 0x6F


#endif // TRAIN_CODE_C_DEFINITIONS





