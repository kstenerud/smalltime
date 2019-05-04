Nanotime
=========

A simple and convenient binary date & time format in 64 bits. Nanotime values are directly comparable, and the standard Gregorian fields are easily extractable.



Features
--------

 * Encodes a complete date & time into a 64-bit unsigned integer.
 * Fields (including year) are compatible with ISO-8601.
 * Maintenance-free (no leap second tables to update).
 * Easily converts to human readable fields.
 * Supports years 1970 to 2226.
 * Supports time units to the nanosecond.
 * Supports leap years and leap seconds.
 * Values are in timezone zero by default.
 * Encoded values are comparable.



Encoding
--------

Time fields are bit-encoded according to the following table, which lists their bit positions, bit width, and minimum and maximum allowed values.

| Field       | Position | Width | Min  | Max       | Extraction Algorithm |
| ----------- | -------- | ----- | ---- | --------- | -------------------- |
| Year        |       56 |     8 | 1970 |      2226 | (value >> 56)        |
| Month       |       52 |     4 |    1 |        12 | (value >> 52) & 16   |
| Day         |       47 |     5 |    1 |        31 | (value >> 47) & 31   |
| Hour        |       42 |     5 |    0 |        23 | (value >> 42) & 31   |
| Minute      |       36 |     6 |    0 |        59 | (value >> 36) & 63   |
| Second      |       30 |     6 |    0 |        60 | (value >> 30) & 63   |
| Microsecond |        0 |    30 |    0 | 999999999 | value & 0x3fffffff   |


### Special Field Notes

#### The Year Field

The year field is interpreted as an unsigned integer with a "zero year" of 1970. For example, a year field value of `30` represents the year `2000`.

#### The Second Field

The second field goes to 60 to support leap seconds.



Time Zone
---------

Values must be relative to UTC, unless other outside accompanying data or agreements specify otherwise.



Invalid Encoding
----------------

If any field contains values outside of its allowed range, the time value is invalid.



Example
-------

| Encoded Value      | ISO8601 Equivalent             | Meaning                              |
| ------------------ | ------------------------------ | ------------------------------------ |
| 0x0fad2164076290ee | 1985-10-26T08:22:16.123900142Z | Oct 26th, 1985 8:22:16.123900142 UTC |


#### Comparability

 * Adding a day (Oct 27th, 1985 8:22:16.900142) encodes to `0x0fada164076290ee`, which is greater than `0x0fad2164076290ee`.
 * Subtracting a minute (Oct 26th, 1985 8:21:16.900142) encodes to `0x0fad2154076290ee`, which is less than `0x0fad2164076290ee`.



License
-------

Copyright 2018 Karl Stenerud

Specification released under Creative Commons Attribution 4.0 International Public License https://creativecommons.org/licenses/by/4.0/
