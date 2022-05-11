#ifndef GAME_TIME_H
#define GAME_TIME_H

#include "core/buffer.h"

typedef struct time_data {
    int tick; // 50 ticks in a day
    int day; // 16 days in a month
    int month; // 12 months in a year
    int year;
    int total_days;
} time_data_t;

enum {
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

/**
 * Initializes game time to the given year with all other fields zero
 * @param year Year
 */
void game_time_init(int year);

/**
 * The current game year
 *
 */
int game_time_year(void);

/**
 * The current game year count since the starting year
 *
 */
int game_time_year_since_start(void);

/**
 * The current game month within the year
 */
int game_time_month(void);

/**
 * The current game day within the month
 */
int game_time_day(void);

/**
 * The current game tick within the day
 */
int game_time_tick(void);

int game_time_absolute_day(bool since_start = false);
int game_time_absolute_tick(bool since_start = false);


/**
 * Increases tick
 * @return True if the tick overflows
 */
int game_time_advance_tick(void);

/**
 * Increase day
 * @return True if the day overflows
 */
int game_time_advance_day(void);

/**
 * Increase month
 * @return True if the month overflows
 */
int game_time_advance_month(void);

/**
 * Increase year
 */
void game_time_advance_year(void);

const time_data_t * game_time_struct();

#endif // GAME_TIME_H
