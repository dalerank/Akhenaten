#include "time.h"

time_data data;

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

void game_time_save_state(buffer *buf) {
    buf->write_i32(data.tick);
    buf->write_i32(data.day);
    buf->write_i32(data.month);
    buf->write_i32(data.year);
    buf->write_i32(data.total_days);
}

void game_time_load_state(buffer *buf) {
    data.tick = buf->read_i32();
    data.day = buf->read_i32();
    data.month = buf->read_i32();
    data.year = buf->read_i32();
    data.total_days = buf->read_i32();
}
