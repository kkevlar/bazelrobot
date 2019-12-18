#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static void test_sanity(void** state)
{
  (void) state;
  assert_int_equal(1,1);
}


int main(void)
{
	const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_sanity),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
