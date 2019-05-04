#include <gtest/gtest.h>
#include <smalltime/smalltime.h>


// ==================================================================
// Helpers
// ==================================================================

static void test_encode_decode(int year, int month, int day, int hour, int minute, int second, int microsecond)
{
    smalltime encoded = smalltime_new(year, month, day, hour, minute, second, microsecond);
    int actual_year = smalltime_get_year(encoded);
    int actual_month = smalltime_get_month(encoded);
    int actual_day = smalltime_get_day(encoded);
    int actual_hour = smalltime_get_hour(encoded);
    int actual_minute = smalltime_get_minute(encoded);
    int actual_second = smalltime_get_second(encoded);
    int actual_microsecond = smalltime_get_microsecond(encoded);

    EXPECT_EQ(year, actual_year);
    EXPECT_EQ(month, actual_month);
    EXPECT_EQ(day, actual_day);
    EXPECT_EQ(hour, actual_hour);
    EXPECT_EQ(minute, actual_minute);
    EXPECT_EQ(second, actual_second);
    EXPECT_EQ(microsecond, actual_microsecond);

    smalltime piecemeal_encoded = 0;
    piecemeal_encoded = smalltime_with_year(encoded, year);
    piecemeal_encoded = smalltime_with_month(encoded, month);
    piecemeal_encoded = smalltime_with_day(encoded, day);
    piecemeal_encoded = smalltime_with_hour(encoded, hour);
    piecemeal_encoded = smalltime_with_minute(encoded, minute);
    piecemeal_encoded = smalltime_with_second(encoded, second);
    piecemeal_encoded = smalltime_with_microsecond(encoded, microsecond);

    EXPECT_EQ(encoded, piecemeal_encoded);
}

static void test_single_date(
    smalltime expected_encoded,
    int expected_year,
    int expected_month,
    int expected_day,
    int expected_hour,
    int expected_minute,
    int expected_second,
    int expected_microsecond)
{
    int actual_year = smalltime_get_year(expected_encoded);
    int actual_month = smalltime_get_month(expected_encoded);
    int actual_day = smalltime_get_day(expected_encoded);
    int actual_hour = smalltime_get_hour(expected_encoded);
    int actual_minute = smalltime_get_minute(expected_encoded);
    int actual_second = smalltime_get_second(expected_encoded);
    int actual_microsecond = smalltime_get_microsecond(expected_encoded);

    EXPECT_EQ(expected_year, actual_year);
    EXPECT_EQ(expected_month, actual_month);
    EXPECT_EQ(expected_day, actual_day);
    EXPECT_EQ(expected_hour, actual_hour);
    EXPECT_EQ(expected_minute, actual_minute);
    EXPECT_EQ(expected_second, actual_second);
    EXPECT_EQ(expected_microsecond, actual_microsecond);

    smalltime actual_encoded = smalltime_new(expected_year, expected_month, expected_day, expected_hour, expected_minute, expected_second, expected_microsecond);

    EXPECT_EQ(expected_encoded, actual_encoded);
}


// ==================================================================
// Tests
// ==================================================================

TEST(Smalltime, spec_examples)
{
    test_single_date(0x1f06b48590dbc2eLL, 1985, 10, 26, 8, 22, 16, 900142);
    test_single_date(0x1f06b68590dbc2eLL, 1985, 10, 27, 8, 22, 16, 900142);
    test_single_date(0x1f06b48550dbc2eLL, 1985, 10, 26, 8, 21, 16, 900142);
}

TEST(Smalltime, comparisons)
{
    EXPECT_GT(smalltime_new(2000, 1, 1, 0, 0, 0, 1), smalltime_new(2000, 1, 1, 0, 0, 0, 0));
    EXPECT_GT(smalltime_new(2000, 1, 1, 0, 0, 1, 0), smalltime_new(2000, 1, 1, 0, 0, 0, 999999));
    EXPECT_GT(smalltime_new(2000, 1, 1, 0, 0, 2, 0), smalltime_new(2000, 1, 1, 0, 0, 1, 0));
    EXPECT_GT(smalltime_new(2000, 1, 1, 0, 1, 0, 0), smalltime_new(2000, 1, 1, 0, 0, 60, 0));
    EXPECT_GT(smalltime_new(2000, 1, 1, 0, 2, 0, 0), smalltime_new(2000, 1, 1, 0, 1, 0, 0));
    EXPECT_GT(smalltime_new(2000, 1, 1, 1, 0, 0, 0), smalltime_new(2000, 1, 1, 0, 59, 0, 0));
    EXPECT_GT(smalltime_new(2000, 1, 1, 2, 0, 0, 0), smalltime_new(2000, 1, 1, 1, 0, 0, 0));
    EXPECT_GT(smalltime_new(2000, 1, 2, 0, 0, 0, 0), smalltime_new(2000, 1, 1, 23, 0, 0, 0));
    EXPECT_GT(smalltime_new(2000, 1, 2, 0, 0, 0, 0), smalltime_new(2000, 1, 1, 0, 0, 0, 0));
    EXPECT_GT(smalltime_new(2005, 1, 1, 0, 0, 0, 0), smalltime_new(2004, 12, 31, 0, 0, 0, 0));
    EXPECT_GT(smalltime_new(1, 1, 1, 0, 0, 0, 0), smalltime_new(0, 1, 1, 0, 0, 0, 0));
    EXPECT_GT(smalltime_new(0, 1, 1, 0, 0, 0, 0), smalltime_new(-1, 1, 1, 0, 0, 0, 0));
    EXPECT_GT(smalltime_new(1, 1, 1, 0, 0, 0, 0), smalltime_new(-1, 1, 1, 0, 0, 0, 0));
}

TEST(Smalltime, year)
{
    int month = 1;
    int day = 11;
    int hour = 11;
    int minute = 11;
    int second = 11;
    int microsecond = 111111;
    for(int year = -131072; year < 131071; year++)
    {
        test_encode_decode(year, month, day, hour, minute, second, microsecond);
    }
}

TEST(Smalltime, day)
{
    int year = 2000;
    int month = 1;
    int hour = 11;
    int minute = 11;
    int second = 11;
    int microsecond = 111111;
    for(int day = 1; day < 28; day++)
    {
        test_encode_decode(year, month, day, hour, minute, second, microsecond);
    }
}

TEST(Smalltime, hour)
{
    int year = 2000;
    int month = 1;
    int day = 11;
    int minute = 11;
    int second = 11;
    int microsecond = 111111;
    for(int hour = 0; hour < 24; hour++)
    {
        test_encode_decode(year, month, day, hour, minute, second, microsecond);
    }
}

TEST(Smalltime, minute)
{
    int year = 2000;
    int month = 1;
    int day = 11;
    int hour = 11;
    int second = 11;
    int microsecond = 111111;
    for(int minute = 0; minute < 60; minute++)
    {
        test_encode_decode(year, month, day, hour, minute, second, microsecond);
    }
}

TEST(Smalltime, second)
{
    int year = 2000;
    int month = 1;
    int day = 11;
    int hour = 11;
    int minute = 11;
    int microsecond = 111111;
    for(int second = 0; second < 61; second++)
    {
        test_encode_decode(year, month, day, hour, minute, second, microsecond);
    }
}

TEST(Smalltime, microsecond)
{
    int year = 2000;
    int month = 1;
    int day = 11;
    int hour = 11;
    int minute = 11;
    int second = 11;
    for(int microsecond = 0; microsecond < 1000000; microsecond++)
    {
        test_encode_decode(year, month, day, hour, minute, second, microsecond);
    }
}
