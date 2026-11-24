#pragma once

#include <cstdint>

struct city_sound_t {
    int8_t march_enemy;
    int8_t march_horse;
    int8_t march_wolf;
    int8_t shoot_arrow;
    int8_t hit_soldier;
    int8_t hit_spear;
    int8_t hit_club;
    int8_t hit_elephant;
    int8_t hit_axe;
    int8_t hit_wolf;
    int8_t die_citizen;
    int8_t die_soldier;

    void reset();
    int update_march_enemy();
    int update_march_horse();
    int update_march_wolf();
    int update_shoot_arrow();
    int update_hit_wolf();
    int update_hit_soldier();
    int update_hit_axe();
    int update_hit_club();
    int update_hit_spear();
    int update_hit_elephant();
    int update_die_citizen();
    int update_die_soldier();
};

city_sound_t& city_sound();
