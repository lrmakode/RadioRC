#include <RadioRC.h>

RadioRC gRC_Control;
void setup()
{
   gRC_Control.Initialize();
   Serial.begin(57600);      //Start the serial connetion @ 57600bps
   delay(250);               //Give the gyro time to start 
  
}
void loop()
{
    gRC_Control.PrintValues();
}
