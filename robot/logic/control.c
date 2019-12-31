
#include "robot/logic/control.h"
#include <stdint.h>

#include "robot/hwhdrs/echo.h"

static float signum(float f)
{
    if (f > 0) return 1;
    if (f < 0) return -1;
    return 1;
}

static float float_abs(float f)
{
    if (f < 0)
        return f * -1;
    else
        return f;
}

static uint8_t u8_max(uint8_t a, uint8_t b)
{
    if (a > b)
        return a;
    else
        return b;
}

void control_clear_result(struct p_control_result* result)
{
    int i;

    result->result_speed = 0;
    result->end_condition_count = 0;
    result->echo_datas_index = 0;
    result->echo_avg = 0;

    for (i = 0; i < ECHO_DATAS_MAX_BUF; i++) result->echo_datas[i] = 0;
}

static float echo_read_buffered(struct p_control_result* result,
                         struct p_control_args* args)
{
    float sum;
    float temp;
    uint8_t count;
    uint8_t i;

    temp = echo_test_mm(args->pin_ultrasonic);
    result->echo_datas[result->echo_datas_index++] = temp;
    result->echo_datas_index %= args->echo_data_buf_count;

    sum = 0;
    count = 0;
    for (i = 0; i < args->echo_data_buf_count; i++)
    {
        temp = result->echo_datas[i];
        sum += temp;
        if (temp > args->mm_filter) count++;
    }

    sum /= (float)(u8_max(count, 1));
    result->echo_avg = sum;

    return sum;
}

float control_treat_speed(float speed,
                          float max_speed,
                          float dead_zone,
                          float boost_zone)
{
    if (float_abs(speed) < float_abs(dead_zone))
        speed = 0;
    else if (float_abs(speed) < float_abs(boost_zone))
        speed = float_abs(boost_zone) * signum(speed);
    if (float_abs(speed) > float_abs(max_speed))
        speed = float_abs(max_speed) * signum(speed);

    return speed;
}

void p_control_non_block(struct p_control_result* result,
                         struct p_control_args* args)
{
    float cm;
    float val;

    cm = echo_read_buffered(result, args);
    val = cm;
    val -= args->mm_target;
    val *= args->pk;

    val = control_treat_speed(val, (float)args->max_speed,
                              (float)args->abs_speed_dead_zone,
                              (float)args->abs_speed_boost_zone);

    result->result_speed = (int16_t)val;

    if (float_abs(cm - args->mm_target) < float_abs(args->mm_accuracy))
        result->end_condition_count++;
    else
    {
        if (result->end_condition_count < 1)
            result->end_condition_count = 0;
        else
            result->end_condition_count--;
    }
}

