#include <gtest/gtest.h>
#include <smalltime/smalltime.h>
#include <smalltime/nanotime.h>
#include <stdio.h>

static void demonstrate_smalltime()
{
	smalltime noon_jan1_2000 =       smalltime_new(2000, 1, 1, 12, 0, 0, 0);
	smalltime one_oclock_jan1_2000 = smalltime_new(2000, 1, 1, 13, 0, 0, 0);
	smalltime noon_feb15_1999 =      smalltime_new(1999, 2, 15, 12, 0, 0, 0);

	if(one_oclock_jan1_2000 > noon_jan1_2000)
	{
		printf("One o'clock is greater than noon.\n");
	}

	if(noon_feb15_1999 < noon_jan1_2000)
	{
		printf("feb 15, 1999 is less than jan 1, 2000\n");
	}

	smalltime some_time = 0;
	some_time = smalltime_with_year(some_time, 2018);
	some_time = smalltime_with_month(some_time, 12);
	some_time = smalltime_with_day(some_time, 31);
	some_time = smalltime_with_hour(some_time, 14);
	some_time = smalltime_with_minute(some_time, 30);
	some_time = smalltime_with_second(some_time, 19);
	some_time = smalltime_with_microsecond(some_time, 885);
	printf("Year %d, month %d, day %d, hour %d, minute %d, second %d.%06d\n",
		smalltime_get_year(some_time),
		smalltime_get_month(some_time),
		smalltime_get_day(some_time),
		smalltime_get_hour(some_time),
		smalltime_get_minute(some_time),
		smalltime_get_second(some_time),
		smalltime_get_microsecond(some_time)
		);
}

static void demonstrate_nanotime()
{
	nanotime noon_jan1_2000 =       nanotime_new(2000, 1, 1, 12, 0, 0, 0);
	nanotime one_oclock_jan1_2000 = nanotime_new(2000, 1, 1, 13, 0, 0, 0);
	nanotime noon_feb15_1999 =      nanotime_new(1999, 2, 15, 12, 0, 0, 0);

	if(one_oclock_jan1_2000 > noon_jan1_2000)
	{
		printf("One o'clock is greater than noon.\n");
	}

	if(noon_feb15_1999 < noon_jan1_2000)
	{
		printf("feb 15, 1999 is less than jan 1, 2000\n");
	}

	nanotime some_time = 0;
	some_time = nanotime_with_year(some_time, 2018);
	some_time = nanotime_with_month(some_time, 12);
	some_time = nanotime_with_day(some_time, 31);
	some_time = nanotime_with_hour(some_time, 14);
	some_time = nanotime_with_minute(some_time, 30);
	some_time = nanotime_with_second(some_time, 19);
	some_time = nanotime_with_nanosecond(some_time, 885);
	printf("Year %d, month %d, day %d, hour %d, minute %d, second %d.%06d\n",
		nanotime_get_year(some_time),
		nanotime_get_month(some_time),
		nanotime_get_day(some_time),
		nanotime_get_hour(some_time),
		nanotime_get_minute(some_time),
		nanotime_get_second(some_time),
		nanotime_get_nanosecond(some_time)
		);
}

TEST(Readme, example)
{
	demonstrate_smalltime();
	demonstrate_nanotime();
}
