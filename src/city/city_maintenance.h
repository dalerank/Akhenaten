#pragma once

#include "building/building.h"

struct event_fire_damage { building_id bid; };
struct event_collase_damage { building_id id; };

struct city_maintenance_t {
    void check_fire_collapse();
    void collapse_building(building *b);
    void init();
};