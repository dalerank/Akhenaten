#include "simulation_time.h"

#include "io/io_buffer.h"
#include "scenario/scenario.h"
#include "game/game.h"
#include "js/js_game.h"

e_month_tokens_t ANK_CONFIG_ENUM(e_month_tokens);

void simulation_time_t::init(int year) {
    tick = 0;
    day = 0;
    month = 0;
    total_days = 0;
    year = year;
}

int16_t simulation_time_t::years_since_start() const {
    return year - g_scenario.start_year;
}

int simulation_time_t::absolute_day(bool since_start) const {
    int days = month * days_in_month + day;
    if (since_start)
        days += (days_in_month * months_in_year)/*192*/ * years_since_start();
    return days;
}

int simulation_time_t::absolute_tick_year_start() const {
    return (ticks_in_day * days_in_month * months_in_year) /*9792*/ * years_since_start();
}

int simulation_time_t::absolute_tick(bool since_start) const {
    const int ticks = absolute_day(since_start) * ticks_in_day + tick;
    return ticks;
}

bool simulation_time_t::advance_tick() {
    if (++tick >= simulation_time_t::ticks_in_day) {
        tick = 0;
        return true;
    }
    return false;
}

day_result simulation_time_t::advance_day() {
    total_days++;
    bool is_week_advanced = false;
    ++day;
    is_week_advanced = (day > 0) && ((day % days_in_week) == 0);
    if (day >= simulation_time_t::days_in_month) {
        day = 0;
        return { is_week_advanced, true };
    }
    return { is_week_advanced, false };
}

bool simulation_time_t::advance_month() {
    if (++month >= 12) {
        month = 0;
        return true;
    }
    return false;
}

void simulation_time_t::advance_year() {
    ++year;
}

io_buffer* iob_game_time = new io_buffer([](io_buffer* iob, size_t version) {
    auto &data = game.simtime;
    iob->bind(BIND_SIGNATURE_INT8, &data.tick);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_INT16, &data.day);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_INT16, &data.month);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_INT16, &data.year);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_INT32, &data.total_days);
});
