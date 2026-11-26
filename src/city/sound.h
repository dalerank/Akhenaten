#pragma once

#include <cstdint>

struct city_sound_t {
    int8_t march_enemy;
    int8_t march_horse;

    void reset();
    int update_march_enemy();
    int update_march_horse();
};

city_sound_t& city_sound();
