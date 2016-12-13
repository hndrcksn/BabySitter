#include <stdlib.h>
#include <check.h>
#include "../lib/BabySitterCalc.h"

// Tests for conversions between strings and time values
START_TEST (testStringAndTimeConversions)
{
    // Lower bounds time_t tm = 61200 secs = 01/01/1970 5:00pm
    // Upper bounds time_t tm = 100800 secs = 02/01/1970 4:00am
    ck_assert_int_eq(strToTime("4:00PM"), 57600);
    ck_assert_int_eq(strToTime("5:00PM"), 61200);
    ck_assert_int_eq(strToTime("6:00PM"), 64800);
    ck_assert_int_eq(strToTime("11:00PM"), 82800);
    ck_assert_int_eq(strToTime("11:59PM"), 86340);
    ck_assert_int_eq(strToTime("12:00AM"), 86400);
    ck_assert_int_eq(strToTime("12:01AM"), 86460);
    ck_assert_int_eq(strToTime("1:00AM"), 90000);
    ck_assert_int_eq(strToTime("2:00AM"), 93600);
    ck_assert_int_eq(strToTime("3:00AM"), 97200);
    ck_assert_int_eq(strToTime("4:00AM"), 100800);
    ck_assert_int_eq(strToTime("5:00AM"), 104400);

    char buffer[32];
    ck_assert_str_eq(timeToStr(57600, buffer, 32), "4:00PM");
    ck_assert_str_eq(timeToStr(61200, buffer, 32), "5:00PM");
    ck_assert_str_eq(timeToStr(64800, buffer, 32), "6:00PM");
    ck_assert_str_eq(timeToStr(82800, buffer, 32), "11:00PM");
    ck_assert_str_eq(timeToStr(86340, buffer, 32), "11:59PM");
    ck_assert_str_eq(timeToStr(86400, buffer, 32), "12:00AM");
    ck_assert_str_eq(timeToStr(86460, buffer, 32), "12:01AM");
    ck_assert_str_eq(timeToStr(90000, buffer, 32), "1:00AM");
    ck_assert_str_eq(timeToStr(93600, buffer, 32), "2:00AM");
    ck_assert_str_eq(timeToStr(97200, buffer, 32), "3:00AM");
    ck_assert_str_eq(timeToStr(100800, buffer, 32), "4:00AM");
    ck_assert_str_eq(timeToStr(104400, buffer, 32), "5:00AM");
}
END_TEST

START_TEST (testValidTimeStringValue)
{
    ck_assert(isValidTimeString("5:00PM"));
    ck_assert(isValidTimeString("6:00PM"));
    ck_assert(isValidTimeString("07:00PM"));
}
END_TEST

START_TEST (testBabySittingTimes)
{
    ck_assert(isEarliestStartTime("5:00PM"));
    ck_assert(!isEarliestStartTime("5:01AM"));
    ck_assert(isLatestEndTime("4:00AM"));
    ck_assert(!isLatestEndTime("3:59AM"));
    ck_assert(!isLatestEndTime("4:01AM"));
}
END_TEST

Suite *babySitterTestSuite (void)
{
    Suite *s = suite_create ("BabySitter");

    /* Time string validation */
    TCase *tc_valid_time_string = tcase_create ("ValidTimeString");
    tcase_add_test (tc_valid_time_string, testValidTimeStringValue);
    suite_add_tcase (s, tc_valid_time_string);

    /* Boundary test case */
    TCase *tc_boundary = tcase_create ("Boundary");
    tcase_add_test (tc_boundary, testBabySittingTimes);
    suite_add_tcase (s, tc_boundary);

    /* String and time conversion case */
    TCase *tc_string_time_conv = tcase_create("StringTimeConversion");
    tcase_add_test (tc_string_time_conv, testStringAndTimeConversions);
    suite_add_tcase (s, tc_string_time_conv);

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

