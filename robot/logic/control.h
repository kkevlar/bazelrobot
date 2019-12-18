#ifndef CONTROL_H
#define CONTROL_H

#include "echo.h"
#include "testoptions.h"
#include "wiring.h"

#define ECHO_DATAS_MAX_BUF 10

struct p_control_result
{
    int16_t result_speed;
    uint16_t end_condition_count;
    uint8_t echo_datas_index;
    float echo_datas[ECHO_DATAS_MAX_BUF];
    float echo_avg;
};

struct p_control_args
{
    uint8_t pin_ultrasonic;
    float mm_target;
    float mm_accuracy;
    float pk;
    int16_t max_speed;
    uint8_t abs_speed_dead_zone;
    uint8_t abs_speed_boost_zone;
    uint8_t echo_data_buf_count;
};

void control_clear_result(struct p_control_result* result);
float control_treat_speed(float speed,
                          float max_speed,
                          float dead_zone,
                          float boost_zone);
void p_control_non_block(struct p_control_result* result,
                         struct p_control_args* args);

#endif
