/*! \file stepper.h */
#pragma once

void stepper_setup();
bool stepper_loop();
void stepper_move(int _delta);

//eof stepper.h