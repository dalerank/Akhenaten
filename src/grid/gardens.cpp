#include "grid/gardens.h"

#include "grid/tiles.h"
#include "grid/terrain.h"
#include "grid/image.h"
#include "grid/property.h"
#include "building/building_garden.h"

void map_tiles_gardens_clear_garden_image(int grid_offset) {
    const bool is_garden = map_terrain_is(grid_offset, TERRAIN_GARDEN);
    const bool is_elevation = map_terrain_is(grid_offset, TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP);
    if (is_garden && !is_elevation) {
        map_image_set(grid_offset, 0);
        map_property_set_multi_tile_size(grid_offset, 1);
        map_property_mark_draw_tile(grid_offset);
    }
}

void map_tiles_gardens_update_all() {
    map_tiles_foreach_map_tile(map_tiles_gardens_clear_garden_image);
    map_tiles_foreach_map_tile(building_garden::set_image);
}

void map_tiles_gardens_determine() {
    map_tiles_foreach_map_tile(building_garden::determine_tile);
}