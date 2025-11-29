#pragma once

#include "figure/figure.h"

struct event_register_mission_animals { uint8_t mid; };

struct city_animals_t {
    bool herd_migration;

    void create_herds();
    formation* create_herd(tile2i tile, e_figure_type ftype, int num_animals);

    void init();
    void update();
    void remove_all();

    void update_herd_formation(formation *m);
    void move_animals(const formation *m, int attacking_animals, int terrain_mask);

    bool can_spawn_ph_wolf(formation *m);
    bool can_spawn_ostrich(formation *m);
    void set_herd_figures_to_initial(const formation *m);
    bool breeding_ground_at(tile2i tile, int size);
    bool get_free_tile(int x, int y, int allow_negative_desirability, tile2i &outtile);
    bool get_roaming_destination(int formation_id, int allow_negative_desirability, tile2i tile, int distance, int direction, tile2i &outtile);

    void add_animals_point(int index, int x, int y, e_figure_type ftype, int num_animals);
    void set_animals_area(int index, int reseach_radius);
};
ANK_CONFIG_STRUCT(city_animals_t, herd_migration)

extern city_animals_t g_city_animals;

