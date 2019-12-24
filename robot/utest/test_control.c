#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "cmocka.h"

#define UNUSED(arg) ((void)arg)

#include "robot/logic/control.c"

float echo_test_mm(uint8_t pin) {return 0;}

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


int main(void)
{
    const struct CMUnitTest clear[] = {
        cmocka_unit_test(test_clear_result),
    };


    int success = 0;
    success |= cmocka_run_group_tests(clear, NULL, NULL);
    return success;
}
