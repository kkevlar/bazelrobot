#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "cmocka.h"

#define UNUSED(arg) ((void)arg)

#include "robot/logic/control.c"

float echo_test_mm(uint8_t pin) {
 check_expected(pin); 
  return (float) mock();
}

static void test_clear_result(void** state)
{
    UNUSED(state);

    struct p_control_result result;

    result.result_speed = 66;
    result.end_condition_count = 66;
    result.echo_datas_index = 66;
    result.echo_datas[5] = 66;
    result.echo_avg = 66;

    control_clear_result(&result);

    assert_int_equal(result.result_speed, 0);
    assert_int_equal(result.end_condition_count, 0);
    assert_int_equal(result.echo_datas_index, 0);
    assert_int_equal(result.echo_datas[5], 0);
    assert_int_equal(result.echo_avg, 0);
}

#define assert_float_similar(a,b) assert_true(float_abs(a-b) < 0.0001) 

static void test_treat_noaction(void** state)
{
  UNUSED(state);

  float speed = 255;
  float max_speed = 255;
  float dead_zone = 255;
  float boost_zone = 255;

  float result = control_treat_speed(speed, max_speed, dead_zone, boost_zone);
  float expect = 255;

assert_float_similar(expect, result);
}

static void test_treat_cap_speed(void** state)
{
  UNUSED(state);

  float speed = 255;
  float max_speed = 155;
  float dead_zone = 255;
  float boost_zone = 255;

  float result = control_treat_speed(speed, max_speed, dead_zone, boost_zone);
  float expect = 155;

assert_float_similar(expect, result);
}

static void test_treat_deadify(void** state)
{
  UNUSED(state);

  float speed = 200;
  float max_speed = 255;
  float dead_zone = 201;
  float boost_zone = 255;

  float result = control_treat_speed(speed, max_speed, dead_zone, boost_zone);
  float expect = 0;

assert_float_similar(expect, result);
}

static void test_treat_boost(void** state)
{
    UNUSED(state);

      float speed = 150;
        float max_speed = 255;
          float dead_zone = 100;
            float boost_zone = 200;

              float result = control_treat_speed(speed, max_speed, dead_zone, boost_zone);
                float expect = 200;

                assert_float_similar(expect, result);
}

static void test_read_buffered_two(void** state) 
{

  UNUSED(state);

struct p_control_result result;
struct p_control_args args;

args.echo_data_buf_count = 2;
args.pin_ultrasonic = 221;
args.mm_filter = -1;

control_clear_result(&result);

    float actual;
    float expected;

expect_value(echo_test_mm, pin, 221);
will_return(echo_test_mm, 200);
actual  = echo_read_buffered(&result, &args);
expected = 100;
  assert_float_similar(expected,actual);

expect_value(echo_test_mm, pin, 221);
will_return(echo_test_mm, 200);
actual  = echo_read_buffered(&result, &args);
expected = 200;
  assert_float_similar(expected,actual);
}

static void test_read_buffered_one(void** state) 
{

  UNUSED(state);

struct p_control_result result;
struct p_control_args args;

args.echo_data_buf_count = 1;
args.pin_ultrasonic = 221;
args.mm_filter = 1;

control_clear_result(&result);

    float actual;
    float expected;

expect_value(echo_test_mm, pin, 221);
will_return(echo_test_mm, 0);
actual  = echo_read_buffered(&result, &args);
expected = 0;
  assert_float_similar(expected,actual);

expect_value(echo_test_mm, pin, 221);
will_return(echo_test_mm, 100);
actual  = echo_read_buffered(&result, &args);
expected = 100;
  assert_float_similar(expected,actual);

expect_value(echo_test_mm, pin, 221);
will_return(echo_test_mm, 0);
actual  = echo_read_buffered(&result, &args);
expected = 0;
  assert_float_similar(expected,actual);

expect_value(echo_test_mm, pin, 221);
will_return(echo_test_mm, 10);
actual  = echo_read_buffered(&result, &args);
expected = 10;
  assert_float_similar(expected,actual);
}

static void test_speed_pcontrol_towards(void** state) 
{
  UNUSED(state);

struct p_control_result result;
struct p_control_args args;

args.echo_data_buf_count = 1;
args.pin_ultrasonic = 221;
args.mm_target = 50;
args.mm_accuracy = 10;
args.mm_filter = 1;
args.pk = 1000.0f;
args.max_speed = 255;
args.abs_speed_dead_zone = 20;
args.abs_speed_boost_zone = 30;

control_clear_result(&result);

expect_value(echo_test_mm, pin, 221);
will_return(echo_test_mm, 200);
p_control_non_block(&result, &args);

assert_int_equal(255, result.result_speed);
}

