#include "drive.h"

#include <math.h>
#include "wheel.h"

void drive_init(void) { wheel_init(); }

static inline int32_t abs_int(int32_t value)
{
    if (value < 0)
    {
        return -1 * value;
    }
    else
    {
        return value;
    }
}

static inline int32_t min_int(int32_t a, int32_t b)
{
    if (b < a)
    {
        return b;
    }
    else
    {
        return a;
    }
}

int16_t direction_to_degrees(direction_t dir)
{
    if (dir == DIRECTION_ID_FRONT)
        return DEGREES_FRONT;
    else if (dir == DIRECTION_ID_BACK)
        return DEGREES_BACK;
    else if (dir == DIRECTION_ID_LEFT)
        return DEGREES_LEFT;
    else if (dir == DIRECTION_ID_RIGHT)
        return DEGREES_RIGHT;

    return 0;
}

void drive_fix_vector(drive_vector_t* vec)
{
    if (vec->speed < 0)
    {
        vec->speed = -1 * vec->speed;
        vec->degrees += 180;
    }
    while (vec->degrees < 0)
    {
        vec->degrees += 360;
    }

    vec->degrees %= 360;
}

double drive_degrees_to_rad(double degrees)
{
    double rad;
    rad = degrees;
    rad *= 3.1415926f;
    rad /= 180;
    return rad;
}

int16_t drive_rad_to_degrees(double rad)
{
    double degrees;
    degrees = rad;
    degrees /= 3.1415926f;
    degrees *= 180;
    return (int16_t)degrees;
}

void drive_calc_xy(drive_vector_t vec, double* fb, double* lr)
{
    double angle;

    drive_fix_vector(&vec);
    angle = drive_degrees_to_rad(vec.degrees);
    *fb = vec.speed * cos(angle);
    *lr = vec.speed * sin(angle);
}

drive_vector_t drive_combine_vecs(drive_vector_t a,
                                  drive_vector_t b,
                                  int speed_max)
{
    drive_vector_t res;
    double a_lr;
    double a_fb;
    double b_lr;
    double b_fb;
    double rad;

    drive_calc_xy(a, &a_fb, &a_lr);
    drive_calc_xy(b, &b_fb, &b_lr);

    a_lr += b_lr;
    a_fb += b_fb;
    rad = atan2(a_lr, a_fb);

    res.degrees = drive_rad_to_degrees(rad);
    res.speed = (int32_t)sqrt((a_lr * a_lr) + (a_fb * a_fb));
    speed_max = min_int(speed_max, 255);
    res.speed = min_int(res.speed, speed_max);

    drive_fix_vector(&res);

    return res;
}

void go(drive_vector_t vec)
{
    double speed_fl;
    double speed_fr;
    double speed_bl;
    double speed_br;
    double speed_max;
    double angle;
    double speed_default;
    double scale;

    drive_fix_vector(&vec);

    angle = drive_degrees_to_rad(vec.degrees);
    speed_default = vec.speed;

    speed_fl = speed_default * cos(angle);
    speed_fr = speed_default * cos(angle);
    speed_bl = speed_default * -cos(angle);
    speed_br = speed_default * -cos(angle);

    speed_fl += speed_default * sin(angle);
    speed_fr += speed_default * -sin(angle);
    speed_bl += speed_default * sin(angle);
    speed_br += speed_default * -sin(angle);

    speed_max = speed_fl;
    if (speed_fr > speed_max) speed_max = speed_fr;
    if (speed_bl > speed_max) speed_max = speed_bl;
    if (speed_br > speed_max) speed_max = speed_br;

    scale = speed_default / speed_max;

    speed_fl *= scale;
    speed_fr *= scale;
    speed_bl *= scale;
    speed_br *= scale;

    set_speed(WHEEL_FL, (int16_t)(MOTOR_MULTIPLIER_FL * speed_fl), 0);
    set_speed(WHEEL_FR, (int16_t)(MOTOR_MULTIPLIER_FR * speed_fr), 0);
    set_speed(WHEEL_BL, (int16_t)(MOTOR_MULTIPLIER_BL * speed_bl), 0);
    set_speed(WHEEL_BR, (int16_t)(MOTOR_MULTIPLIER_BR * speed_br), 0);
}

void go_front()
{
    drive_vector_t vec;

    vec.degrees = direction_to_degrees(DIRECTION_ID_FRONT);
    vec.speed = 255;

    go(vec);
}

void go_back()
{
    drive_vector_t vec;

    vec.degrees = direction_to_degrees(DIRECTION_ID_BACK);
    vec.speed = 255;

    go(vec);
}

void go_right()
{
    drive_vector_t vec;

    vec.degrees = direction_to_degrees(DIRECTION_ID_RIGHT);
    vec.speed = 255;

    go(vec);
}

void go_left()
{
    drive_vector_t vec;

    vec.degrees = direction_to_degrees(DIRECTION_ID_LEFT);
    vec.speed = 255;

    go(vec);
}

void go_stop()
{
    drive_vector_t vec;

    vec.degrees = 0;
    vec.speed = 0;

    go(vec);
}
