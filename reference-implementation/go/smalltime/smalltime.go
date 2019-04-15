/*
TODO
*/
package smalltime

import "time"

import "fmt"
func blah() {
	fmt.Printf("")
}

type Smalltime int64

const bitshift_year = 46
const bitshift_doy = 37
const bitshift_hour = 32
const bitshift_minute = 26
const bitshift_second = 20

const mask_year = uint64(0x3ffff) << bitshift_year
const mask_doy = Smalltime(0x1ff) << bitshift_doy
const mask_hour = Smalltime(0x1f) << bitshift_hour
const mask_minute = Smalltime(0x3f) << bitshift_minute
const mask_second = Smalltime(0x3f) << bitshift_second
const mask_microsecond = Smalltime(0xfffff)

func is_leap_year(year int) bool {
	return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)
}

func ymd_to_doy(year, month, day int) (doy int) {
	months_from_march := (month + 9) % 12 // [0, 11]
	doy = (153 * months_from_march + 2) / 5 + day - 1 // [0, 365]
	if is_leap_year(year) {
		doy = (doy + 60) % 366
	} else {
		doy = (doy + 59) % 365
	}
	doy += 1
	return doy // [1, 366]
}

func doy_to_ymd(year, doy int) (month, day int) {
	if is_leap_year(year) {
		doy = (doy + 305) % 366
	} else {
		doy = (doy + 305) % 365
	}
	months_from_march := (5 * doy + 2) / 153 // [0, 11]
	day = doy - (153 * months_from_march + 2) / 5 + 1 // [1, 31]
	month = (months_from_march + 2) % 12 + 1 // [1, 12]
	return month, day
}

func FromTime(t time.Time) Smalltime {
	return New(t.Year(), int(t.Month()), t.Day(), t.Hour(), t.Minute(), t.Second(), t.Nanosecond()/1000)
}

// Set the time using the Gregorian calendar.
func New(year, month, day, hour, minute, second, microsecond int) Smalltime {
	return NewWithDoy(year, ymd_to_doy(year, month, day), hour, minute, second, microsecond)
}

// Set the time using day-of-year notation.
// This is required for dates prior to October 1582.
func NewWithDoy(year, day_of_year, hour, minute, second, microsecond int) Smalltime {
	return Smalltime(year)<<bitshift_year |
		Smalltime(day_of_year)<<bitshift_doy |
		Smalltime(hour)<<bitshift_hour |
		Smalltime(minute)<<bitshift_minute |
		Smalltime(second)<<bitshift_second |
		Smalltime(microsecond)
}

func (t Smalltime) AsTime() time.Time {
	return time.Date(t.Year(), time.Month(t.Month()), t.Day(), t.Hour(), t.Minute(), t.Second(), t.Microsecond()*1000, time.UTC)
}

func (time Smalltime) Year() int {
	return int(time >> bitshift_year)
}

func (time Smalltime) Doy() int {
	return int((time & mask_doy) >> bitshift_doy)
}

func (time Smalltime) Month() int {
	month, _ := doy_to_ymd(time.Year(), time.Doy())
	return month
}

func (time Smalltime) Day() int {
	_, day := doy_to_ymd(time.Year(), time.Doy())
	return day
}

func (time Smalltime) Hour() int {
	return int((time & mask_hour) >> bitshift_hour)
}

func (time Smalltime) Minute() int {
	return int((time & mask_minute) >> bitshift_minute)
}

func (time Smalltime) Second() int {
	return int((time & mask_second) >> bitshift_second)
}

func (time Smalltime) Microsecond() int {
	return int(time & mask_microsecond)
}

func (time Smalltime) WithYear(year int) Smalltime {
	return time&Smalltime(^mask_year) | Smalltime(year)<<bitshift_year
}

func (time Smalltime) WithDoy(doy int) Smalltime {
	return time&Smalltime(^mask_doy) | Smalltime(doy)<<bitshift_doy
}

func (time Smalltime) WithMonth(month int) Smalltime {
	return time.WithDoy(ymd_to_doy(time.Year(), month, time.Day()))
}

func (time Smalltime) WithDay(day int) Smalltime {
	return time.WithDoy(ymd_to_doy(time.Year(), time.Month(), day))
}

func (time Smalltime) WithHour(hour int) Smalltime {
	return time&Smalltime(^mask_hour) | Smalltime(hour)<<bitshift_hour
}

func (time Smalltime) WithMinute(minute int) Smalltime {
	return time&Smalltime(^mask_minute) | Smalltime(minute)<<bitshift_minute
}

func (time Smalltime) WithSecond(second int) Smalltime {
	return time&Smalltime(^mask_second) | Smalltime(second)<<bitshift_second
}

func (time Smalltime) WithMicrosecond(microsecond int) Smalltime {
	return time&Smalltime(^mask_microsecond) | Smalltime(microsecond)
}
