package smalltime

import "testing"
import "fmt"
func workaround_unused_import_error_fmt() {
	fmt.Printf("")
}

func assert_encode_decode(t *testing.T, year, month, day, hour, minute, second, usec int) {
	time := New(year, month, day, hour, minute, second, usec)
	if(time.Year() != year || time.Month() != month || time.Day() != day ||
	time.Minute() != minute || time.Second() != second || time.Microsecond() != usec) {
		t.Errorf("Expected: %04d-%02d-%02dT%02d:%02d:%02d.%06d, Actual: %04d-%02d-%02dT%02d:%02d:%02d.%06d (doy %d)",
		year, month, day, hour, minute, second, usec,
		time.Year(), time.Month(), time.Day(), time.Hour(), time.Minute(), time.Second(), time.Microsecond(), time.Doy())
	}
}

func assert_encode(t *testing.T, year, month, day, hour, minute, second, usec int, encoded Smalltime) {
	time := New(year, month, day, hour, minute, second, usec)
	if time != encoded {
		t.Errorf("Expected %04d-%02d-%02dT%02d:%02d:%02d.%06d to encode to %016x. Actual: %016x",
		year, month, day, hour, minute, second, usec, encoded, time)
	}
}

func assert_decode(t *testing.T, time Smalltime, year, month, day, hour, minute, second, usec int) {
	if(time.Year() != year || time.Month() != month || time.Day() != day ||
	time.Minute() != minute || time.Second() != second || time.Microsecond() != usec) {
		t.Errorf("Expected %016x to decode to %04d-%02d-%02dT%02d:%02d:%02d.%06d. Actual: %04d-%02d-%02dT%02d:%02d:%02d.%06d",
		time, year, month, day, hour, minute, second, usec,
		time.Year(), time.Month(), time.Day(), time.Hour(), time.Minute(), time.Second(), time.Microsecond())
	}
}

func assert_yd_to_md(t *testing.T, year, doy, month, day int) {
	mm, dd := doy_to_ymd(year, doy)
	if(mm != month || dd != day) {
		t.Errorf("Expected Y %d DOY %d to give M %d D %d, but got %d %d", year, doy, month, day, mm, dd)
	}
}

func assert_ymd_to_doy(t *testing.T, year, month, day, doy int) {
	dd := ymd_to_doy(year, month, day)
	if(dd != doy) {
		t.Errorf("Expected Y %d M %d D %d to give DOY %d, but got %d", year, month, day, doy, dd)
	}
}