static void test_speed_pcontrol_away(void** state) 
{

  UNUSED(state);

struct p_control_result result;
struct p_control_args args;

args.echo_data_buf_count = 1;
args.pin_ultrasonic = 221;
args.mm_target = 500;
args.mm_accuracy = 10;
args.mm_filter = 1;
args.pk = 1000.0f;
args.max_speed = 255;
args.abs_speed_dead_zone = 20;
args.abs_speed_boost_zone = 30;

control_clear_result(&result);

expect_value(echo_test_mm, pin, 221);
will_return(echo_test_mm, 200);
p_control_non_block(&result, &args);

assert_int_equal(-255, result.result_speed);
}

static void test_speed_pcontrol_stop(void** state) 
{

  UNUSED(state);

struct p_control_result result;
struct p_control_args args;

args.echo_data_buf_count = 1;
args.pin_ultrasonic = 221;
args.mm_target = 500;
args.mm_accuracy = 10;
args.mm_filter = 1;
args.pk = 1000.0f;
args.max_speed = 255;
args.abs_speed_dead_zone = 2;
args.abs_speed_boost_zone = 100;

control_clear_result(&result);

expect_value(echo_test_mm, pin, 221);
will_return(echo_test_mm, 500);
p_control_non_block(&result, &args);

assert_int_equal(0, result.result_speed);
}

static void test_cond_pcontrol_away(void** state) 
{

  UNUSED(state);

struct p_control_result result;
struct p_control_args args;

args.echo_data_buf_count = 1;
args.pin_ultrasonic = 221;
args.mm_target = 500;
args.mm_accuracy = 10;
args.mm_filter = 1;
args.pk = 1000.0f;
args.max_speed = 255;
args.abs_speed_dead_zone = 20;
args.abs_speed_boost_zone = 30;

control_clear_result(&result);

result.end_condition_count = 1;

expect_value(echo_test_mm, pin, 221);
will_return(echo_test_mm, 200);
p_control_non_block(&result, &args);

assert_int_equal(0, result.end_condition_count);
}

static void test_cond_pcontrol_stop(void** state) 
{

  UNUSED(state);

struct p_control_result result;
struct p_control_args args;

args.echo_data_buf_count = 1;
args.pin_ultrasonic = 221;
args.mm_target = 500;
args.mm_accuracy = 10;
args.mm_filter = 1;
args.pk = 1000.0f;
args.max_speed = 255;
args.abs_speed_dead_zone = 2;
args.abs_speed_boost_zone = 100;

control_clear_result(&result);

result.end_condition_count = 2;

expect_value(echo_test_mm, pin, 221);
will_return(echo_test_mm, 500);
p_control_non_block(&result, &args);

assert_int_equal(3, result.end_condition_count);
}
int main(void)
{
    const struct CMUnitTest clear[] = {
        cmocka_unit_test(test_clear_result),
    };

    const struct CMUnitTest treat[] = {
        cmocka_unit_test(test_treat_noaction),
        cmocka_unit_test(test_treat_cap_speed),
        cmocka_unit_test(test_treat_deadify),
        cmocka_unit_test(test_treat_boost),
    };

    const struct CMUnitTest read_buffered[] = {
        cmocka_unit_test(test_read_buffered_two),
          cmocka_unit_test(test_read_buffered_one),
    };

    const struct CMUnitTest pcontrol_speed[] = {
        cmocka_unit_test(test_speed_pcontrol_away),
        cmocka_unit_test(test_speed_pcontrol_towards),
        cmocka_unit_test(test_speed_pcontrol_stop),
    };

    const struct CMUnitTest pcontrol_endcond[] = {
        cmocka_unit_test(test_cond_pcontrol_stop),
        cmocka_unit_test(test_cond_pcontrol_away),
    };

    int success = 0;
    success |= cmocka_run_group_tests(clear, NULL, NULL);
    success |= cmocka_run_group_tests(treat, NULL, NULL);
    success |= cmocka_run_group_tests(read_buffered, NULL, NULL);
    success |= cmocka_run_group_tests(pcontrol_speed, NULL, NULL);
    success |= cmocka_run_group_tests(pcontrol_endcond , NULL, NULL);
    return success;
}
