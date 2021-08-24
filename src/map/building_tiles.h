#ifndef MAP_BUILDING_TILES_H
#define MAP_BUILDING_TILES_H

#include "building/building.h"

struct tile_graphics_query {
    int x;
    int y;
    int size;
    int image_id;
    int building_id;
};

void map_building_tiles_add(int building_id, int x, int y, int size, int image_id, int terrain);
void map_building_tiles_add_farm(int building_id, int x, int y, int crop_image_offset, int progress);
int map_building_tiles_add_aqueduct(int x, int y);

void map_add_bandstand_tiles(building *b);
void map_add_venue_plaza_tiles(int building_id, int size, int x, int y, int image_id, bool update_only);

void map_building_tiles_remove(int building_id, int x, int y);
void map_building_tiles_set_rubble(int building_id, int x, int y, int size);
void map_building_tiles_mark_deleting(int grid_offset);
int map_building_tiles_mark_construction(int x, int y, int size, int terrain, int absolute_xy);
int map_building_tiles_are_clear(int x, int y, int size, int terrain);

#endif // MAP_BUILDING_TILES_H
