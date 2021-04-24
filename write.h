#ifndef C_REPO_WRITE_H
#define C_REPO_WRITE_H

/*
void write0();
void write1();
void writeByte(unsigned char byte);
*/

int writeByte(unsigned char commandPin ,int byte);
int writeBit(unsigned char commandPin, unsigned char bit);

#endif //C_REPO_WRITE_H
