#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "cmocka.h"

#define UNUSED(arg) ((void)arg)

#include "robot/logic/control.c"

float echo_test_mm(uint8_t pin) {
 UNUSED(pin); 
  return 0;
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

    int success = 0;
    success |= cmocka_run_group_tests(clear, NULL, NULL);
    success |= cmocka_run_group_tests(treat, NULL, NULL);
    return success;
}
