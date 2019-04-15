Reference Implementation for Smalltime
======================================

A C implementation to demonstrate smalltime.

Implemented as a header only (`smalltime.h`).



Header Dependencies
-------------------

 * stdint.h: For standard integer types



Usage
-----

```c
#include <smalltime/smalltime.h>
#include <stdio.h>

static void demonstrate_smalltime()
{
	smalltime noon_jan1_2000 =       smalltime_new(2000,  1, 12, 0, 0, 0);
	smalltime one_oclock_jan1_2000 = smalltime_new(2000,  1, 13, 0, 0, 0);
	smalltime noon_feb15_1999 =      smalltime_new(1999, 46, 12, 0, 0, 0);

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
	some_time = smalltime_with_day(some_time, 365);
	some_time = smalltime_with_hour(some_time, 14);
	some_time = smalltime_with_minute(some_time, 30);
	some_time = smalltime_with_second(some_time, 19);
	some_time = smalltime_with_microsecond(some_time, 885);
	printf("Year %d, day %d, hour %d, minute %d, second %d.%06d\n",
		smalltime_get_year(some_time),
		smalltime_get_day(some_time),
		smalltime_get_hour(some_time),
		smalltime_get_minute(some_time),
		smalltime_get_second(some_time),
		smalltime_get_microsecond(some_time)
		);
}
```

Converting from Gregorian month and day to day-of-year is pretty simple:

```c
static int g_days_to_the_month[] =
{
    0, // Nothing
    g_days_to_the_month[ 0] +  0, // January
    g_days_to_the_month[ 1] + 31, // February
    g_days_to_the_month[ 2] + 28, // March
    g_days_to_the_month[ 3] + 31, // April
    g_days_to_the_month[ 4] + 30, // May
    g_days_to_the_month[ 5] + 31, // June
    g_days_to_the_month[ 6] + 30, // July
    g_days_to_the_month[ 7] + 31, // August
    g_days_to_the_month[ 8] + 31, // September
    g_days_to_the_month[ 9] + 30, // October
    g_days_to_the_month[10] + 31, // November
    g_days_to_the_month[11] + 30, // December
};

static inline int is_leap_year(int year)
{
    return (year % 4 == 0) && (year % 100 != 0 || year % 400 == 0);
}

unsigned int to_doy(int year, unsigned int month, unsigned int day)
{
    unsigned int days = g_days_to_the_month[month] + day;
    if(is_leap_year(year))
    {
        days++;
    }
    return days;
}
```


Requirements
------------

  * Meson 0.49 or newer
  * Ninja 1.8.2 or newer
  * A C compiler
  * A C++ compiler (for the tests)



Building
--------

    meson build
    ninja -C build



Running Tests
-------------

    ninja -C build test

For the full report:

    ./build/run_tests



Installing
----------

    ninja -C build install
