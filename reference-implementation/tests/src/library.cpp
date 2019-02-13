#include <gtest/gtest.h>
#include <smalltime/smalltime.h>


// ==================================================================
// Helpers
// ==================================================================

static void test_encode_decode(int year, int doy, int hour, int minute, int second, int microsecond)
{
    smalltime encoded = smalltime_new(year, doy, hour, minute, second, microsecond);
    int actual_year = smalltime_get_year(encoded);
    int actual_doy = smalltime_get_day(encoded);
    int actual_hour = smalltime_get_hour(encoded);
    int actual_minute = smalltime_get_minute(encoded);
    int actual_second = smalltime_get_second(encoded);
    int actual_microsecond = smalltime_get_microsecond(encoded);

    EXPECT_EQ(year, actual_year);
    EXPECT_EQ(doy, actual_doy);
    EXPECT_EQ(hour, actual_hour);
    EXPECT_EQ(minute, actual_minute);
    EXPECT_EQ(second, actual_second);
    EXPECT_EQ(microsecond, actual_microsecond);

    smalltime piecemeal_encoded = 0;
    piecemeal_encoded = smalltime_with_year(encoded, year);
    piecemeal_encoded = smalltime_with_day(encoded, doy);
    piecemeal_encoded = smalltime_with_hour(encoded, hour);
    piecemeal_encoded = smalltime_with_minute(encoded, minute);
    piecemeal_encoded = smalltime_with_second(encoded, second);
    piecemeal_encoded = smalltime_with_microsecond(encoded, microsecond);

    EXPECT_EQ(encoded, piecemeal_encoded);
}

static void test_single_date(
    smalltime expected_encoded,
    int expected_year,
    int expected_doy,
    int expected_hour,
    int expected_minute,
    int expected_second,
    int expected_microsecond)
{
    int actual_year = smalltime_get_year(expected_encoded);
    int actual_doy = smalltime_get_day(expected_encoded);
    int actual_hour = smalltime_get_hour(expected_encoded);
    int actual_minute = smalltime_get_minute(expected_encoded);
    int actual_second = smalltime_get_second(expected_encoded);
    int actual_microsecond = smalltime_get_microsecond(expected_encoded);

    EXPECT_EQ(expected_year, actual_year);
    EXPECT_EQ(expected_doy, actual_doy);
    EXPECT_EQ(expected_hour, actual_hour);
    EXPECT_EQ(expected_minute, actual_minute);
    EXPECT_EQ(expected_second, actual_second);
    EXPECT_EQ(expected_microsecond, actual_microsecond);

    smalltime actual_encoded = smalltime_new(expected_year, expected_doy, expected_hour, expected_minute, expected_second, expected_microsecond);

    EXPECT_EQ(expected_encoded, actual_encoded);
}


// ==================================================================
// Tests
// ==================================================================

TEST(Time, readme_examples)
{
    test_single_date(0x1f06568590dbc2eLL, 1985, 299, 8, 22, 16, 900142);
    test_single_date(0x1f06588590dbc2eLL, 1985, 300, 8, 22, 16, 900142);
    test_single_date(0x1f06568550dbc2eLL, 1985, 299, 8, 21, 16, 900142);
}

TEST(Time, single)
{
    test_single_date(0x13487072091e240LL, 1234, 56, 7, 8, 9, 123456);
}

TEST(Time, comparisons)
{
    EXPECT_GT(smalltime_new(2000, 1, 0, 0, 0, 1), smalltime_new(2000, 1, 0, 0, 0, 0));
    EXPECT_GT(smalltime_new(2000, 1, 0, 0, 1, 0), smalltime_new(2000, 1, 0, 0, 0, 999999));
    EXPECT_GT(smalltime_new(2000, 1, 0, 0, 2, 0), smalltime_new(2000, 1, 0, 0, 1, 0));
    EXPECT_GT(smalltime_new(2000, 1, 0, 1, 0, 0), smalltime_new(2000, 1, 0, 0, 60, 0));
    EXPECT_GT(smalltime_new(2000, 1, 0, 2, 0, 0), smalltime_new(2000, 1, 0, 1, 0, 0));
    EXPECT_GT(smalltime_new(2000, 1, 1, 0, 0, 0), smalltime_new(2000, 1, 0, 59, 0, 0));
    EXPECT_GT(smalltime_new(2000, 1, 2, 0, 0, 0), smalltime_new(2000, 1, 1, 0, 0, 0));
    EXPECT_GT(smalltime_new(2000, 2, 0, 0, 0, 0), smalltime_new(2000, 1, 23, 0, 0, 0));
    EXPECT_GT(smalltime_new(2000, 2, 0, 0, 0, 0), smalltime_new(2000, 1, 0, 0, 0, 0));
    EXPECT_GT(smalltime_new(2005, 1, 0, 0, 0, 0), smalltime_new(2004, 366, 0, 0, 0, 0));
    EXPECT_GT(smalltime_new(1, 1, 0, 0, 0, 0), smalltime_new(0, 1, 0, 0, 0, 0));
    EXPECT_GT(smalltime_new(0, 1, 0, 0, 0, 0), smalltime_new(-1, 1, 0, 0, 0, 0));
    EXPECT_GT(smalltime_new(1, 1, 0, 0, 0, 0), smalltime_new(-1, 1, 0, 0, 0, 0));
}

TEST(Time, year)
{
    int doy = 111;
    int hour = 11;
    int minute = 11;
    int second = 11;
    int microsecond = 111111;
    for(int year = -131072; year < 131071; year++)
    {
        test_encode_decode(year, doy, hour, minute, second, microsecond);
    }
}

TEST(Time, doy)
{
    int year = 2000;
    int hour = 11;
    int minute = 11;
    int second = 11;
    int microsecond = 111111;
    for(int doy = 1; doy <= 366; doy++)
    {
        test_encode_decode(year, doy, hour, minute, second, microsecond);
    }
}

TEST(Time, hour)
{
    int year = 2000;
    int doy = 111;
    int minute = 11;
    int second = 11;
    int microsecond = 111111;
    for(int hour = 0; hour < 24; hour++)
    {
        test_encode_decode(year, doy, hour, minute, second, microsecond);
    }
}

TEST(Time, minute)
{
    int year = 2000;
    int doy = 111;
    int hour = 11;
    int second = 11;
    int microsecond = 111111;
    for(int minute = 0; minute < 60; minute++)
    {
        test_encode_decode(year, doy, hour, minute, second, microsecond);
    }
}

TEST(Time, second)
{
    int year = 2000;
    int doy = 111;
    int hour = 11;
    int minute = 11;
    int microsecond = 111111;
    for(int second = 0; second < 61; second++)
    {
        test_encode_decode(year, doy, hour, minute, second, microsecond);
    }
}

TEST(Time, microsecond)
{
    int year = 2000;
    int doy = 111;
    int hour = 11;
    int minute = 11;
    int second = 11;
    for(int microsecond = 0; microsecond < 1000000; microsecond++)
    {
        test_encode_decode(year, doy, hour, minute, second, microsecond);
    }
}
