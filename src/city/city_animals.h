#pragma once

#include "figure/figure.h"

struct event_register_mission_animals { uint8_t mid; };

struct city_animals_t {
    bool herd_migration;

    void create_herds();
    void create_herd(tile2i tile);

    void init();
    void update();

    void update_herd_formation(formation *m);
    void move_animals(const formation *m, int attacking_animals, int terrain_mask);

    bool can_spawn_ph_wolf(formation *m);
    bool can_spawn_ostrich(formation *m);
    void set_herd_figures_to_initial(const formation *m);
    bool breeding_ground_at(tile2i tile, int size);
};
ANK_CONFIG_STRUCT(city_animals_t, herd_migration)

extern city_animals_t g_city_animals;

