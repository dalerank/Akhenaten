#pragma once

enum e_month {
    MONTH_JANUARY = 0,
    MONTH_FEBRUARY = 1,
    MONTH_MARCH = 2,
    MONTH_APRIL = 3,
    MONTH_MAY = 4,
    MONTH_JUNE = 5,
    MONTH_JULY = 6,
    MONTH_AUGUST = 7,
    MONTH_SEPTEMPTER = 8,
    MONTH_OCTOBER = 9,
    MONTH_NOVEMBER = 10,
    MONTH_DECEMBER = 11,
};

/**
 * @file
 * Game time.
 * One year has 12 months.
 * One month has 16 days.
 * One day has 50 ticks.
 */

struct game_time_t {
    enum {
        days_in_month = 16,
        ticks_in_day = 50,
        months_in_year = 12,
    };

    int tick;  // 50 ticks in a day
    int day;   // 16 days in a month
    int month; // 12 months in a year
    int year;
    int total_days;

    void init(int year);
    int years_since_start() const;
    int absolute_day(bool since_start = false) const;
    int absolute_tick(bool since_start = false) const;

    bool advance_tick();
    bool advance_day();
    bool advance_month();
    void advance_year();
};

const game_time_t& gametime();
