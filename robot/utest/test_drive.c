#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "cmocka.h"

#define UNUSED(arg) ((void)arg)

#include "robot/logic/drive.h"

void wheel_init(void) {}

void set_speed(uint8_t wheel, int16_t speed, int time)
{
    check_expected(wheel);
    check_expected(speed);
    check_expected(time);
}

#include "robot/logic/drive.c"

static void test_combine_easy(void** state)
{
    UNUSED(state);

    drive_vector_t a;
    drive_vector_t b;
    drive_vector_t result;

    a.degrees = 0;
    a.speed = 255;
    b.degrees = 0;
    b.speed = 255;

    result = drive_combine_vecs(a, b, 255);

    assert_int_equal(0, result.degrees);
    assert_int_equal(255, result.speed);
}

static void test_combine_opposites(void** state)
{
    UNUSED(state);

    drive_vector_t a;
    drive_vector_t b;
    drive_vector_t result;

    a.degrees = 0;
    a.speed = 255;
    b.degrees = 180;
    b.speed = 255;

    result = drive_combine_vecs(a, b, 255);

    assert_int_equal(0, result.speed);
}

static void test_combine_diagonal(void** state)
{
    UNUSED(state);

    drive_vector_t a;
    drive_vector_t b;
    drive_vector_t result;

    a.degrees = 0;
    a.speed = 255;
    b.degrees = 90;
    b.speed = 255;

    result = drive_combine_vecs(a, b, 255);

    assert_int_equal(45, result.degrees);
    assert_int_equal(255, result.speed);
}

static void test_combine_complicated(void** state)
{
    UNUSED(state);

    drive_vector_t a;
    drive_vector_t b;
    drive_vector_t result;

    a.degrees = 360;
    a.speed = 100;
    b.degrees = 270;
    b.speed = 100;

    result = drive_combine_vecs(a, b, 255);

    assert_int_equal(141, result.speed);
    assert_int_equal(315, result.degrees);
}

static void test_combine_complicated_with_max(void** state)
{
    UNUSED(state);

    drive_vector_t a;
    drive_vector_t b;
    drive_vector_t result;

    a.degrees = 360;
    a.speed = 100;
    b.degrees = 270;
    b.speed = 100;

    result = drive_combine_vecs(a, b, 100);

    assert_int_equal(100, result.speed);
    assert_int_equal(315, result.degrees);
}

static void test_go_stop(void** state)
{
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
        cmocka_unit_test(test_combine_opposites),
        cmocka_unit_test(test_combine_diagonal),
        cmocka_unit_test(test_combine_complicated),
        cmocka_unit_test(test_combine_complicated_with_max),
    };

    const struct CMUnitTest go[] = {
        cmocka_unit_test(test_go_stop),
    };

    int success = 0;
    success |= cmocka_run_group_tests(combine, NULL, NULL);
    success |= cmocka_run_group_tests(go, NULL, NULL);
    return success;
}
