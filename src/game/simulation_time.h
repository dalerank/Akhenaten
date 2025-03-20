#pragma once

#include <cstdint>

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

struct game_date_t {
    union {
        int32_t ym;
        struct {
            int16_t year;
            int16_t month;
        };
    };

    game_date_t(int16_t y, int16_t m) : year(y), month(m) {}
    bool operator==(const game_date_t &o) const { return o.ym == ym; }
};

struct simulation_time_t {
    enum {
        days_in_month = 16,
        ticks_in_day = 50,
        months_in_year = 12,
    };

    int tick;  // 50 ticks in a day
    int16_t day;   // 16 days in a month
    int16_t month; // 12 months in a year
    int16_t year;
    int total_days;

    void init(int year);
    int16_t years_since_start() const;
    int absolute_day(bool since_start = false) const;
    int absolute_tick(bool since_start = false) const;
    int absolute_tick_year_start() const;

    bool advance_tick();
    bool advance_day();
    bool advance_month();
    void advance_year();

    game_date_t date() const { return {years_since_start(), month}; }
};

struct event_advance_date {
    int year, month, mday, abdday;
};

struct event_advance_day : public event_advance_date {
    static event_advance_day from_simtime(const simulation_time_t &tm) {
        return { tm.year, tm.month, tm.day, tm.absolute_day() };
    }
};

struct event_advance_month : public event_advance_date {
    static event_advance_month from_simtime(const simulation_time_t &tm) {
        return { tm.year, tm.month, tm.day, tm.absolute_day() };
    }
};
