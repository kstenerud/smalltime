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



Requirements to Build Tests
---------------------------

  * CMake 3.5 or higher
  * A C compiler
  * A C++ compiler



Building Tests
--------------

    mkdir build
    cd build
    cmake ..
    make



Running Tests
-------------

    ./test/smalltime_test
