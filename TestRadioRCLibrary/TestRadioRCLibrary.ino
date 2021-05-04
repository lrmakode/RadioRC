#include <RadioRC.h>

RadioRC gRC_Control;
void setup()
{
   Serial.begin(57600);      //Start the serial connetion @ 57600bps
   delay(250);               //Give the gyro time to start 
   gRC_Control.Initialize(8,9,10,11);
}
void loop()
{
    gRC_Control.PrintValues();
}