var days_in_month_normal = [...]int {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
var days_in_month_leap = [...]int {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
func test_is_leap_year(year int) bool {
	if year % 100 == 0 {
		return year % 400 == 0
	}
	return year % 4 == 0
}

// ==================================================================

func Test409Years(t *testing.T) {
	for year := 1999; year <= 2408; year++ {
		days_in_month_table := &days_in_month_normal
		if test_is_leap_year(year) {
			days_in_month_table = &days_in_month_leap
		}
		for month := 1; month <= 12; month++ {
			days_in_month := days_in_month_table[month]
			for day := 1; day <= days_in_month; day++ {
				assert_encode_decode(t, year, month, day, 0, 0, 0, 0)
			}
		}
	}
}

func TestYmdToDoy(t *testing.T) {
    assert_ymd_to_doy(t, 1985,  1,  1,   1)
    assert_ymd_to_doy(t, 1985,  1,  2,   2)
    assert_ymd_to_doy(t, 1985,  1, 31,  31)
    assert_ymd_to_doy(t, 1985,  2,  1,  32)
    assert_ymd_to_doy(t, 1985,  2, 28,  59)
    assert_ymd_to_doy(t, 1985,  3,  1,  60)
    assert_ymd_to_doy(t, 1985,  3,  2,  61)
    assert_ymd_to_doy(t, 1985,  3, 31,  90)
    assert_ymd_to_doy(t, 1985,  4,  1,  91)
    assert_ymd_to_doy(t, 1985, 12, 30, 364)
    assert_ymd_to_doy(t, 1985, 12, 31, 365)
    assert_ymd_to_doy(t, 1986,  1,  1,   1)

    assert_ymd_to_doy(t, 2000,  1,  1,   1)
    assert_ymd_to_doy(t, 2000,  1,  2,   2)
    assert_ymd_to_doy(t, 2000,  1, 31,  31)
    assert_ymd_to_doy(t, 2000,  2,  1,  32)
    assert_ymd_to_doy(t, 2000,  2, 28,  59)
    assert_ymd_to_doy(t, 2000,  2, 29,  60)
    assert_ymd_to_doy(t, 2000,  3,  1,  61)
    assert_ymd_to_doy(t, 2000,  3,  2,  62)
    assert_ymd_to_doy(t, 2000,  3, 31,  91)
    assert_ymd_to_doy(t, 2000,  4,  1,  92)
    assert_ymd_to_doy(t, 2000, 12, 30, 365)
    assert_ymd_to_doy(t, 2000, 12, 31, 366)
    assert_ymd_to_doy(t, 2001,  1,  1,   1)

    assert_ymd_to_doy(t, 2100,  1,  1,   1)
    assert_ymd_to_doy(t, 2100,  1,  2,   2)
    assert_ymd_to_doy(t, 2100,  1, 31,  31)
    assert_ymd_to_doy(t, 2100,  2,  1,  32)
    assert_ymd_to_doy(t, 2100,  2, 28,  59)
    assert_ymd_to_doy(t, 2100,  3,  1,  60)
    assert_ymd_to_doy(t, 2100,  3,  2,  61)
    assert_ymd_to_doy(t, 2100,  3, 31,  90)
    assert_ymd_to_doy(t, 2100,  4,  1,  91)
    assert_ymd_to_doy(t, 2100, 12, 30, 364)
    assert_ymd_to_doy(t, 2100, 12, 31, 365)
    assert_ymd_to_doy(t, 2101,  1,  1,   1)
}

func TestDoyToYmd(t *testing.T) {
    assert_yd_to_md(t, 1985,   1,  1,  1)
    assert_yd_to_md(t, 1985,   2,  1,  2)
    assert_yd_to_md(t, 1985,  31,  1, 31)
    assert_yd_to_md(t, 1985,  32,  2,  1)
    assert_yd_to_md(t, 1985,  59,  2, 28)
    assert_yd_to_md(t, 1985,  60,  3,  1)
    assert_yd_to_md(t, 1985,  61,  3,  2)
    assert_yd_to_md(t, 1985,  90,  3, 31)
    assert_yd_to_md(t, 1985,  91,  4,  1)
    assert_yd_to_md(t, 1985, 364, 12, 30)
    assert_yd_to_md(t, 1985, 365, 12, 31)
    assert_yd_to_md(t, 1986,   1,  1,  1)

    assert_yd_to_md(t, 2000,   1,  1,  1)
    assert_yd_to_md(t, 2000,   2,  1,  2)
    assert_yd_to_md(t, 2000,  31,  1, 31)
    assert_yd_to_md(t, 2000,  32,  2,  1)
    assert_yd_to_md(t, 2000,  59,  2, 28)
    assert_yd_to_md(t, 2000,  60,  2, 29)
    assert_yd_to_md(t, 2000,  61,  3,  1)
    assert_yd_to_md(t, 2000,  62,  3,  2)
    assert_yd_to_md(t, 2000,  91,  3, 31)
    assert_yd_to_md(t, 2000,  92,  4,  1)
    assert_yd_to_md(t, 2000, 365, 12, 30)
    assert_yd_to_md(t, 2000, 366, 12, 31)
    assert_yd_to_md(t, 2001,   1,  1,  1)

    assert_yd_to_md(t, 2100,   1,  1,  1)
    assert_yd_to_md(t, 2100,   2,  1,  2)
    assert_yd_to_md(t, 2100,  31,  1, 31)
    assert_yd_to_md(t, 2100,  32,  2,  1)
    assert_yd_to_md(t, 2100,  59,  2, 28)
    assert_yd_to_md(t, 2100,  60,  3,  1)
    assert_yd_to_md(t, 2100,  61,  3,  2)
    assert_yd_to_md(t, 2100,  90,  3, 31)
    assert_yd_to_md(t, 2100,  91,  4,  1)
    assert_yd_to_md(t, 2100, 364, 12, 30)
    assert_yd_to_md(t, 2100, 365, 12, 31)
    assert_yd_to_md(t, 2101,   1,  1,  1)
}

func TestReadmeExamples(t *testing.T) {
    assert_decode(t, Smalltime(0x1f06568590dbc2e), 1985, 10, 26, 8, 22, 16, 900142)
    assert_decode(t, Smalltime(0x1f06588590dbc2e), 1985, 10, 27, 8, 22, 16, 900142)
    assert_decode(t, Smalltime(0x1f06568550dbc2e), 1985, 10, 26, 8, 21, 16, 900142)

}
