#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "cmocka.h"

#define UNUSED(arg) ((void)arg)

#include "robot/logic/control.c"

static void test_combine_easy(void** state)
{
    UNUSED(state);
}

static void test_go_stop(void** state)
{
  UNUSED(state);

    expect_value(set_speed, wheel, WHEEL_FL);
    expect_value(set_speed, speed, 0);
    expect_value(set_speed, time, 0);

    expect_value(set_speed, wheel, WHEEL_FR);
    expect_value(set_speed, speed, 0);
    expect_value(set_speed, time, 0);

    expect_value(set_speed, wheel, WHEEL_BL);
    expect_value(set_speed, speed, 0);
    expect_value(set_speed, time, 0);

    expect_value(set_speed, wheel, WHEEL_BR);
    expect_value(set_speed, speed, 0);
    expect_value(set_speed, time, 0);

    go_stop();
}

int main(void)
{
    const struct CMUnitTest combine[] = {
        cmocka_unit_test(test_combine_easy),
    };

    const struct CMUnitTest go[] = {
        cmocka_unit_test(test_go_stop),
    };

    int success = 0;
    success |= cmocka_run_group_tests(combine, NULL, NULL);
    success |= cmocka_run_group_tests(go, NULL, NULL);
    return success;
}
