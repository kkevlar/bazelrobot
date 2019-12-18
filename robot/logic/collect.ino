
#include "collect.h"

void collect_init(void)
{
	/*Nobody's Home!!*/
	return;
}

void collect_im_bored(void)
{
    /* shoot_indexer_spam(); */ 
}

void position_for_collection(direction_t dir_wall, direction_t dir_target, float mm_target)
{
    struct p_control_result result_wall;
    struct p_control_result result_target;

    struct p_control_args args_wall;
    struct p_control_args args_target;

    drive_vector_t vec_wall;
    drive_vector_t vec_target;
    drive_vector_t vec_result;

    vec_wall.degrees = direction_to_degrees(dir_wall);
    vec_target.degrees = direction_to_degrees(dir_target);

    control_clear_result(&result_wall);
    control_clear_result(&result_target);

    args_wall.pin_ultrasonic = direction_to_echo_pin(dir_wall);
    args_wall.pk = COLLECT_PRE_WALL_P_CONSTANT;
    args_wall.max_speed = 255;
    args_wall.abs_speed_dead_zone = 0;
    args_wall.abs_speed_boost_zone = 0;
    args_wall.echo_data_buf_count = 2;

    args_target.pin_ultrasonic = direction_to_echo_pin(dir_target);
    args_target.pk = COLLECT_PRE_TARGET_P_CONSTANT;
    args_target.max_speed = 255;
    args_target.abs_speed_dead_zone = 0;
    args_target.abs_speed_boost_zone = 0;
    args_target.echo_data_buf_count = 2;

    while(1)
    {
        args_wall.mm_target = COLLECT_PRE_DESIRED_WALL_DIST_MM;
        args_wall.mm_accuracy = COLLECT_PRE_MM_ACCURACY;
        args_target.mm_target = mm_target;
        args_target.mm_accuracy = COLLECT_PRE_MM_ACCURACY;

        p_control_non_block(&result_wall,&args_wall);
        vec_wall.speed = (result_wall.result_speed);
        delay(COLLECT_PRE_IN_BETWEEN_ECHO_TESTS_DELAY_MS);
        p_control_non_block(&result_target,&args_target);
        vec_target.speed = (result_target.result_speed);
        vec_wall.speed = (result_wall.result_speed);
        vec_result = drive_combine_vecs(vec_wall, vec_target, 255);

        vec_result.speed = (int16_t) (control_treat_speed(
            (float) vec_result.speed,
            255.0f,
            20.0f,
            COLLECT_GENERAL_BOOST_ZONE
            ));

        go(vec_result);

        if(result_target.end_condition_count > 2 && 
            (result_wall.end_condition_count > 2 || result_wall.echo_avg < COLLECT_PRE_EARLY_BREAK_WALL_DIST))
            break;

        collect_im_bored();
        delay(COLLECT_PRE_IN_BETWEEN_ECHO_TESTS_DELAY_MS);
    }
}

void roomba(direction_t dir_wall)
{
    drive_vector_t vec_wall;

    vec_wall.degrees = direction_to_degrees(dir_wall);
    vec_wall.speed = COLLECT_ROOMBA_SPEED;

    go(vec_wall);

    while(switch_test_up(dir_wall))
    {
        collect_im_bored();
        delay(20);
    }

    delay(COLLECT_ROOMBA_PERSIST_MS);
}


void backglide()
{
    drive_vector_t vec;
    vec.speed = 255;
    vec.degrees = 190;
    while(echo_test_mm(direction_to_echo_pin(DIRECTION_ID_LEFT)) > 550)
    {
        delay(5);
        go(vec);
    }
    while(echo_test_mm(direction_to_echo_pin(DIRECTION_ID_LEFT)) > 550)
    {
        delay(5);

        go(vec);
    }
    while(echo_test_mm(direction_to_echo_pin(DIRECTION_ID_LEFT)) > 550)
    {
        delay(5);

        go(vec);
    }
    while(echo_test_mm(direction_to_echo_pin(DIRECTION_ID_LEFT)) > 550)
    {
        delay(5);

        go(vec);
    }
    while(echo_test_mm(direction_to_echo_pin(DIRECTION_ID_LEFT)) > 550)
    {
        delay(5);

        go(vec);
    }
}

void do_collection(direction_t dir_wall, direction_t dir_target, float mm_target)
{
    struct p_control_result result_target;
    struct p_control_args args_target;

    drive_vector_t vec_wall;
    drive_vector_t vec_target;
    drive_vector_t vec_result;

    vec_wall.degrees = direction_to_degrees(dir_wall);
    vec_target.degrees = direction_to_degrees(dir_target);

    control_clear_result(&result_target);

    vec_wall.speed = COLLECT_DO_INTO_WALL_SPEED_FOR_HUG;

    args_target.pin_ultrasonic = direction_to_echo_pin(dir_target);
    args_target.pk = COLLECT_DO_P_CONSTANT;
    args_target.max_speed = COLLECT_DO_MAX_TARGET_SPEED;
    args_target.abs_speed_dead_zone = 0;
    args_target.abs_speed_boost_zone = 0;
    args_target.echo_data_buf_count = 1;
    args_target.mm_accuracy = COLLECT_DO_MM_ACCURACY;
    args_target.mm_target = mm_target;

    while(1)
    {
        p_control_non_block(&result_target,&args_target);

        vec_target.speed = result_target.result_speed;

        vec_result = drive_combine_vecs(vec_target, vec_wall, 255);

        vec_result.speed = (int16_t) (control_treat_speed(
            (float) vec_result.speed,
            COLLECT_DO_MAX_NET_SPEED,
            20.0f,
            230
            ));

        go(vec_result);

        if(result_target.end_condition_count > 2)
            break;

        collect_im_bored();
        delay(COLLECT_DO_IN_BETWEEN_ECHO_TESTS_DELAY_MS);
    }
}

