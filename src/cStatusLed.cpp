/*! \file cStatusLed.cpp */
#include "cStatusLed.h"

/*! \brief constructor 
    \param _gpiopin : io line used for the LED
    \param _onValue : value to set LED on
    \param _delayms : defines the blink period
*/
cStatusLed::cStatusLed(byte _gpiopin, bool _onValue, uint32_t _delayms) {
    mu8gpio = _gpiopin;
    mOnValue = _onValue;
    mu8phase = 0;
    pinMode(mu8gpio, OUTPUT);
    digitalWrite(mu8gpio, !mOnValue);
    SetState(0);
    SetDelay(_delayms);
    mtimer.Enable(true);
}

cStatusLed::~cStatusLed() = default;

/*! \brief Sets the LED status
    \param _state : guess what
*/
void cStatusLed::SetState(byte _state) {
    mu8State = _state;
}

/*! \brief Sets (update) the blink period
    \param _u32delayms : delay in ms
*/
void cStatusLed::SetDelay(uint32_t _u32delayms) {
    mu32delay = _u32delayms;
}

/*! \brief LED blink task
    \note Call this from the main loop
*/
void cStatusLed::Task() {
    if(mu8State == 0 || !mtimer.IsTimeOut())
        return;

    mtimer.SetTimeOut(mu32delay);

    if( mu8phase <= (mu8State * 2))
    {
        if(mu8phase & 0x01)
            digitalWrite(mu8gpio, mOnValue);
        else
            digitalWrite(mu8gpio, !mOnValue);
    }
    else if( mu8phase >= (mu8State * 2) + 4)
        mu8phase = 255;
    mu8phase++;
}

//eof cStatusLed.cpp
