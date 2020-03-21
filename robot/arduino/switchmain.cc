
#include "switch.h"
#include <Arduino.h>

void setup()
{
  pinMode(13, OUTPUT);
}

void loop()
{
switch_test_all();
digitalWrite(13, LOW);
delay(1000);
digitalWrite(13, HIGH);
delay(1000);
}

