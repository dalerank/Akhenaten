#pragma once

#include "building/building.h"
#include "grid/point.h"
#include "game/resource.h"

class buffer;

// void building_barracks_add_weapon(building *barracks);
// int building_barracks_create_soldier(building *barracks, int x, int y);
// int building_barracks_create_tower_sentry(building *barracks, int x, int y);

void building_barracks_request_tower_sentry();
void building_barracks_decay_tower_sentry_request();
int building_barracks_has_tower_sentry_request();

void building_barracks_save_state(buffer* buf);
void building_barracks_load_state(buffer* buf);

// void building_barracks_toggle_priority(building *barracks);
// int building_barracks_get_priority(building *barracks);

enum e_barracks_priority {
    PRIORITY_TOWER = 0,
    PRIORITY_FORT = 1,
};
