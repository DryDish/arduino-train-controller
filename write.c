#include "write.h"

int writeByte(unsigned char commandPin, int byte)
{ 
  int a;
  for(a=128;a>0;a=a/2)
  { 
    if((byte & a)!=0)
      writeBit(commandPin, 1);
    else 
    {
      writeBit(commandPin, 0);
    }
      
  }
  return 0;
}

int writeBit(unsigned char commandPin, unsigned char b)
{ 
  if(b==0)
  {
    digitalWrite(commandPin,0x1);
    delayMicroseconds(116);
    digitalWrite(commandPin,0x1);
    delayMicroseconds(116);
  }
  else
  {
    digitalWrite(commandPin,0x1);
    delayMicroseconds(58);
    digitalWrite(commandPin,0x1);
    delayMicroseconds(58);
  }
  return 0;
}

/*
void write1()
{
    digitalWrite(A, HIGH);
    digitalWrite(B, LOW);
    delayMicroseconds(48);
    digitalWrite(A, LOW);
    digitalWrite(B, HIGH);
    delayMicroseconds(48);
}

void write0()
{
    digitalWrite(A, HIGH);
    digitalWrite(B, LOW);
    delayMicroseconds(96);
    digitalWrite(A, LOW);
    digitalWrite(B, HIGH);
    delayMicroseconds(96);
}

 void writeByte(unsigned char byte)
 {
    for (int i = 7; i >= 0; i--) {
      if ((byte & (1 << i)) > 0) {
        write1();
      } else {
        write0();
      }
    }
  }
*/