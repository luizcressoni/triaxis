/*! \file stepper.h */
#pragma once

void stepper_setup();
bool stepper_loop(bool _justrun);
void stepper_move(int _delta);
long stepper_getpos();
void stepper_stop();
void stepper_step(bool _forward);

//eof stepper.h