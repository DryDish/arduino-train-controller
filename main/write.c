#include "write.h"

int writeByte(unsigned char pin, int byte)
{ 
  int a;
  for(a=256;a>0;a=a/2)
  { 
      
  }
  return 0;
}


int writeBit(unsigned char pin, unsigned char b)
{ 
  if(b==0)
  {
    digitalWrite(pin,0x1);
    delayMicroseconds(116);
    digitalWrite(pin,0x0);
    delayMicroseconds(116);
  }
  else
  {
    digitalWrite(pin, 0x1);
    delayMicroseconds(58);
    digitalWrite(pin, 0x0);
    delayMicroseconds(58);
  }
  return 0;
}
