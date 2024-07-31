#pragma once

#include <cstdint>

struct city_figures_t {
    uint8_t fish_number;
    uint8_t animals_number;
    int32_t attacking_natives;
    int32_t enemies;
    int32_t kingdome_soldiers;
    int32_t rioters;
    int32_t soldiers;
    int32_t security_breach_duration;

    void reset();
    void on_post_load();
    void update();
    void add_animal();
};