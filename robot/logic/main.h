
#ifndef MAIN_H
#define MAIN_H

#include "testoptions.h"
#include <Arduino.h>
#include "drive.h"
#include "shoot.h"
#include "switch.h"
#include "echo.h"
#include "lcd.h"
#include "control.h"
#include "aim.h"
#include "collect.h"

#ifndef TEST_NO_GAME
void main_setup();
void main_loop();
#endif

#endif

