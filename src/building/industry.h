#ifndef BUILDING_INDUSTRY_H
#define BUILDING_INDUSTRY_H

#include "building/building.h"
#include "map/point.h"
#include "graphics/image.h"

int get_farm_image(int grid_offset);
int get_crops_image(int type, int growth);
void draw_ph_crops(int type, int progress, int grid_offset, int x, int y, color_t color_mask);

int building_determine_worker_needed();

void building_industry_update_production(void);
void building_industry_update_wheat_production(void);
int building_industry_has_produced_resource(building *b);
void building_industry_start_new_production(building *b);

void building_bless_farms(void);
void building_curse_farms(int big_curse);
void building_farm_deplete_soil(const building *b);

void building_workshop_add_raw_material(building *b);

int building_get_workshop_for_raw_material(int x, int y, int resource, int distance_from_entry, int road_network_id,
                                           map_point *dst);
int building_get_workshop_for_raw_material_with_room(int x, int y, int resource, int distance_from_entry,
                                                     int road_network_id, map_point *dst);

#endif // BUILDING_INDUSTRY_H
