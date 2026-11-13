#include "canals.h"

#include "core/profiler.h"
#include "graphics/image_groups.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "grid/grid.h"
#include "grid/image.h"
#include "grid/tiles.h"
#include "grid/property.h"
#include "scenario/map.h"
#include "io/io_buffer.h"
#include "grid/terrain.h"
#include "grid/basin.h"
#include "building/building.h"
#include "building/building_road.h"
#include "building/building_irrigation_ditch.h"
#include "city/city_buildings.h"
#include "grid/building.h"
#include "grid/image_context.h"
#include "graphics/view/view.h"
#include "game/game.h"
#include "game/game_config.h"

#include <array>
#include <cstdint>
#include <vector>

// When flood basins are on, do not stamp irrigation across a dike wall:
// only tiles that share the canal's basin_id (0 = outside / unsealed).
void map_add_irrigation_range(tile2i tile, int size, int radius) {
    if (!game_features::gameplay_enhanced_flood_basins.to_bool()) {
        map_terrain_add_with_radius(tile, size, radius, TERRAIN_IRRIGATION_RANGE);
        return;
    }

    const uint16_t src_id = map_basin_id_at(tile);
    grid_area area = map_grid_get_area(tile, size, radius);
    map_grid_area_foreach(area, [src_id](tile2i t) {
        if (map_basin_id_at(t) == src_id) {
            map_terrain_add(t, TERRAIN_IRRIGATION_RANGE);
        }
    });
}

static int canals_include_construction = 0;

grid_xx canals_grid(FS_UINT8);
grid_xx canals_grid_backup(FS_UINT8);

int map_canal_at(int grid_offset) {
    return map_grid_get(canals_grid, grid_offset);
}

void map_canal_set(int grid_offset, int value) {
    map_grid_set(canals_grid, grid_offset, value);
}

void map_canal_remove(int grid_offset) {
    map_grid_set(canals_grid, grid_offset, 0);
}

void map_canal_clear() {
    map_grid_clear(canals_grid);
}

void map_canal_backup() {
    map_grid_copy(canals_grid, canals_grid_backup);
}

void map_canal_restore(void) {
    map_grid_copy(canals_grid_backup, canals_grid);
}

io_buffer* iob_aqueduct_grid = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &canals_grid);
});

io_buffer *iob_aqueduct_backup_grid = new io_buffer([] (io_buffer *iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &canals_grid_backup);
});

static bool canal_image_follows_water(int grid_offset) {
    const int building_id = map_building_at(grid_offset);
    return building_id == 0 || building_get(building_id)->type == BUILDING_ROADBLOCK;
}

void map_canals_reset_water_supply() {
    OZZY_PROFILER_FUNCTION();
    map_terrain_remove_all(TERRAIN_IRRIGATION_RANGE);

    const int image_without_water
      = building_irrigation_ditch::images().begin + building_irrigation_ditch::image_set::IMAGE_FULL_OFFSET;
    int grid_offset = scenario_map_data()->start_offset;
    for (int y = 0; y < scenario_map_data()->height; y++, grid_offset += scenario_map_data()->border_size) {
        for (int x = 0; x < scenario_map_data()->width; x++, grid_offset++) {
            if (!map_terrain_is(grid_offset, TERRAIN_CANAL) || map_terrain_is(grid_offset, TERRAIN_WATER)) {
                continue;
            }
            if (!canal_image_follows_water(grid_offset)) {
                continue;
            }

            map_canal_set(grid_offset, 0);
            const int image_id = map_image_at(grid_offset);
            if (image_id < image_without_water) {
                map_image_set(grid_offset, image_id + building_irrigation_ditch::image_set::IMAGE_FULL_OFFSET);
            }
        }
    }
}

// OG map_water_supply_fill_canals_from_offset: unlimited BFS, the first new neighbour is walked next, the others queue.
void map_canal_fill_from_offset(tile2i tile) {
    if (!map_terrain_is(tile, TERRAIN_CANAL)) {
        return;
    }

    const int image_without_water
      = building_irrigation_ditch::images().begin + building_irrigation_ditch::image_set::IMAGE_FULL_OFFSET;
    const std::array<int, 4> cardinal_delta
      = {GRID_OFFSET(0, -1), GRID_OFFSET(1, 0), GRID_OFFSET(0, 1), GRID_OFFSET(-1, 0)};
    std::vector<int> queue;
    size_t queue_head = 0;
    int grid_offset = tile.grid_offset();
    for (;;) {
        // OG spins on a water tile until its guard runs out: the rest of this fill is dropped.
        if (map_terrain_is(grid_offset, TERRAIN_WATER)) {
            return;
        }

        map_canal_set(grid_offset, 1);
        map_tiles_set_canal_image(grid_offset);
        const int image_id = map_image_at(grid_offset);
        if (image_id >= image_without_water) {
            map_image_set(grid_offset, image_id - building_irrigation_ditch::image_set::IMAGE_FULL_OFFSET);
        }

        int next_offset = -1;
        for (const int delta : cardinal_delta) {
            const int new_offset = grid_offset + delta;
            const int building_id = map_building_at(new_offset);
            building* neighbour = building_id ? building_get(building_id) : nullptr;
            if (neighbour && neighbour->type == BUILDING_WATER_LIFT) {
                if (!neighbour->has_water_access) {
                    neighbour->has_water_access = 2;
                }
            } else if (map_terrain_is(new_offset, TERRAIN_CANAL) && !map_canal_at(new_offset)) {
                map_add_irrigation_range(tile2i(new_offset), 1, 2);
                if (next_offset == -1) {
                    next_offset = new_offset;
                } else {
                    queue.push_back(new_offset);
                }
            }
        }

        if (next_offset == -1) {
            if (queue_head == queue.size()) {
                return;
            }
            next_offset = queue[queue_head++];
        }
        grid_offset = next_offset;
    }
}

