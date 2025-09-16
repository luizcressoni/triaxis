/*! \file ntp.h */
#pragma once
#include <Arduino.h>

void init_ntp();
void printLocalTime();
void update_time();
bool minute_changed(byte flipseconds);

//eof ntp.h