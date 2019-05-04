#include <gtest/gtest.h>
#include <smalltime/nanotime.h>


// ==================================================================
// Helpers
// ==================================================================

static void test_encode_decode(int year, int month, int day, int hour, int minute, int second, int nanosecond)
{
    nanotime encoded = nanotime_new(year, month, day, hour, minute, second, nanosecond);
    int actual_year = nanotime_get_year(encoded);
    int actual_month = nanotime_get_month(encoded);
    int actual_day = nanotime_get_day(encoded);
    int actual_hour = nanotime_get_hour(encoded);
    int actual_minute = nanotime_get_minute(encoded);
    int actual_second = nanotime_get_second(encoded);
    int actual_nanosecond = nanotime_get_nanosecond(encoded);

    EXPECT_EQ(year, actual_year);
    EXPECT_EQ(month, actual_month);
    EXPECT_EQ(day, actual_day);
    EXPECT_EQ(hour, actual_hour);
    EXPECT_EQ(minute, actual_minute);
    EXPECT_EQ(second, actual_second);
    EXPECT_EQ(nanosecond, actual_nanosecond);

    nanotime piecemeal_encoded = 0;
    piecemeal_encoded = nanotime_with_year(encoded, year);
    piecemeal_encoded = nanotime_with_month(encoded, month);
    piecemeal_encoded = nanotime_with_day(encoded, day);
    piecemeal_encoded = nanotime_with_hour(encoded, hour);
    piecemeal_encoded = nanotime_with_minute(encoded, minute);
    piecemeal_encoded = nanotime_with_second(encoded, second);
    piecemeal_encoded = nanotime_with_nanosecond(encoded, nanosecond);

    EXPECT_EQ(encoded, piecemeal_encoded);
}

static void test_single_date(
    nanotime expected_encoded,
    int expected_year,
    int expected_month,
    int expected_day,
    int expected_hour,
    int expected_minute,
    int expected_second,
    int expected_nanosecond)
{
    int actual_year = nanotime_get_year(expected_encoded);
    int actual_month = nanotime_get_month(expected_encoded);
    int actual_day = nanotime_get_day(expected_encoded);
    int actual_hour = nanotime_get_hour(expected_encoded);
    int actual_minute = nanotime_get_minute(expected_encoded);
    int actual_second = nanotime_get_second(expected_encoded);
    int actual_nanosecond = nanotime_get_nanosecond(expected_encoded);

    EXPECT_EQ(expected_year, actual_year);
    EXPECT_EQ(expected_month, actual_month);
    EXPECT_EQ(expected_day, actual_day);
    EXPECT_EQ(expected_hour, actual_hour);
    EXPECT_EQ(expected_minute, actual_minute);
    EXPECT_EQ(expected_second, actual_second);
    EXPECT_EQ(expected_nanosecond, actual_nanosecond);

    nanotime actual_encoded = nanotime_new(expected_year, expected_month, expected_day, expected_hour, expected_minute, expected_second, expected_nanosecond);

    EXPECT_EQ(expected_encoded, actual_encoded);
}


// ==================================================================
// Tests
// ==================================================================

TEST(Nanotime, spec_examples)
{
    test_single_date(0x0fad2164076290ee, 1985, 10, 26, 8, 22, 16, 123900142);
    test_single_date(0x0fada164076290ee, 1985, 10, 27, 8, 22, 16, 123900142);
    test_single_date(0x0fad2154076290ee, 1985, 10, 26, 8, 21, 16, 123900142);
}

TEST(Nanotime, comparisons)
{
    EXPECT_GT(nanotime_new(2000, 1, 1, 0, 0, 0, 1), nanotime_new(2000, 1, 1, 0, 0, 0, 0));
    EXPECT_GT(nanotime_new(2000, 1, 1, 0, 0, 1, 0), nanotime_new(2000, 1, 1, 0, 0, 0, 999999));
    EXPECT_GT(nanotime_new(2000, 1, 1, 0, 0, 2, 0), nanotime_new(2000, 1, 1, 0, 0, 1, 0));
    EXPECT_GT(nanotime_new(2000, 1, 1, 0, 1, 0, 0), nanotime_new(2000, 1, 1, 0, 0, 60, 0));
    EXPECT_GT(nanotime_new(2000, 1, 1, 0, 2, 0, 0), nanotime_new(2000, 1, 1, 0, 1, 0, 0));
    EXPECT_GT(nanotime_new(2000, 1, 1, 1, 0, 0, 0), nanotime_new(2000, 1, 1, 0, 59, 0, 0));
    EXPECT_GT(nanotime_new(2000, 1, 1, 2, 0, 0, 0), nanotime_new(2000, 1, 1, 1, 0, 0, 0));
    EXPECT_GT(nanotime_new(2000, 1, 2, 0, 0, 0, 0), nanotime_new(2000, 1, 1, 23, 0, 0, 0));
    EXPECT_GT(nanotime_new(2000, 1, 2, 0, 0, 0, 0), nanotime_new(2000, 1, 1, 0, 0, 0, 0));
    EXPECT_GT(nanotime_new(2005, 1, 1, 0, 0, 0, 0), nanotime_new(2004, 12, 31, 0, 0, 0, 0));
    EXPECT_GT(nanotime_new(1, 1, 1, 0, 0, 0, 0), nanotime_new(0, 1, 1, 0, 0, 0, 0));
    EXPECT_GT(nanotime_new(0, 1, 1, 0, 0, 0, 0), nanotime_new(-1, 1, 1, 0, 0, 0, 0));
    EXPECT_GT(nanotime_new(1, 1, 1, 0, 0, 0, 0), nanotime_new(-1, 1, 1, 0, 0, 0, 0));
}

TEST(Nanotime, year)
{
    int month = 1;
    int day = 11;
    int hour = 11;
    int minute = 11;
    int second = 11;
    int nanosecond = 111111;
    for(int year = 1970; year < 2226; year++)
    {
        test_encode_decode(year, month, day, hour, minute, second, nanosecond);
    }
}

TEST(Nanotime, day)
{
    int year = 2000;
    int month = 1;
    int hour = 11;
    int minute = 11;
    int second = 11;
    int nanosecond = 111111;
    for(int day = 1; day < 28; day++)
    {
        test_encode_decode(year, month, day, hour, minute, second, nanosecond);
    }
}

TEST(Nanotime, hour)
{
    int year = 2000;
    int month = 1;
    int day = 11;
    int minute = 11;
    int second = 11;
    int nanosecond = 111111;
    for(int hour = 0; hour < 24; hour++)
    {
        test_encode_decode(year, month, day, hour, minute, second, nanosecond);
    }
}

TEST(Nanotime, minute)
{
    int year = 2000;
    int month = 1;
    int day = 11;
    int hour = 11;
    int second = 11;
    int nanosecond = 111111;
    for(int minute = 0; minute < 60; minute++)
    {
        test_encode_decode(year, month, day, hour, minute, second, nanosecond);
    }
}

TEST(Nanotime, second)
{
    int year = 2000;
    int month = 1;
    int day = 11;
    int hour = 11;
    int minute = 11;
    int nanosecond = 111111;
    for(int second = 0; second < 61; second++)
    {
        test_encode_decode(year, month, day, hour, minute, second, nanosecond);
    }
}

TEST(Nanotime, nanosecond)
{
    int year = 2000;
    int month = 1;
    int day = 11;
    int hour = 11;
    int minute = 11;
    int second = 11;
    for(int nanosecond = 0; nanosecond < 1000000; nanosecond++)
    {
        test_encode_decode(year, month, day, hour, minute, second, nanosecond);
    }
}
