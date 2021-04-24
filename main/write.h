#ifndef C_REPO_WRITE_H
#define C_REPO_WRITE_H

#ifdef __cplusplus
 extern "C" {
#endif


int writeByte(unsigned char pin ,int byte);
int writeBit(unsigned char pin, unsigned char bit);


#ifdef __cplusplus
}
#endif

#endif //C_REPO_WRITE_H