void position_after_yeet(direction_t dir_wall, direction_t dir_target, float mm_wall, float mm_target)
{
    struct p_control_result result_wall;
    struct p_control_result result_target;

    struct p_control_args args_wall;
    struct p_control_args args_target;

    drive_vector_t vec_wall;
    drive_vector_t vec_target;
    drive_vector_t vec_result;

    vec_wall.degrees = direction_to_degrees(dir_wall);
    vec_target.degrees = direction_to_degrees(dir_target);

    control_clear_result(&result_wall);
    control_clear_result(&result_target);

    args_wall.pin_ultrasonic = direction_to_echo_pin(dir_wall);
    args_wall.pk = COLLECT_PRE_WALL_P_CONSTANT;
    args_wall.max_speed = 255;
    args_wall.abs_speed_dead_zone = 0;
    args_wall.abs_speed_boost_zone = 0;
    args_wall.echo_data_buf_count = 4;

    args_target.pin_ultrasonic = direction_to_echo_pin(dir_target);
    args_target.pk = COLLECT_PRE_TARGET_P_CONSTANT;
    args_target.max_speed = 255;
    args_target.abs_speed_dead_zone = 0;
    args_target.abs_speed_boost_zone = 0;
    args_target.echo_data_buf_count = 4;

    while(1)
    {
        args_wall.mm_target = mm_wall;
        args_wall.mm_accuracy = 150;
        args_target.mm_target = mm_target;
        args_target.mm_accuracy = 150;

        p_control_non_block(&result_wall,&args_wall);
        vec_wall.speed = (result_wall.result_speed);
        delay(COLLECT_PRE_IN_BETWEEN_ECHO_TESTS_DELAY_MS);
        p_control_non_block(&result_target,&args_target);
        vec_target.speed = (result_target.result_speed);
        vec_wall.speed = (result_wall.result_speed);
        vec_result = drive_combine_vecs(vec_wall, vec_target, 255);

        vec_result.speed = (int16_t) (control_treat_speed(
            (float) vec_result.speed,
            255.0f,
            20.0f,
            COLLECT_GENERAL_BOOST_ZONE
            ));

        go(vec_result);

        if(result_target.end_condition_count > 1 && 
            (result_wall.end_condition_count > 1))
            break;

        collect_im_bored();
        delay(COLLECT_PRE_IN_BETWEEN_ECHO_TESTS_DELAY_MS);
    }
}



void yeet_away_from_wall(direction_t dir_wall, float mm_target)
{
    struct p_control_result result_wall;
    struct p_control_args args_wall;

    drive_vector_t vec_wall;

    vec_wall.degrees = direction_to_degrees(dir_wall);

    control_clear_result(&result_wall);

    args_wall.pin_ultrasonic = direction_to_echo_pin(dir_wall);
    args_wall.pk = COLLECT_YEET_AWAY_P_CONSTANT;
    args_wall.max_speed = COLLECT_YEET_AWAY_MAX_SPEED;
    args_wall.abs_speed_dead_zone = COLLECT_YEET_AWAY_DEAD_ZONE;
    args_wall.abs_speed_boost_zone = COLLECT_GENERAL_BOOST_ZONE;
    args_wall.echo_data_buf_count = 1;
    args_wall.mm_accuracy = COLLECT_YEET_AWAY_ACCURACY;
    args_wall.mm_target = mm_target;

    while(1)
    {
        p_control_non_block(&result_wall,&args_wall);

        vec_wall.speed = result_wall.result_speed;

        go(vec_wall);

        if(result_wall.end_condition_count > 2)
            break;

        collect_im_bored();
        delay(COLLECT_YEET_AWAY_DELAY_MS);
    }
}

void collect_right()
{
    position_for_collection(
        DIRECTION_ID_RIGHT,
        DIRECTION_ID_BACK,
        FIELD_COLLECT_RIGHT_PRE_TARGET_FROM_BACK);
    roomba(DIRECTION_ID_RIGHT);
    do_collection(
        DIRECTION_ID_RIGHT,
        DIRECTION_ID_BACK,
        FIELD_COLLECT_RIGHT_POST_TARGET_FROM_BACK);
}

void collect_back()
{
    // position_for_collection(
    //     DIRECTION_ID_BACK,
    //     DIRECTION_ID_RIGHT,
    //     FIELD_COLLECT_BACK_PRE_TARGET_FROM_RIGHT);
    // roomba(DIRECTION_ID_BACK);
    backglide();
    do_collection(
        DIRECTION_ID_BACK,
        DIRECTION_ID_LEFT,
        FIELD_COLLECT_BACK_POST_TARGET_FROM_LEFT);
}

void collect_left()
{
    position_for_collection(
        DIRECTION_ID_LEFT,
        DIRECTION_ID_BACK,
        FIELD_COLLECT_LEFT_PRE_TARGET_FROM_BACK);
    roomba(DIRECTION_ID_LEFT);
    do_collection(
        DIRECTION_ID_LEFT,
        DIRECTION_ID_BACK,
        FIELD_COLLECT_LEFT_POST_TARGET_FROM_BACK);
}

void collection_victory_lap()
{
    while(echo_test_mm(direction_to_echo_pin(DIRECTION_ID_RIGHT)) > 710)
    {
        delay(5);
        go_right();
    }
    collect_right();
    collect_back();
    yeet_away_from_wall(
        DIRECTION_ID_BACK,
        FIELD_COLLECT_YEET_ANTI_ROOMBA_WALL_BACK);
    position_after_yeet(DIRECTION_ID_LEFT,
        DIRECTION_ID_BACK,
        300, 300);
    collect_left();
}


