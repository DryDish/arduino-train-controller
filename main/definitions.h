#ifndef C_REPO_DEFINITIONS_H
#define C_REPO_DEFINITIONS_H

// Static variables
#define blankPreamble 0x00
#define blankSeparator 0
#define blankEndOfMessage 0
#define blankEngineNumber 0
#define blankCommand 0
#define blankEndOfMessage 0

#define PREAMBLE 255
#define SEPARATOR 0
#define END_OF_MESSAGE 1

// ----------- Commands -----------

// Speed
#define SPEED0 0x60
#define HARDSTOP 0x61
#define SPEED1 0x64
#define SPEED2 0x65
#define SPEED3 0x66
#define SPEED4 0x67
#define SPEED5 0x68
#define SPEED6 0x69
#define SPEED7 0x6A
#define SPEED8 0x6B
#define SPEED9 0x6C
#define SPEED10 0x6D
#define SPEED11 0x6E
#define SPEED12 0x6F

// Sounds
#define SOUND_OFF 0x80
#define SOUND_HORN 0x81
#define HORN3 0x82
#define HORN4 0x83
#define HORN5 0x84
#define SOUND_BELL 0x85
#define SOUND_WHISTLE 0x86
#define SOUND_JUSTDIE 0x87
#define SOUND_CHUG 0x88
#define HORN10 0x89

#endif //C_REPO_DEFINITIONS_H