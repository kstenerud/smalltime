/*
 * Nanotime
 * =========
 *
 * A simple and convenient binary date & time format in 64 bits.
 *
 *
 * Features
 * --------
 *
 *  * Encodes a complete date & time into a 64-bit unsigned integer.
 *  * Fields (including year) are compatible with ISO-8601.
 *  * Maintenance-free (no leap second tables to update).
 *  * Easily converts to human readable fields.
 *  * Supports years 1970 to 2226.
 *  * Supports time units to the nanosecond.
 *  * Supports leap years and leap seconds.
 *  * Values are always in timezone zero.
 *  * Encoded values are comparable.
 *
 *
 * License
 * -------
 *
 * Copyright 2018 Karl Stenerud
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#ifndef KS_nanotime_H
#define KS_nanotime_H
#ifdef __cplusplus 
extern "C" {
#endif

#include <stdint.h>


typedef uint64_t nanotime;


// Internal defines. These will be undef'd at the end of the header.
#define NANOTIME_ZERO_YEAR 1970

#define NANOTIME_BITSHIFT_YEAR    56
#define NANOTIME_BITSHIFT_MONTH   52
#define NANOTIME_BITSHIFT_DAY     47
#define NANOTIME_BITSHIFT_HOUR    42
#define NANOTIME_BITSHIFT_MINUTE  36
#define NANOTIME_BITSHIFT_SECOND  30

#define NANOTIME_MASK_YEAR        (0xffULL << NANOTIME_BITSHIFT_YEAR)
#define NANOTIME_MASK_MONTH       (0xfULL  << NANOTIME_BITSHIFT_MONTH)
#define NANOTIME_MASK_DAY         (0x1fULL << NANOTIME_BITSHIFT_DAY)
#define NANOTIME_MASK_HOUR        (0x1fULL << NANOTIME_BITSHIFT_HOUR)
#define NANOTIME_MASK_MINUTE      (0x3fULL << NANOTIME_BITSHIFT_MINUTE)
#define NANOTIME_MASK_SECOND      (0x3fULL << NANOTIME_BITSHIFT_SECOND)
#define NANOTIME_MASK_MICROSECOND 0x3fffffff



/**
 * Create a new time value, encoding the fields into a 64-bit unsigned integer.
 * Note: This function does NOT validate input! Make sure your source values are correct!
 *
 * @param year The year (1970 - 2226).
 * @param month The month of the year (1 - 12).
 * @param day The day of the month (1 - 31).
 * @param hour The hour of the day (0 - 23).
 * @param minute The minute of the hour (0 - 59).
 * @param second The second of the minute, allowing for leap second (0 - 60).
 * @param nanosecond The nanosecond of the second (0 - 999999999).
 * @return A new time value.
 */
static inline nanotime nanotime_new(int year, int month, int day, int hour, int minute, int second, int nanosecond)
{
    return ((nanotime)(year-NANOTIME_ZERO_YEAR)   << NANOTIME_BITSHIFT_YEAR)   |
           ((nanotime)month  << NANOTIME_BITSHIFT_MONTH)  |
           ((nanotime)day    << NANOTIME_BITSHIFT_DAY)    |
           ((nanotime)hour   << NANOTIME_BITSHIFT_HOUR)   |
           ((nanotime)minute << NANOTIME_BITSHIFT_MINUTE) |
           ((nanotime)second << NANOTIME_BITSHIFT_SECOND) |
           nanosecond;
}

/**
 * Get the year component from a time value.
 *
 * @param time The existing time value.
 * @return the year component.
 */
static inline int nanotime_get_year(nanotime time)
{
    return (time >> NANOTIME_BITSHIFT_YEAR) + NANOTIME_ZERO_YEAR;
}

/**
 * Get a new time based on an existing one, with a new year component.
 * Valid range is 1970 - 2226.
 * Note: Input is NOT validated!
 *
 * @param time The existing time value.
 * @param year The year component.
 * @return the new time value.
 */
static inline nanotime nanotime_with_year(nanotime time, int year)
{
    return (time & ~NANOTIME_MASK_YEAR) |
        ((nanotime)(year-NANOTIME_ZERO_YEAR) << NANOTIME_BITSHIFT_YEAR);
}

/**
 * Get the month component from a time value.
 *
 * @param time The existing time value.
 * @return the day component.
 */
static inline int nanotime_get_month(nanotime time)
{
    return (time & NANOTIME_MASK_MONTH) >> NANOTIME_BITSHIFT_MONTH;
}

/**
 * Get a new time based on an existing one, with a new month component.
 * Valid range is 1 to 12.
 * Note: Input is NOT validated!
 *
 * @param time The existing time value.
 * @param month The month component.
 * @return the new time value.
 */
