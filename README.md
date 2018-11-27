Smalltime
=========

A simple and convenient date & time format in 64 bits.



Features
--------

 * Encodes a complete date & time into a 64-bit signed integer.
 * Maintenance-free (no human managed tables to update).
 * Easily converts to human readable fields.
 * Supports hundreds of thousands of years.
 * Supports time units to the microsecond.
 * Supports leap years and leap seconds.
 * Values are always in timezone zero.
 * Encoded values are comparable.



Encoding
--------

Time fields are bit-encoded according to the following table, which lists their bit positions, bit width, and minimum and maximum allowed values.

| Field       | Position | Width | Min     | Max    | Extraction Algorithm |
| ----------- | -------- | ----- | ------- | ------ | -------------------- |
| Year        |       46 |    18 | -131072 | 131071 | (value >> 46)        |
| Day         |       37 |     9 |       1 |    366 | (value >> 37) & 511  |
| Hour        |       32 |     5 |       0 |     23 | (value >> 32) & 31   |
| Minute      |       26 |     6 |       0 |     59 | (value >> 26) & 63   |
| Second      |       20 |     6 |       0 |     60 | (value >> 20) & 63   |
| Microsecond |        0 |    20 |       0 | 999999 | value & 1048575      |


### The Year Field

The year field is interpreted as a signed two's complement integer. Values <= 0 represent dates in the BC era.

As the Anno Domini system has no zero year (there is no 0 BC or 0 AD), BC era dates are interpreted offset by 1 in order to preserve numeric continuity (0 = 1 BC, -1 = 2 BC, and so on). Thus, years from 131073 BC to 131071 AD are supported.


### The Day Field

Day goes to 366 to support leap years.


### The Second Field

Second goes to 60 to support leap seconds.



Invalid Encoding
----------------

If any field contains data outside of its allowed range, the time value is invalid.



Example
-------

| Encoded Value     | ISO8601 Equivalent        | Meaning                           |
| ----------------- | ------------------------- | --------------------------------- |
| 0x1f06568590dbc2e | 1985-299T08:22:16.900142Z | Oct 26th, 1985 8:22:16.900142 UTC |


#### Comparability

 * Adding a day (Oct 27th, 1985 8:22:16.900142) encodes to `0x1f06588590dbc2e`, which is greater than `0x1f06568590dbc2e`.
 * Subtracting a minute (Oct 26th, 1985 8:21:16.900142) encodes to `0x1f06568550dbc2e`, which is less than `0x1f06568590dbc2e`.



License
-------

Copyright 2018 Karl Stenerud

Specification released under Creative Commons Attribution 4.0 International Public License https://creativecommons.org/licenses/by/4.0/

Reference implementation released under MIT License https://opensource.org/licenses/MIT
