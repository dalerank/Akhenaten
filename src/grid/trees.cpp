#include "trees.h"

#include "tile_cache.h"
#include "core/profiler.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "graphics/image_groups.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "grid/random.h"
#include "grid/moisture.h"
#include "grid/image.h"
#include "grid/property.h"
#include "vegetation.h"
#include "grid/canals.h"

tile_cache trees_tiles_cache;

void map_tree_clear() {
    trees_tiles_cache.clear();
}

void map_tree_push_back(int grid_offset) {
    trees_tiles_cache.push_back(grid_offset);
}

void map_tree_foreach_tile(void (*callback)(int grid_offset)) {
    for (int i = 0; i < trees_tiles_cache.size(); i++) {
        callback(trees_tiles_cache.at(i));
    }
}

void map_tree_growth_update() {
    OZZY_PROFILER_SECTION("Game/Map/Trees Growth Update");
    const auto &opt = g_scenario.env.tree_grow;
    for (int tile_offset : trees_tiles_cache) {
        vegetation_tile_update(tile_offset, opt);
    }
}

void map_tree_update_image(int grid_offset) {
    int x = MAP_X(grid_offset);
    int y = MAP_Y(grid_offset);

    if (map_terrain_is(grid_offset, TERRAIN_TREE)
        && !map_terrain_is(grid_offset, TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP)) {
        int image_id = image_id_from_group(GROUP_TERRAIN_TREE) + (map_random_get(grid_offset) & 7);

        int grasslevel = map_grasslevel_get(grid_offset);
        if (map_get_vegetation_growth(grid_offset) == 255) {
            if (map_terrain_has_only_rocks_trees_in_ring(x, y, 3))
                image_id += 56;
            else if (map_terrain_has_only_rocks_trees_in_ring(x, y, 2))
                image_id += 48;
            else {
                if (grasslevel > 8)
                    image_id += 32;
                else if (grasslevel > 4)
                    image_id += 16;
                if (map_terrain_has_only_rocks_trees_in_ring(x, y, 1))
                    image_id += 8;
            }
        } else {
            image_id += 64;
            if (grasslevel > 8)
                image_id += 16;
            else if (grasslevel > 4)
                image_id += 8;
            //            if (map_terrain_has_only_rocks_trees_in_ring(x, y, 1))
            //                image_id += 8;
        }
        map_image_set(grid_offset, image_id);

        //        if (map_terrain_has_only_rocks_trees_in_ring(x, y, 3))
        //            map_image_set(grid_offset, image_id + 24);
        //        else if (map_terrain_has_only_rocks_trees_in_ring(x, y, 2))
        //            map_image_set(grid_offset, image_id + 16);
        //        if (map_terrain_has_only_rocks_trees_in_ring(x, y, 1))
        //            map_image_set(grid_offset, image_id + 8);
        //        else
        //            map_image_set(grid_offset, image_id);

        map_property_set_multi_tile_size(grid_offset, 1);
        map_property_mark_draw_tile(grid_offset);
        map_canal_set(grid_offset, 0);
    }
}

void map_tree_update_all_tiles() {
    map_tree_foreach_tile(map_tree_update_image);
}

void map_tree_update_region_tiles(tile2i min, tile2i max) {
    map_tiles_foreach_region_tile(min, max, map_tree_update_image_3x3);
}

void map_tree_update_region_tiles(int x_min, int y_min, int x_max, int y_max) {
    map_tiles_foreach_region_tile(tile2i(x_min, y_min), tile2i(x_max, y_max), map_tree_update_image_3x3);
}

void map_tree_update_image_3x3(int grid_offset) {
    int x = MAP_X(grid_offset);
    int y = MAP_Y(grid_offset);
    if (map_terrain_is(grid_offset, TERRAIN_TREE)
        && !map_terrain_is(grid_offset, TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP)) {
        map_tiles_foreach_region_tile(tile2i(x - 1, y - 1), tile2i(x + 1, y + 1), map_tree_update_image);
    }
}