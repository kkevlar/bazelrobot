#ifndef ECHO_H
#define ECHO_H

#include "robottypes.h"

void echo_init();
float echo_test_mm(uint8_t pin);
pin_t direction_to_echo_pin(direction_t dir);

#endif

