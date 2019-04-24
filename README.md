Smalltime
=========

A simple and convenient binary date & time format in 64 bits. Smalltime values are directly comparable, and the standard Gregorian fields are easily extractable.



Features
--------

 * Encodes a complete date & time into a 64-bit signed integer.
 * Fields (including year) are compatible with ISO-8601.
 * Maintenance-free (no leap second tables to update).
 * Easily converts to human readable fields.
 * Supports hundreds of thousands of years.
 * Supports time units to the microsecond.
 * Supports leap years and leap seconds.
 * Values are in timezone zero by default.
 * Encoded values are comparable.



Specification
-------------

[Smalltime Specification](smalltime-specification.md)



Implementations
---------------

* [C implementation](reference-implementation)
* [Go implementation](https://github.com/kstenerud/go-smalltime)



License
-------

Copyright 2018 Karl Stenerud

Specification released under Creative Commons Attribution 4.0 International Public License https://creativecommons.org/licenses/by/4.0/

Reference implementation released under MIT License https://opensource.org/licenses/MIT
