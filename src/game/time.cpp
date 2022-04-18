#include <scenario/property.h>
#include <game/io/io_buffer.h>
#include "time.h"

static time_data data;

time_data* give_me_da_time() {
    return &data;
}

void game_time_init(int year) {
    data.tick = 0;
    data.day = 0;
    data.month = 0;
    data.total_days = 0;
    data.year = year;
}

int game_time_tick(void) {
    return data.tick;
}
int game_time_day(void) {
    return data.day;
}
int game_time_month(void) {
    return data.month;
}
int game_time_year(void) {
    return data.year;
}
int game_time_year_since_start(void) {
    return data.year - scenario_property_start_year();
}

int game_time_absolute_day() {
    return data.month * 16 + data.day;
}
int game_time_absolute_tick() {
    return game_time_absolute_day() * 51 + data.tick;
}

#include "core/game_environment.h"

int game_time_advance_tick(void) {
    if (++data.tick >= 50) {
        if (GAME_ENV == ENGINE_ENV_PHARAOH && data.tick == 50)
            return 0;
        data.tick = 0;
        return 1;
    }
    return 0;
}
int game_time_advance_day(void) {
    data.total_days++;
    if (++data.day >= 16) {
        data.day = 0;
        return 1;
    }
    return 0;
}
int game_time_advance_month(void) {
    if (++data.month >= 12) {
        data.month = 0;
        return 1;
    }
    return 0;
}
void game_time_advance_year(void) {
    ++data.year;
}

io_buffer *iob_game_time = new io_buffer([](io_buffer *iob) {
    iob->bind(BIND_SIGNATURE_INT32, &data.tick);
    iob->bind(BIND_SIGNATURE_INT32, &data.day);
    iob->bind(BIND_SIGNATURE_INT32, &data.month);
    iob->bind(BIND_SIGNATURE_INT32, &data.year);
    iob->bind(BIND_SIGNATURE_INT32, &data.total_days);
});
