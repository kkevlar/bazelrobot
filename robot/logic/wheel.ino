
#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include "wheel.h"

Adafruit_MotorShield AFMS_LEFT(
    MOTOR_SHEILD_ADDRESS_LEFT);  // Rightmost jumper closed
Adafruit_MotorShield AFMS_RIGHT(
    MOTOR_SHEILD_ADDRESS_RIGHT);  // Rightmost jumper closed

uint8_t wheel_has_init = 0;
Adafruit_DCMotor *fl;
Adafruit_DCMotor *fr;
Adafruit_DCMotor *bl;
Adafruit_DCMotor *br;

void wheel_init(void)
{
    if (!wheel_has_init)
    {
        AFMS_LEFT.begin();   // create with the default frequency 1.6KHz
        AFMS_RIGHT.begin();  // create with the default frequency 1.6KHz

        fl = AFMS_LEFT.getMotor(MOTOR_SHEILD_PORT_FL);
        bl = AFMS_LEFT.getMotor(MOTOR_SHEILD_PORT_BL);
        fr = AFMS_RIGHT.getMotor(MOTOR_SHEILD_PORT_FR);
        br = AFMS_RIGHT.getMotor(MOTOR_SHEILD_PORT_BR);

        fl->run(RELEASE);
        fr->run(RELEASE);
        bl->run(RELEASE);
        br->run(RELEASE);
        wheel_has_init = 1;
    }
}

// Assumed that if time = 0, then current speed is zero
void set_speed(uint8_t wheel, int16_t speed, int time)
{
    Adafruit_DCMotor *motor;
    time = 0;

    if (wheel & WHEEL_FL)
        motor = fl;
    else if (wheel & WHEEL_FR)
        motor = fr;
    else if (wheel & WHEEL_BL)
        motor = bl;
    else
        motor = br;

    if (speed < 0)
    {
        speed = -speed;
        motor->run(BACKWARD);
    }
    else if (speed > 0)
    {
        motor->run(FORWARD);
    }
    if (speed > WHEEL_GLOBAL_SPEED_CAP) speed = WHEEL_GLOBAL_SPEED_CAP;

    if (time == 0 || speed == 0)  // no ramp down
    {
        motor->setSpeed(speed);
        if (speed == 0) motor->run(RELEASE);
        return;
    }
    for (int i = 0; i < speed; i++)
    {
        motor->setSpeed(i);
        delay(time / speed);
    }

    if (speed == 0) motor->run(RELEASE);
}
