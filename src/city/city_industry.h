#pragma once

#include "building/building.h"
#include "graphics/graphics.h"
#include "grid/point.h"

struct city_industry_t {
    void update_production();
    // Remake: when gameplay_change_industry_nearby_houses is on, set houses_covered
    // from houses within building nearby_houses_radius for flags.need_nearby_houses_for_work.
    void update_nearby_houses_weekly();
};

void building_industry_update_farms();

struct delivery_destination {
    int building_id = 0;
    tile2i dest = tile2i(-1);
};

delivery_destination building_get_asker_for_resource(tile2i tile, e_building_type btype, e_resource resource, int road_network_id, int distance_from_entry);

void building_workshop_add_raw_material(building* b, int amount, e_resource res);

int building_get_workshop_for_raw_material(tile2i tile, e_resource resource, int distance_from_entry, int road_network_id, tile2i& dst);
int building_get_workshop_for_raw_material_with_room(tile2i tile, e_resource resource, int distance_from_entry, int road_network_id, tile2i& dst);