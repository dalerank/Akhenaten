#pragma once

#include "building/building.h"
#include "graphics/boilerplate.h"
#include "grid/point.h"

// int get_farm_image(int grid_offset);
// int get_crops_image(int type, int growth);
// void draw_ph_crops(int type, int progress, int grid_offset, int x, int y, color color_mask);

building* building_determine_worker_needed();

int farm_expected_produce(building* b);

void building_industry_update_production(void);
void building_industry_update_farms(void);
void building_industry_update_wheat_production(void);
bool building_industry_has_produced_resource(building &b);
void building_industry_start_new_production(building* b);

bool building_farm_time_to_deliver(bool floodplains, int resource_id = 0);

void building_curse_farms(int big_curse);
void building_farm_deplete_soil(building* b);

void building_workshop_add_raw_material(building* b, int amount);

int building_get_workshop_for_raw_material(map_point tile, int resource, int distance_from_entry, int road_network_id, map_point* dst);
int building_get_workshop_for_raw_material_with_room(map_point tile, int resource, int distance_from_entry, int road_network_id, map_point* dst);