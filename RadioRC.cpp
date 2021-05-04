
#include "RadioRC.h"


volatile int RadioRC::mRoll, RadioRC::mPitch, RadioRC::mYaw, 
         RadioRC::mThrottle, RadioRC::mFlightMode;

bool ch1_state, ch2_state, ch3_state, ch4_state;
byte gChannelState = 0;
byte gRollByte, gPitchByte, gThrottleByte, gYawByte;

unsigned long mCurrentTime, mRollClock, 
              mThrottleClock, mYawClock, 
              mFlightModeClock, mPitchClock;
ISR(PCINT0_vect)
{
    mCurrentTime = micros();
    if(PINB & gRollByte) 
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
        if( RadioRC::mRoll < MIN_VAL) 
            RadioRC::mRoll = MIN_VAL;
        if( RadioRC::mRoll > MAX_VAL)
            RadioRC::mRoll = MAX_VAL;
        ch1_state = false;
    }

    if(PINB & gPitchByte) 
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
        if(RadioRC::mPitch< MIN_VAL) 
            RadioRC::mPitch= MIN_VAL;
        if(RadioRC::mPitch > MAX_VAL)
            RadioRC::mPitch = MAX_VAL;
        ch2_state = false;
    }

    if(PINB & gThrottleByte) 
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
        if(RadioRC::mThrottle< MIN_VAL) 
            RadioRC::mThrottle= MIN_VAL;
        if(RadioRC::mThrottle > MAX_VAL)
            RadioRC::mThrottle = MAX_VAL;
        ch3_state = false;
    }

    if(PINB & gYawByte) 
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
        if(RadioRC::mYaw < MIN_VAL) 
            RadioRC::mYaw= MIN_VAL;
        if(RadioRC::mYaw > MAX_VAL)
            RadioRC::mYaw = MAX_VAL;
        ch4_state = false;
    }
}

/**
 * @brief 
 */
int RadioRC::Initialize(unsigned int pRollPin,
                              unsigned int pPitchPin,
                              unsigned int pThrottlePin,
                              unsigned int pYawPin)
{
    Serial.println("RadioRC::Initialize");
    gRollByte = gPitchByte = gThrottleByte = gYawByte = 0;

    gRollByte = pow( 2, pRollPin - 8);
    gPitchByte = pow( 2, pPitchPin - 8);
    gThrottleByte = pow( 2, pThrottlePin - 8);
    gYawByte = pow( 2, pYawPin -8);

    Serial.println(gRollByte, BIN);
    Serial.println(gPitchByte, BIN);
    Serial.println(gThrottleByte, BIN);
    Serial.println(gYawByte, BIN);
    
    PCICR |= (1 << PCIE0);    // set PCIE0 to enable PCMSK0 scan
    PCMSK0 |= (1 << pRollPin - 8);  // set PCINT0 (digital input 8) to trigger an interrupt on state change
    PCMSK0 |= (1 << pPitchPin - 8);  // set PCINT0 (digital input 8) to trigger an interrupt on state change
    PCMSK0 |= (1 << pThrottlePin - 8);  // set PCINT0 (digital input 8) to trigger an interrupt on state change
    PCMSK0 |= (1 << pYawPin - 8);  // set PCINT0 (digital input 8) to trigger an interrupt on state change
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

