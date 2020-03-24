
#include <Arduino.h>
#include <stdint.h>
#include "robottypes.h" 

void inorandom_seed()
{
    uint32_t seed;

    pinMode(PIN_ANALOG_RANDOM, INPUT);
    delay(5);
    seed = analogRead(PIN_ANALOG_RANDOM);
    delay(5);
    seed *= analogRead(PIN_ANALOG_RANDOM);
    seed += 7;
    randomSeed(seed);
}

int inorandom(int max) { return random(max); }

