/*! \file stepper.cpp */
//#include <Arduino.h>
#include <AccelStepper.h>
#include "defines.h"
#include "stepper.h"


/*! I'm using a 28BYJ-48 stepper with a ULN2003 phase driver
    You better check your driver and wiring to match.
    Values are in defines.h
*/

/**** stepper dynamics *****/
#define MAX_SPEED   3000    //these values are ok for my machine, powering the stepper with 12V
#define MAX_ACCEL   500

AccelStepper stepper(AccelStepper::FULL4WIRE, STEPPER_A, STEPPER_C, STEPPER_B, STEPPER_D);

/*! \brief Configures the stepper driver */
void stepper_setup() {  
    stepper.setMaxSpeed(MAX_SPEED);
    stepper.setAcceleration(MAX_ACCEL);
}

/*! \brief loop. Add this to the main loop 
    \note I'm disabling the stepper when there are no pulses
*/
bool stepper_loop() {
    bool running = stepper.run();
    if(!running)
        stepper.disableOutputs();
    return running;
}

/*! \brief Sends command to spin the stepper
    \param _delta: number of pulses. We only need relative motion anyway
*/
void stepper_move(int _delta){
    stepper.move(_delta);
}

//eof stepper.cpp