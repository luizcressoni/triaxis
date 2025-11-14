/*! \file stepper.cpp */
//#include <Arduino.h>
#include <AccelStepper.h>
#include "defines.h"
#include "stepper.h"
#include "ctimer.h"

/*! I'm using a 28BYJ-48 stepper with a ULN2003 phase driver
    You better check your driver and wiring to match.
    Values are in defines.h
*/

/**** stepper dynamics *****/
#define MAX_SPEED   2000    //these values are ok for my machine, powering the stepper with 12V
#define MAX_ACCEL   400

AccelStepper stepper(AccelStepper::HALF4WIRE, STEPPER_A, STEPPER_C, STEPPER_B, STEPPER_D);

cTimer IdleTimer;

/*! \brief Configures the stepper driver */
void stepper_setup() {  
    stepper.setMaxSpeed(MAX_SPEED);
    stepper.setAcceleration(MAX_ACCEL);
    stepper.disableOutputs();
    stepper.setCurrentPosition(0);
    IdleTimer.Enable(false);
}

/*! \brief loop. Add this to the main loop 
    \note I'm disabling the stepper when there are no pulses
*/
bool stepper_loop(bool _justrun) {
    static bool was_running = false;
    if(_justrun){
        return stepper.run();
    }
    bool running = stepper.run();
    if(was_running && !running)
    {
        IdleTimer.SetTimeOut(2000);
        stepper.setCurrentPosition(0);
    }
    was_running = running;

    if(IdleTimer.IsTimeOut())
    {
        stepper.disableOutputs();
        IdleTimer.Enable(false);
    }

    return running;
}

/*! \brief Sends command to spin the stepper
    \param _delta: number of pulses. We only need relative motion anyway
*/
void stepper_move(int _delta){
    stepper.enableOutputs();
    //delay(500);
    stepper.move(_delta);
}


long stepper_getpos()
{
    return stepper.currentPosition();
}

void stepper_stop()
{
    stepper.runToNewPosition(stepper.currentPosition());
    //stepper.stop();
}

void stepper_step(bool _forward){
     stepper.enableOutputs();
    if(_forward)
        stepper.move(1);
    else
        stepper.move(-1);
}
//eof stepper.cpp