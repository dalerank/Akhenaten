#ifndef BUILDING_CONSTRUCTION_H
#define BUILDING_CONSTRUCTION_H

#include "building/type.h"

void map_add_venue_plaza_tiles(int building_id, int size, int x, int y, int image_id, bool update_only);

//int building_construction_place_building(int type, int x, int y);

void building_construction_set_type(int type);

void building_construction_clear_type(void);

int building_construction_type(void);

int building_construction_cost(void);

int building_construction_size(int *x, int *y);

bool building_construction_in_progress(void);

void building_construction_start(int x, int y, int grid_offset);

bool building_construction_is_draggable(void);

void building_construction_cancel(void);

void building_construction_update(int x, int y, int grid_offset);

void building_construction_finalize(void);

bool building_construction_can_place_on_terrain(int x, int y, int *warning_id, int size);

void building_construction_record_view_position(int view_x, int view_y, int grid_offset);
void building_construction_get_view_position(int *view_x, int *view_y);
int building_construction_get_start_grid_offset(void);

void building_construction_reset_draw_as_constructing(void);
int building_construction_draw_as_constructing(void);

#endif // BUILDING_CONSTRUCTION_H
