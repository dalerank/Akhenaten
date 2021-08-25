#ifndef OZYMANDIAS_CONSTRUCTION_PLANNER_H
#define OZYMANDIAS_CONSTRUCTION_PLANNER_H

#include "map/point.h"

void planner_reset_tiles(int size_x, int size_y);
void planner_set_pivot(int x, int y);
void planner_update_coord_caches(const map_tile *cursor_tile, int x, int y);

void planner_set_graphics_row(int row, int *image_ids, int total);
void planner_set_graphics_array(int *image_set, int size_x, int size_y);

void planner_set_tile_size(int row, int column, int size);
void plannet_set_allowed_terrain(int row, int column, int terrain);

void planner_update_obstructions();
int planner_get_blocked_count();
bool planner_is_obstructed();

void planner_draw_blueprints(int x, int y, bool fully_blocked = false);
void planner_draw_graphics(int x, int y);

void planner_draw_all(const map_tile *cursor_tile, int x, int y);

#endif //OZYMANDIAS_CONSTRUCTION_PLANNER_H
