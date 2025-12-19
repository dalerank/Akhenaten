#pragma once

#include "building/building.h"

struct event_fire_damage { building_id bid; };
struct event_collase_damage { building_id bid; };
struct event_flooded_damage { building_id bid; };

struct city_maintenance_t {
    int fire_spread_direction = 0;

    void check_building_destroying();
    void collapse_building(building *b);
    void flood_building(building *b);
    void destroy_by_enemy(building *b);
    void init();
    void check_kingdome_access();
    void update_fire_direction();

    int find_nearest_enemy_formation(tile2i tile);
};