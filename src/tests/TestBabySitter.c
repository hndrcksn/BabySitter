#include <stdlib.h>
#include <check.h>
#include "../lib/BabySitterCalc.h"

START_TEST (testBabySittingTimes)
{
    ck_assert(isEarliestStartTime("5:00PM"));
}
END_TEST

Suite *babySitterTestSuite (void)
{
    Suite *s = suite_create ("BabySitter");

    /* First test case */
    TCase *tc_first = tcase_create ("First");
    tcase_add_test (tc_first, testBabySittingTimes);
    suite_add_tcase (s, tc_first);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s = babySitterTestSuite ();
    SRunner *sr = srunner_create (s);
    srunner_run_all (sr, CK_NORMAL);
    number_failed = srunner_ntests_failed (sr);
    srunner_free (sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

