
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
    if ( pRollPin == 8 
        || pPitchPin == 8
        || pThrottlePin == 8
        || pYawPin == 8 ) 
    {
        PCMSK0 |= (1 << PCINT0);  // set PCINT0 (digital input 8) to trigger an interrupt on state change
    }

    if ( pRollPin == 9 
        || pPitchPin == 9
        || pThrottlePin == 9
        || pYawPin == 9 ) 
    {
        PCMSK0 |= (1 << PCINT1);  // set PCINT1 (digital input 9)to trigger an interrupt on state change
    }

    if ( pRollPin == 10
        || pPitchPin == 10
        || pThrottlePin == 10
        || pYawPin == 10 ) 
    {
        PCMSK0 |= (1 << PCINT2);  // set PCINT2 (digital input 10)to trigger an interrupt on state change
    }

    if ( pRollPin == 11 
        || pPitchPin == 11
        || pThrottlePin == 11
        || pYawPin == 11 ) 
    {
        PCMSK0 |= (1 << PCINT3);  // set PCINT3 (digital input 11)to trigger an interrupt on state change
    }

    if ( pRollPin == 12 
        || pPitchPin == 12
        || pThrottlePin == 12
        || pYawPin == 12 ) 
    {
        PCMSK0 |= (1 << PCINT4);  // set PCINT4 (digital input 12)to trigger an interrupt on state change
    }

    if ( pRollPin == 13 
        || pPitchPin == 13
        || pThrottlePin == 13
        || pYawPin == 13 ) 
    {
        PCMSK0 |= (1 << PCINT5);  // set PCINT5 (digital input 13)to trigger an interrupt on state change
    }
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

