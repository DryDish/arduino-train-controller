#include "write.h"

int writeByte(unsigned char pin, int byte)
{ 
  int a;
  for(a=128;a>0;a=a/2)
  { 
    if((byte & a)!=0)
      writeBit(pin, 1);
    else 
    {
      writeBit(pin, 0);
    }
      
  }
  return 0;
}


int trackWriteByte(unsigned char pin, int byte)
{ 
  int a;
  for(a=128;a>0;a=a/2)
  { 
    if((byte & a)!=0)
      writeBit(pin, 1);
    else 
    {
      writeBit(pin, 0);
    }
      
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