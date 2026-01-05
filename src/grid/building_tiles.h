#pragma once

#include "grid/point.h"
#include "graphics/image_desc.h"
#include "building/building.h"

void map_building_tiles_add(int building_id, tile2i tile, int size, int image_id, int terrain);

void map_add_venue_plaza_tiles(int building_id, int size, tile2i tile, int image_id, bool update_only);

void map_building_tiles_remove(int building_id, tile2i tile);
void map_building_tiles_set_rubble(int building_id, tile2i tile, int size);
void map_building_tiles_mark_deleting(int grid_offset);
bool map_building_tiles_mark_construction(tile2i tile, int size_x, int size_y, int terrain, bool absolute_xy);
int map_building_tiles_are_clear(tile2i tile, int size, int terrain);
