#ifndef CONTROL_H
#define CONTROL_H

#include "testoptions.h"
#include "echo.h"
#include "wiring.h"
#include "wheel.h"

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
void p_control_non_block(struct p_control_result* result, struct p_control_args* args);
float control_treat_speed(
    float speed,
    float max,
    float dead_zone,
    float boost_zone);

#endif