static inline nanotime nanotime_with_month(nanotime time, int month)
{
    return (time & ~NANOTIME_MASK_MONTH) | ((nanotime)month << NANOTIME_BITSHIFT_MONTH);
}

/**
 * Get the day component from a time value.
 *
 * @param time The existing time value.
 * @return the day component.
 */
static inline int nanotime_get_day(nanotime time)
{
    return (time & NANOTIME_MASK_DAY) >> NANOTIME_BITSHIFT_DAY;
}

/**
 * Get a new time based on an existing one, with a new day component.
 * Valid range is 1 to 31.
 * Note: Input is NOT validated!
 *
 * @param time The existing time value.
 * @param day The day component.
 * @return the new time value.
 */
static inline nanotime nanotime_with_day(nanotime time, int day)
{
    return (time & ~NANOTIME_MASK_DAY) | ((nanotime)day << NANOTIME_BITSHIFT_DAY);
}

/**
 * Get the hour component from a time value.
 *
 * @param time The existing time value.
 * @return the hour component.
 */
static inline int nanotime_get_hour(nanotime time)
{
    return (time & NANOTIME_MASK_HOUR) >> NANOTIME_BITSHIFT_HOUR;
}

/**
 * Get a new time based on an existing one, with a new hour component.
 * Valid range is 0 to 23.
 * Note: Input is NOT validated!
 *
 * @param time The existing time value.
 * @param hour The new hour component.
 * @return the new time value.
 */
static inline nanotime nanotime_with_hour(nanotime time, int hour)
{
    return (time & ~NANOTIME_MASK_HOUR) | ((nanotime)hour << NANOTIME_BITSHIFT_HOUR);
}

/**
 * Get the minute component from a time value.
 *
 * @param time The existing time value.
 * @return the minute component.
 */
static inline int nanotime_get_minute(nanotime time)
{
    return (time & NANOTIME_MASK_MINUTE) >> NANOTIME_BITSHIFT_MINUTE;
}

/**
 * Get a new time based on an existing one, with a new minute component.
 * Valid range is 0-59.
 * Note: Input is NOT validated!
 *
 * @param time The existing time value.
 * @param minute The minute component.
 * @return the new time value.
 */
static inline nanotime nanotime_with_minute(nanotime time, int minute)
{
    return (time & ~NANOTIME_MASK_MINUTE) | ((nanotime)minute << NANOTIME_BITSHIFT_MINUTE);
}

/**
 * Get the second component from a time value.
 *
 * @param time The existing time value.
 * @return the second component.
 */
static inline int nanotime_get_second(nanotime time)
{
    return (time & NANOTIME_MASK_SECOND) >> NANOTIME_BITSHIFT_SECOND;
}

/**
 * Get a new time based on an existing one, with a new second component.
 * Valid range is 0-60.
 * The value 60 is to support leap seconds.
 * Note: Input is NOT validated!
 *
 * @param time The existing time value.
 * @param second The second component.
 * @return the new time value.
 */
static inline nanotime nanotime_with_second(nanotime time, int second)
{
    return (time & ~NANOTIME_MASK_SECOND) | ((nanotime)second << NANOTIME_BITSHIFT_SECOND);
}

/**
 * Get the nanosecond component from a time value.
 *
 * @param time The existing time value.
 * @return the nanosecond component.
 */
static inline int nanotime_get_nanosecond(nanotime time)
{
    return time & NANOTIME_MASK_MICROSECOND;
}

/**
 * Get a new time based on an existing one, with a new nanosecond component.
 * Valid range is 0-999999999.
 * Note: Input is NOT validated!
 *
 * @param time The existing time value.
 * @param nanosecond The nanosecond component.
 * @return the new time value.
 */
static inline nanotime nanotime_with_nanosecond(nanotime time, int nanosecond)
{
    return (time & ~NANOTIME_MASK_MICROSECOND) | nanosecond;
}


#undef NANOTIME_ZERO_YEAR

#undef NANOTIME_BITSHIFT_YEAR
#undef NANOTIME_BITSHIFT_DAY
#undef NANOTIME_BITSHIFT_HOUR
#undef NANOTIME_BITSHIFT_MINUTE
#undef NANOTIME_BITSHIFT_SECOND

#undef NANOTIME_MASK_DAY
#undef NANOTIME_MASK_HOUR
#undef NANOTIME_MASK_MINUTE
#undef NANOTIME_MASK_SECOND
#undef NANOTIME_MASK_MICROSECOND


#ifdef __cplusplus 
}
#endif
#endif // KS_nanotime_H
