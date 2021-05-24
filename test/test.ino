

void setupTimer2()
{ 
  TCCR2A |= 0; //page 203 - 206 ATmega328/P
  TCCR2B |= 2; //Page 206

  TIMSK2 = 1 << TOIE2;   //Timer2 Overflow Interrupt Enable - page 211 ATmega328/P   
  TCNT2 = 141;   //load the timer for its first cycle
}
bool flag = false;
unsigned int number = 0;

ISR(TIMER2_OVF_vect)
{
    flag = flag ^ 1;    
    
    //Serial.println("hello!");
}

void setup()
{
    Serial.begin(9600);
    
    setupTimer2();
    
}

void loop()
{
    //Serial.println(TCNT2);
    if (flag == true)
    {
        Serial.print("Hello from here!");
    }
    else
    {
        Serial.print("hello from there!");
    }
     Serial.println();
     delay(1000);
}