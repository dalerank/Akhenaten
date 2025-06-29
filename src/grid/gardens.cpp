#include "grid/gardens.h"

#include "grid/tiles.h"
#include "grid/terrain.h"
#include "grid/image.h"
#include "grid/property.h"
#include "building/building_garden.h"
#include "grid/tile_cache.h"
#include "dev/debug.h"

grid_xx g_terraing_garden_value = { 0, FS_INT8 };
grid_xx g_terraing_garden_decay = { 0, FS_INT8 };

declare_console_command_p(gardendecay) {
    std::string args; is >> args;
    int v = atoi(args.empty() ? (pcstr)"0" : args.c_str());

    map_tiles_foreach_map_tile([v] (tile2i tile) {
        const bool is_garden = map_terrain_is(tile, TERRAIN_GARDEN);
        if (is_garden) {
            map_tiles_garden_decay_update(tile, v);
        }
    });
};

declare_console_command_p(gardenclear) {
    map_tiles_gardens_clear_all();
}

void map_tiles_gardens_garden_value(int grid_offset) {
    const bool is_garden = map_terrain_is(grid_offset, TERRAIN_GARDEN);
    if (is_garden) {
        tile2i tcenter(grid_offset);
        tile2i tmin = tcenter.shifted(-1, -1);
        tile2i tmax = tcenter.shifted(1, 1);

        map_grid_bound_area(tmin, tmax);

        int garden_value = 0;
        map_grid_area_foreach(tmin, tmax, [&] (tile2i t) {
            const bool is_garden = map_terrain_is(t, TERRAIN_GARDEN);
            garden_value += (is_garden ? 1 : 0);
        });

        map_tiles_garden_set(tcenter, garden_value);
    }
}

void map_tiles_gardens_clear_garden_image(int grid_offset) {
    const bool is_garden = map_terrain_is(grid_offset, TERRAIN_GARDEN);
    const bool is_elevation = map_terrain_is(grid_offset, TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP);
    if (is_garden && !is_elevation) {
        map_image_set(grid_offset, 0);
        map_property_set_multi_tile_size(grid_offset, 1);
        map_property_mark_draw_tile(grid_offset);
    }
}

void map_tiles_garden_set(tile2i tile, int value) {
    map_grid_set(g_terraing_garden_value, tile, value);
}

int map_tiles_garden_get(tile2i tile, bool with_decay) {
    const int value = map_grid_get(g_terraing_garden_value, tile);
    const int decay = with_decay ? map_grid_get(g_terraing_garden_decay, tile) : 0;
    const int max_value = std::max(value - decay, 1);
    return max_value;
}

int map_tiles_garden_decay_get(tile2i tile) {
    const int decay = map_grid_get(g_terraing_garden_decay, tile);
    return decay;
}

int map_tiles_garden_decay_update(tile2i tile, int delta) {
    const int decay = map_grid_get(g_terraing_garden_decay, tile);
    map_grid_set(g_terraing_garden_decay, tile, decay + delta);
    return decay;
}

int map_garden_at(int grid_offset) {
    const bool is_garden = map_terrain_is(grid_offset, TERRAIN_GARDEN);
    return is_garden;
}

void map_tiles_gardens_clear_all() {
    map_grid_clear(g_terraing_garden_value);
    map_grid_clear(g_terraing_garden_decay);
}

void map_tiles_gardens_update_all() {
    map_tiles_foreach_map_tile(map_tiles_gardens_clear_garden_image);
    map_tiles_foreach_map_tile(building_garden::set_image);
    map_tiles_foreach_map_tile(map_tiles_gardens_garden_value);
}

void map_tiles_gardens_determine() {
    map_tiles_foreach_map_tile(building_garden::determine_tile);
}