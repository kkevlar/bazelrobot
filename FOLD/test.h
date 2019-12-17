
#ifndef TEST_H
#define TEST_H

#include "testoptions.h"
#include <Arduino.h>
#include "drive.h"
#include "switch.h"
#include "echo.h"
#include "control.h"
#include "collect.h"
#include "lcd.h"
#include "shoot.h"
#include "wheel.h"

#ifdef TEST_NO_GAME
void test_setup();
void test_loop();
#endif

#endif

