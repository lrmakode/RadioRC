
#ifndef RadioRC_h
#define RadioRC_h
#include <arduino.h>

/**
 * @brief Enables Pinchange intrupts for PIN 8,11
 * @brief PIN10 must be connected to Throttle Channel
 * @Return If failed return -1 on Sucess Returns 0
 */
class RadioRC
{
    public:
        
        static int Initialize(unsigned int pRollPin,
                              unsigned int pPitchPin,
                              unsigned int pThrottlePin,
                              unsigned int pYawPin);
        /**
        * @brief 
        */
        static void PrintValues();

        static volatile int mRoll, mPitch, mYaw, 
                            mThrottle, mFlightMode;

};

#endif //RadioRC_h

