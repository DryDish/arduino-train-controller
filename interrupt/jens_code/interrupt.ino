#include "definitions.h"

#define dirpin     2                   // sense for direction
#define DCC_PIN    4                   // Arduino pin for DCC out 
#define sw101      8                   // switch 101 turn when low
#define sw102      9                   // switch 102 turn when low
#define ledpin     13                  // led
#define TIMER_SHORT 0x8D               // 58usec pulse length 141 255-141=114
#define TIMER_LONG  0x1B               // 116usec pulse length 27 255-27 =228
#define PREAMBLE  0                    // definitions for state machine
#define SEPERATOR 1                    // definitions for state machine
#define SENDBYTE  2                    // definitions for state machine

unsigned char state = PREAMBLE;        // start of state maschine
unsigned char preamble_count = 16;     // number of bits in preamble
unsigned char outbyte = 0;             //
unsigned char cbit = 0x80;             //         
unsigned char last_timer=TIMER_SHORT;  // store last timer value
unsigned char flag=0;                  // used for short or long pulse
unsigned char locoSpeed=0;             // variables for throttle
unsigned char dir=1;                   //forward
unsigned char locoAdr=36;              // this is the (fixed) address of the loco
unsigned char addr, data, xdata;       //
int msgIndex=0;                        //
int byteIndex=0;                       //
bool sound = false;                    //    
bool second_isr = false;               // pulse up or down
bool turn_101 = false;                 //
bool turn_102 = false;                 //
bool last101 = true;                   //
bool last102 = true;                   //
struct Message                         // buffer for command
{
   unsigned char data[7];              // max number of bytes in the struct
   unsigned char len;                  // indicating how many bytes are used
};

#define MAXMSG  2

struct Message msg[MAXMSG] = 
{ 
    { { 0xFF,     0, 0xFF, 0, 0, 0, 0}, 3},   // idle msg
    { { locoAdr, 0,  0, 0, 0, 0, 0}, 3}       // locoMsg with 128 speed steps
}; 
                                
void SetupTimer2();
ISR(TIMER2_OVF_vect);
void checkshift();
void shift101();
void shift102();
void setup(void); 
void loop(void); 
void assemble_dcc_msg(); 


void SetupTimer2()
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
} // end SetupTimer2

ISR(TIMER2_OVF_vect) //Timer2 overflow interrupt vector handler
{
  //Capture the current timer value TCTN2. This is how much error we have
  //due to interrupt latency and the work in this function
  //Reload the timer and correct for latency.  
  unsigned char latency;
  
  if (second_isr) 
  {  // for every second interupt just toggle signal
     digitalWrite(DCC_PIN,1);
     second_isr = false;    
     latency=TCNT2;    // set timer to last value
     TCNT2=latency+last_timer; 
  }
  else  
  {  // != every second interrupt, advance bit or state
     digitalWrite(DCC_PIN,0);
     second_isr = true;
     switch(state)  
     {
       case PREAMBLE:
           flag=1; // short pulse
           preamble_count--;
           if (preamble_count == 0)  
           {  
              state = SEPERATOR; // advance to next state
              msgIndex++; // get next message
              if (msgIndex >= MAXMSG)  
              {  
                msgIndex = 0; 
              }  
              byteIndex = 0; //start msg with byte 0
           }
           break;
        case SEPERATOR:
           flag=0; // long pulse and then advance to next state
           state = SENDBYTE; // goto next byte ...
           outbyte = msg[msgIndex].data[byteIndex];
           cbit = 0x80;  // send this bit next time first         
           break;
        case SENDBYTE:
           if ((outbyte & cbit)!=0)  
           { 
              flag = 1;  // send short pulse
           }
           else  
           {
              flag = 0;  // send long pulse
           }
           cbit = cbit >> 1;
           if (cbit == 0)  
           {  // last bit sent 
              //Serial.print(" ");
              byteIndex++;
              if (byteIndex >= msg[msgIndex].len) // is there a next byte?  
              {  // this was already the XOR byte then advance to preamble
                 state = PREAMBLE;
                 preamble_count = 16;
                 //Serial.println();
              }
              else  
              {  // send separator and advance to next byte
                 state = SEPERATOR ;
              }
           }
           break;
     }   
 
     if (flag)  
     {  // data = 1 short pulse
        latency=TCNT2;
        TCNT2=latency+TIMER_SHORT;
        last_timer=TIMER_SHORT;
        //Serial.print('1');
     }  
     else  
     {   // data = 0 long pulse
        latency=TCNT2;
        TCNT2=latency+TIMER_LONG; 
        last_timer=TIMER_LONG;
       // Serial.print('0');
     } 
  }
} // end ISR(TIMER2_OVF_vect)

void checkshift()
{
   int x,y;
  
   x=digitalRead(sw101); // pin 8
   y=digitalRead(sw102); // pin 9
   
   if(last101 != x)
   {
      if(x == HIGH)
      {
        turn_101=false;
      }
      else
      {
        turn_101=true;
      }
      last101=x;
      shift101();
   }

   if(last102 != y)
   {
      if(y == HIGH)
      {
        turn_102=false;
      }
      else
      {
        turn_102=true;
      }
      last102=y;
      shift102();
   }

} // end checkshift
void shift101()
{
  if(turn_101 == true)
  {
    addr=154;
    data=248;
    assemble_dcc_msg();
    delay(100);
    data=240;
    assemble_dcc_msg();
    delay(100);
  }
  
  if(turn_101 == false)
  {
    addr=154;
    data=249;
    assemble_dcc_msg();
    delay(100);
    data=241;
    assemble_dcc_msg();
    delay(100);
  }
} // end shift101

void shift102()
{
  if(turn_102 == true)
  {
    addr=154;
    data=250;
    assemble_dcc_msg();
    delay(100);
    data=242;
    assemble_dcc_msg();
    delay(100);
  }
  if(turn_102 == false)
  {
    addr=154;
    data=251;
    assemble_dcc_msg();
    delay(100);
    data=243;
    assemble_dcc_msg();
    delay(100);
  }
} // end shift102


void setup(void) 
{
  Serial.begin(9600);
  pinMode(dirpin,INPUT_PULLUP);         // pin 2
  pinMode(DCC_PIN,OUTPUT);              // pin 4 this is for the DCC Signal
  pinMode(ledpin,OUTPUT);               // pin 13 the onboard LED
  pinMode(sw101,INPUT_PULLUP);          // pin 8 switch 101
  pinMode(sw102,INPUT_PULLUP);          // pin 9 switch 102
  SetupTimer2();                        // Start the timer  
  delay(100);
} // end setup

void loop(void) 
{
    int i=digitalRead(dirpin);
 
   checkshift();
 
   if(i==HIGH)
     data = 0x49;
   else
     data = 0x69;
   addr = locoAdr;  
   assemble_dcc_msg();
   delay(100);	
} // end loop



void assemble_dcc_msg() 
{
   xdata = addr ^ data;
   noInterrupts();  // make sure that only "matching" parts of the message are used in ISR
   msg[1].data[0] = addr;
   msg[1].data[1] = data;
   msg[1].data[2] = xdata;
   if(data != 102)
   {
     Serial.print(addr);
     Serial.print("  ");
     Serial.println( data);
   }
   interrupts();
}

