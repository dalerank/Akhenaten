#include "grid/terrain.h"
#include "grid/road_canal.h"
#include "grid/point.h"
#include "grid/grid.h"
#include "grid/routing/routing.h"
#include "building/building_irrigation_ditch.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "core/profiler.h"
#include "mujs/mujs.h"
#include "js/js_game.h"

bool __map_terrain_is(tile2i tile, int terrain_mask) {
    return map_terrain_is(tile, terrain_mask);
}
ANK_FUNCTION_2(__map_terrain_is)

void __map_terrain_add(tile2i tile, int terrain) {
    map_terrain_add(tile, terrain);
}
ANK_FUNCTION_2(__map_terrain_add)

bool __map_terrain_has_adjacent_x_with_type(tile2i tile, int terrain) {
    return map_terrain_has_adjacent_x_with_type(tile.grid_offset(), terrain);
}
ANK_FUNCTION_2(__map_terrain_has_adjacent_x_with_type)

bool __map_terrain_has_adjacent_y_with_type(tile2i tile, int terrain) {
    return map_terrain_has_adjacent_y_with_type(tile.grid_offset(), terrain);
}
ANK_FUNCTION_2(__map_terrain_has_adjacent_y_with_type)

bool __map_terrain_has_adjacent_with_type(tile2i tile, int terrain) {
    return map_terrain_has_adjecent_with_type(tile.grid_offset(), terrain);
}
ANK_FUNCTION_2(__map_terrain_has_adjacent_with_type)

int __map_terrain_count_directly_adjacent_with_type(tile2i tile, int terrain) {
    return map_terrain_count_directly_adjacent_with_type(tile.grid_offset(), terrain);
}
ANK_FUNCTION_2(__map_terrain_count_directly_adjacent_with_type)

bool __map_can_place_road_under_canal(tile2i tile) {
    return map_can_place_road_under_canal(tile);
}
ANK_FUNCTION_1(__map_can_place_road_under_canal)

int __map_get_canal_with_road_image(tile2i tile) {
    return map_get_canal_with_road_image(tile.grid_offset());
}
ANK_FUNCTION_1(__map_get_canal_with_road_image)

int __terrain_dirt_road_image_base() {
    return image_id_from_group(GROUP_TERRAIN_DIRT_ROAD);
}
ANK_FUNCTION(__terrain_dirt_road_image_base)

int __terrain_canal_image_begin() {
    return building_irrigation_ditch::images().begin;
}
ANK_FUNCTION(__terrain_canal_image_begin)

int __map_grid_offset(tile2i tile) {
    return MAP_OFFSET(tile.x(), tile.y());
}
ANK_FUNCTION_1(__map_grid_offset);

int __map_grid_direction_delta(int direction) {
    return map_grid_direction_delta(direction);
}
ANK_FUNCTION_1(__map_grid_direction_delta);

int __map_grid_tiledir_offset(tile2i tile, int direction) {
    return MAP_OFFSET(tile.x(), tile.y()) + map_grid_direction_delta(direction);
}
ANK_FUNCTION_2(__map_grid_tiledir_offset);

tile2i __map_tile_at_grid_offset(int grid_offset) {
    return tile2i(grid_offset);
}
ANK_FUNCTION_1(__map_tile_at_grid_offset);

int __map_routing_distance_at_grid_offset(int grid_offset) {
    return map_routing_distance(grid_offset);
}
ANK_FUNCTION_1(__map_routing_distance_at_grid_offset);
