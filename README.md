Smalltime and Nanotime
======================

Simple and convenient binary date & time formats in 64 bits. Values are directly comparable (within the same type), and the standard Gregorian fields are easily extractable.



Features
--------

 * Encodes a complete date & time into a 64-bit integer.
 * Fields (including year) are compatible with ISO-8601.
 * Maintenance-free (no leap second tables to update).
 * Easily converts to human readable fields.
 * Supports hundreds of thousands of years (Smalltime).
 * Supports time units to the microsecond (Smalltime) or nanosecond (Nanotime).
 * Supports leap years and leap seconds.
 * Values are in timezone zero by default.
 * Encoded values are comparable within their types.



Specifications
--------------

* [Smalltime Specification](smalltime-specification.md)
* [Nanotime Specification](nanotime-specification.md)



Implementations
---------------

* [C implementation](https://github.com/kstenerud/c-smalltime)
* [Go implementation](https://github.com/kstenerud/go-smalltime)



License
-------

Copyright 2018 Karl Stenerud

Specification released under Creative Commons Attribution 4.0 International Public License https://creativecommons.org/licenses/by/4.0/

Reference implementation released under MIT License https://opensource.org/licenses/MIT
