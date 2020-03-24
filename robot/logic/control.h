#ifndef CONTROL_H
#define CONTROL_H

#include <stdint.h>

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
    uint8_t pin_ultrasonic; /* Pin number of ultrasonic */
    float mm_target; /* Target distance in ultrasonic's direction */
    float mm_accuracy; /* Range of error around the target distance */
    float mm_filter; /* All measurements less than the filter are ignored */ 
    float pk; /* P control contstant */
    int16_t max_speed; /* Max output speed of the pcontrol block */
    uint8_t abs_speed_dead_zone; /* Dead zone- all outputs within +/- deadzone will instead output zero */
    uint8_t abs_speed_boost_zone; /* Boost zone- all outputs within +/- boostzone but not in dead zone will be boosted up to boostzone * signum(initial) */
    uint8_t echo_data_buf_count; /* Rolling average of measurements- how many to use? */
};

void control_clear_result(struct p_control_result* result);
float control_treat_speed(float speed,
                          float max_speed,
                          float dead_zone,
                          float boost_zone);
void p_control_non_block(struct p_control_result* result,
                         struct p_control_args* args);

#endif
