
#ifndef SHOOT_H
#define SHOOT_H

#include "testoptions.h"
#include <Wire.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>
#include "wiring.h"
#include "lcd.h"


void shoot_init(void);
void shoot_flywheel_left_start();
void shoot_flywheel_right_start();
void shoot_flywheel_left_stop();
void shoot_flywheel_right_stop();
void shoot_flywheel_both_start();
void shoot_flywheel_both_stop();
void shoot_conveyor_left_start();
void shoot_conveyor_right_start();
void shoot_conveyor_both_start();
void shoot_conveyor_left_stop();
void shoot_conveyor_right_stop();
void shoot_conveyor_both_stop();
void shoot_indexer_start();
void shoot_indexer_stop();
void shoot_indexer_spam_forward();
void shoot_indexer_spam_reversed();
void shoot_indexer_spam(void);

#endif
