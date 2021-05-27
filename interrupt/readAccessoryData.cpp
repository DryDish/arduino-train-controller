#include "readAccessoryData.h";

void readAccessoryData(unsigned int trackSensorAddresses[TOTAL_SENSORS][MAX_READINGS])
{
    for (short i = 0; i < TOTAL_SENSORS; i++)
   {
      /*
      unsigned char reading = digitalRead(trackSensorAddresses[i][0]);
      if (reading != 1)
      {
         
         Serial.print("Triggered sensor: < ");

         // adjust the output to match sensor numbers instead of array index
         // index 0 corresponds to sensor 1, index 7 corresponds to sensor 9 etc. There is no sensor 7
         if (i > 5)
         {
            Serial.print(i + 2); // there is no sensor 7 so increase output by 2
         }
         else
         {

            Serial.print(i + 1); // index begins at 0
         }

         Serial.print(" - index: ");
         Serial.print(i);

         Serial.print(" - pin: ");
         Serial.print(trackSensorAddresses[i][0]);
         Serial.println(" >");
         trackSensorAddresses[i][1]++;
      }*/
   }
}
