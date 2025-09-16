/*! \file cStatusLed.h */
#pragma once
#include "ctimer.h"

#define LED_STATUS_OFFLINE  3
#define LED_STATUS_ONLINE   1
#define LED_STATUS_CONFIG   2

/*! \class cStatusLed 
    \brief Implements a blinking LEd with status.
    \note LED will blink as may times as set by the status, then pause a bit
*/
class cStatusLed {
protected:
    byte        mu8State,
                mu8phase,
                mu8gpio;
    bool        mOnValue;
    uint32_t    mu32delay;
    cTimer      mtimer;
public:
    cStatusLed(byte _gpiopin, bool _onValue, uint32_t _delayms = 200);
    ~cStatusLed();
    void        SetState(byte _state);
    void        SetDelay(uint32_t _u32delayms);
    void        Task();
    byte        GetState(){ return mu8State;};
};

//eof cStatusLed.h
