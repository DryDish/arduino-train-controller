#include "setupTimer2Overflow.h"


void setupTimer2Overflow()
{
  //Timer2 Settings: Timer Prescaler /8, mode 0
  //Timer clock = 16MHz/8 = 2MHz oder 0,5usec
  // 
  TCCR2A = 0; //page 203 - 206 ATmega328/P

  TCCR2B = 2; //Page 206
  
/*         bit 2     bit 1     bit0
            0         0         0       Timer/Counter stopped 
            0         0         1       No Prescaling
            0         1         0       Prescaling by 8
            0         1         1       Prescaling by 32
            1         0         0       Prescaling by 64
            1         0         1       Prescaling by 128
            1         1         0       Prescaling by 256
            1         1         1       Prescaling by 1024
*/
  TIMSK2 = 1<<TOIE2;   //Timer2 Overflow Interrupt Enable - page 211 ATmega328/P   
  TCNT2=TIMER_SHORT;   //load the timer for its first cycle
} 
