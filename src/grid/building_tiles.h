#pragma once

#include "grid/point.h"
#include "graphics/image_desc.h"
#include "building/building.h"

void map_building_tiles_add(int building_id, tile2i tile, int size, int image_id, int terrain);

void map_add_venue_plaza_tiles(int building_id, int size, tile2i tile, int image_id, bool update_only);

void map_building_tiles_remove(int building_id, tile2i tile);

// Resets one tile's building-grid pointer, image, sprite and properties to
// "empty land" — mirrors the per-tile work map_building_tiles_remove() does
// inside its inner loop. Pass building_type = 0 (BUILDING_NONE) when the
// caller has no associated building (e.g. clearing decorative tiles), so the
// rubble marker is skipped.
void map_building_tile_clear_at(int grid_offset, int building_type);
void map_building_tiles_set_rubble(int building_id, tile2i tile, int size);
void map_building_tiles_mark_deleting(int grid_offset);
bool map_building_tiles_mark_construction(tile2i tile, int size_x, int size_y, int terrain, bool absolute_xy);
int map_building_tiles_are_clear(tile2i tile, int size, int terrain);
