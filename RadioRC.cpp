
#include "RadioRC.h"


volatile int RadioRC::mRoll, RadioRC::mPitch, RadioRC::mYaw, 
         RadioRC::mThrottle, RadioRC::mFlightMode;

bool ch1_state, ch2_state, ch3_state, ch4_state;
byte gChannelState = 0;

unsigned long mCurrentTime, mRollClock, 
              mThrottleClock, mYawClock, 
              mFlightModeClock, mPitchClock;
ISR(PCINT0_vect)
{
    mCurrentTime = micros();
    if(PINB & B00000001) 
    {
        if( ch1_state == false)
        {                                   
            mRollClock = mCurrentTime;
            ch1_state = true;
        }
    }
    else if( ch1_state )
    {   
        RadioRC::mRoll = mCurrentTime - mRollClock;
        ch1_state = false;
    }

    if(PINB & B00000010) 
    {
        if( ch2_state == false)
        {                                   
            mPitchClock = mCurrentTime;
            ch2_state = true;
        }
    }
    else if( ch2_state )
    {   
        RadioRC::mPitch = mCurrentTime - mPitchClock;
        ch2_state = false;
    }

    if(PINB & B00000100) 
    {
        if( ch3_state == false )
        {                                   
            mThrottleClock = mCurrentTime;
            ch3_state = true;
        }
    }
    else if( ch3_state  )
    {   
        RadioRC::mThrottle = mCurrentTime - mThrottleClock;
        ch3_state = false;
    }

    if(PINB & B00001000) 
    {
        if( ch4_state == false )
        {                                   
            mYawClock = mCurrentTime;
            ch4_state = true;
        }
    }
    else if( ch4_state )
    {   
        RadioRC::mYaw = mCurrentTime - mYawClock;
        ch4_state = false;
    }
}

/**
 * @brief 
 */
int RadioRC::Initialize()
{
    Serial.println("RadioRC::Initialize");
    PCICR |= (1 << PCIE0);    // set PCIE0 to enable PCMSK0 scan
    PCMSK0 |= (1 << PCINT0);  // set PCINT0 (digital input 8) to trigger an interrupt on state change
    PCMSK0 |= (1 << PCINT1);  // set PCINT1 (digital input 9)to trigger an interrupt on state change
    PCMSK0 |= (1 << PCINT2);  // set PCINT2 (digital input 10)to trigger an interrupt on state change
    PCMSK0 |= (1 << PCINT3);  // set PCINT3 (digital input 11)to trigger an interrupt on state change
    return 0;
}

/**
 * @brief 
 */
void RadioRC::PrintValues()
{
    Serial.print(F("Roll : "));    
    Serial.print(mRoll);
    Serial.print(F("    Pitch: "));    
    Serial.print(mPitch);
    Serial.print(F("    Fuel: "));    
    Serial.print(mThrottle);
    Serial.print(F("    Yaw: "));    
    Serial.print(mYaw);
    Serial.print(F("    F. Mode: "));    
    Serial.println(mFlightMode);
    delay(250);
}

