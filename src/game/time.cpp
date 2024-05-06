#include "time.h"

#include "io/io_buffer.h"
#include "scenario/scenario.h"

static game_time g_game_time;

constexpr int max_game_tick = 50;

const game_time& gametime() {
    return g_game_time;
}

void game_time_init(int year) {
    g_game_time.tick = 0;
    g_game_time.day = 0;
    g_game_time.month = 0;
    g_game_time.total_days = 0;
    g_game_time.year = year;
}

int game_time_tick(void) {
    return g_game_time.tick;
}
int game_time_day(void) {
    return g_game_time.day;
}
int game_time_month(void) {
    return g_game_time.month;
}

int game_time_year(void) {
    return g_game_time.year;
}

int game_time_year_since_start(void) {
    return g_game_time.year - scenario_property_start_year();
}

int game_time_absolute_day(bool since_start) {
    int days = g_game_time.month * 16 + g_game_time.day;
    if (since_start)
        days += 192 * game_time_year_since_start();
    return days;
}

int game_time_absolute_tick(bool since_start) {
    int ticks = game_time_absolute_day() * 51 + g_game_time.tick;
    if (since_start)
        ticks += 9792 * game_time_year_since_start();
    return ticks;
}

#include "core/game_environment.h"

int game_time_advance_tick(void) {
    if (++g_game_time.tick >= max_game_tick) {
        g_game_time.tick = 0;
        return 1;
    }
    return 0;
}
int game_time_advance_day(void) {
    g_game_time.total_days++;
    if (++g_game_time.day >= 16) {
        g_game_time.day = 0;
        return 1;
    }
    return 0;
}
int game_time_advance_month(void) {
    if (++g_game_time.month >= 12) {
        g_game_time.month = 0;
        return 1;
    }
    return 0;
}
void game_time_advance_year(void) {
    ++g_game_time.year;
}

io_buffer* iob_game_time = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_INT32, &g_game_time.tick);
    iob->bind(BIND_SIGNATURE_INT32, &g_game_time.day);
    iob->bind(BIND_SIGNATURE_INT32, &g_game_time.month);
    iob->bind(BIND_SIGNATURE_INT32, &g_game_time.year);
    iob->bind(BIND_SIGNATURE_INT32, &g_game_time.total_days);
});