// Clipped to same basin_id so radius-2 does not leak across a dike.
static void map_stamp_irrigation_from_wet_canals() {
    int grid_offset = scenario_map_data()->start_offset;
    for (int y = 0; y < scenario_map_data()->height; y++, grid_offset += scenario_map_data()->border_size) {
        for (int x = 0; x < scenario_map_data()->width; x++, grid_offset++) {
            if (!map_terrain_is(grid_offset, TERRAIN_CANAL) || map_terrain_is(grid_offset, TERRAIN_WATER)) {
                continue;
            }
            if (map_canal_at(grid_offset) <= 0) {
                continue;
            }
            map_add_irrigation_range(tile2i(grid_offset), 1, 2);
        }
    }
}

void map_irrigation_restamp_from_wet_canals() {
    OZZY_PROFILER_FUNCTION();
    map_terrain_remove_all(TERRAIN_IRRIGATION_RANGE);
    map_stamp_irrigation_from_wet_canals();
}

void set_terrain_canal_connections(int grid_offset, int direction, int multi_tile_mask, image_tiles_vec& tiles) {
    int offset = grid_offset + map_grid_direction_delta(direction);
    if (map_terrain_is(offset, TERRAIN_BUILDING)) {
        building *b = building_at(offset);
        if (b->type == BUILDING_WATER_LIFT) {
            int lift_direction_binary = b->orientation % 2;
            int canal_direction_binary = (direction / 2) % 2;
            if (lift_direction_binary == canal_direction_binary)
                tiles[direction] = 1;
            return;
        }
    }

    if (map_terrain_is(offset, TERRAIN_WATER)) {
        tiles[direction] = 1;
    }
}

terrain_image map_image_context_get_canal(int grid_offset) {
    image_tiles_vec tiles = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int has_road = map_terrain_is(grid_offset, TERRAIN_ROAD) ? 1 : 0;
    for (int i = 0; i < MAP_IMAGE_MAX_TILES; i += 2) {
        int offset = grid_offset + map_grid_direction_delta(i);
        if (!map_terrain_is(offset, TERRAIN_CANAL)) {
            continue;
        }

        if (has_road) {
            if (!map_terrain_is(offset, TERRAIN_ROAD))
                tiles[i] = 1;
        } else {
            tiles[i] = 1;
        }
    }

    set_terrain_canal_connections(grid_offset, 0, EDGE_X1Y2, tiles);
    set_terrain_canal_connections(grid_offset, 2, EDGE_X0Y1, tiles);
    set_terrain_canal_connections(grid_offset, 4, EDGE_X1Y0, tiles);
    set_terrain_canal_connections(grid_offset, 6, EDGE_X2Y1, tiles);
    return map_image_context_get_terrain_image(CONTEXT_CANAL, tiles);
}

int get_canal_image(int grid_offset, bool is_road, int terrain, const terrain_image img) {
    if (map_terrain_is(grid_offset, TERRAIN_WATER)) {
        return 0;
    }

    int image_canal_set_begin = building_irrigation_ditch::images().begin; // 119 C3
    int water_offset = (map_canal_at(grid_offset) > 0) ? 0 : building_irrigation_ditch::image_set::IMAGE_FULL_OFFSET;

    // floodplains
    int floodplains_offset = 0;
    if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN))
        floodplains_offset = IMAGE_CANAL_FLOODPLAIN_OFFSET;

    // curve/connection offset
    int image_offset = img.group_offset;
    // TODO: some edge cases with roads don't perfectly match up with original game (not really a priority?)
    if (is_road) {
        bool road_dir_right = false;
        if (map_terrain_is(grid_offset + GRID_OFFSET(0, -1), TERRAIN_ROAD))
            road_dir_right = true;

        if (map_terrain_is(grid_offset + GRID_OFFSET(0, 1), TERRAIN_ROAD))
            road_dir_right = true;

        road_dir_right = g_camera.relative_orientation(road_dir_right) % 2;
        bool is_paved = building_road::is_paved(tile2i(grid_offset));

        if (road_dir_right) // left/right offset is opposite from C3
            image_offset = 0;
        else
            image_offset = 1;
        if (is_paved) {
            floodplains_offset = 0; // no floodplains version for paved roads
            image_offset += 42;
        } else
            image_offset += 15;
    } else {
        if (image_offset <= 3) {
            image_offset = !(image_offset - 2);
        } else if (image_offset <= 7) {
            image_offset -= 2;
        }
    }
    // TODO: canals disappearing into the Nile river --- good luck with that!
    return image_canal_set_begin + water_offset + floodplains_offset + image_offset;
}

void map_tiles_set_canal_image(int grid_offset) {
    const bool is_canal = map_terrain_is(grid_offset, TERRAIN_CANAL) && !map_terrain_is(grid_offset, TERRAIN_WATER);

    if (!is_canal) {
        return;
    }

    const terrain_image img = map_image_context_get_canal(grid_offset);
    bool is_road = map_terrain_is(grid_offset, TERRAIN_ROAD);
    if (is_road)
        map_property_clear_plaza_or_earthquake(grid_offset);

    int image_id = get_canal_image(grid_offset, is_road, 0, img);
    if (image_id) {
        map_image_set(grid_offset, image_id);
        map_property_set_multi_tile_size(grid_offset, 1);
        map_property_mark_draw_tile(grid_offset);
    }
}

void map_canal_update_all_tiles(int include_construction) {
    canals_include_construction = include_construction;
    map_tiles_foreach_map_tile(map_tiles_set_canal_image);
    canals_include_construction = 0;
}