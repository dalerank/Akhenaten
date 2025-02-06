#include "canals.h"

#include "core/profiler.h"
#include "graphics/image_groups.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "grid/image.h"
#include "grid/property.h"
#include "scenario/map.h"
#include "io/io_buffer.h"
#include "grid/terrain.h"
#include "building/building.h"
#include "city/city_buildings.h"

#define MAX_QUEUE 1000

struct water_supply_queue_t {
    int items[MAX_QUEUE];
    int head;
    int tail;
};

water_supply_queue_t g_water_supply_queue;

static unsigned int river_access_canal_offsets[300] = {};
static int river_access_canal_offsets_total = 0;

static grid_xx canals_grid = {0, FS_UINT8};
static grid_xx canals_grid_backup = {0, FS_UINT8};

int map_canal_at(int grid_offset) {
    return map_grid_get(canals_grid, grid_offset);
}

void map_canal_set(int grid_offset, int value) {
    map_grid_set(canals_grid, grid_offset, value);
}

void map_canal_remove(int grid_offset) {
    map_grid_set(canals_grid, grid_offset, 0);
    if (map_grid_get(canals_grid, grid_offset + GRID_OFFSET(0, -1)) == 5)
        map_grid_set(canals_grid, grid_offset + GRID_OFFSET(0, -1), 1);

    if (map_grid_get(canals_grid, grid_offset + GRID_OFFSET(1, 0)) == 6)
        map_grid_set(canals_grid, grid_offset + GRID_OFFSET(1, 0), 2);

    if (map_grid_get(canals_grid, grid_offset + GRID_OFFSET(0, 1)) == 5)
        map_grid_set(canals_grid, grid_offset + GRID_OFFSET(0, 1), 3);

    if (map_grid_get(canals_grid, grid_offset + GRID_OFFSET(-1, 0)) == 6)
        map_grid_set(canals_grid, grid_offset + GRID_OFFSET(-1, 0), 4);
}

void map_canal_clear() {
    map_grid_clear(canals_grid);
}

void map_canal_backup() {
    void* t = malloc(12);
    uint16_t* x = (uint16_t*)t;

    uint16_t g = x[2];
    x[4] = 1;

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

static void canals_empty_all(void) {
    // reset river access counters
    river_access_canal_offsets_total = 0;

    int image_without_water = image_id_from_group(GROUP_BUILDING_AQUEDUCT) + IMAGE_CANAL_FULL_OFFSET;
    int grid_offset = scenario_map_data()->start_offset;
    for (int y = 0; y < scenario_map_data()->height; y++, grid_offset += scenario_map_data()->border_size) {
        for (int x = 0; x < scenario_map_data()->width; x++, grid_offset++) {
            if (map_terrain_is(grid_offset, TERRAIN_CANAL) && !map_terrain_is(grid_offset, TERRAIN_WATER)) {
                map_canal_set(grid_offset, 0);
                int image_id = map_image_at(grid_offset);
                if (image_id < image_without_water)
                    map_image_set(grid_offset, image_id + IMAGE_CANAL_FULL_OFFSET);

                // check if canal has river access
                if (map_terrain_count_directly_adjacent_with_type(grid_offset, TERRAIN_WATER) > 0) {
                    river_access_canal_offsets[river_access_canal_offsets_total] = grid_offset;
                    river_access_canal_offsets_total++;
                }
            }
        }
    }
}

void map_canal_fill_from_offset(int grid_offset) {
    if (!map_terrain_is(grid_offset, TERRAIN_CANAL) || map_terrain_is(grid_offset, TERRAIN_WATER)) {
        return;
    }

    memset(&g_water_supply_queue, 0, sizeof(g_water_supply_queue));
    int guard = 0;
    int next_offset;
    int image_without_water = image_id_from_group(GROUP_BUILDING_AQUEDUCT) + IMAGE_CANAL_FULL_OFFSET;
    do {
        if (++guard >= GRID_SIZE_TOTAL)
            break;

        map_canal_set(grid_offset, 1);
        int image_id = map_image_at(grid_offset);
        if (image_id >= image_without_water) {
            map_image_set(grid_offset, image_id - IMAGE_CANAL_FULL_OFFSET);
        }
        map_terrain_add_with_radius(tile2i(grid_offset), 1, 2, TERRAIN_IRRIGATION_RANGE);

        next_offset = -1;
        for (int i = 0; i < 4; i++) {
            const int ADJACENT_OFFSETS[] = {-GRID_LENGTH, 1, GRID_LENGTH, -1};
            int new_offset = grid_offset + ADJACENT_OFFSETS[i];
            building* b = building_at(new_offset);
            if (b->id && b->type == BUILDING_WATER_LIFT) {
                // check if aqueduct connects to reservoir --> doesn't connect to corner
                int xy = map_property_multi_tile_xy(new_offset);
                if (xy != EDGE_X0Y0 && xy != EDGE_X2Y0 && xy != EDGE_X0Y2 && xy != EDGE_X2Y2) {
                    if (!b->has_water_access) {
                        b->has_water_access = 2;
                    }
                }
            } else if (map_terrain_is(new_offset, TERRAIN_CANAL)) {
                if (!map_canal_at(new_offset)) {
                    if (next_offset == -1) {
                        next_offset = new_offset;
                    } else {
                        g_water_supply_queue.items[g_water_supply_queue.tail++] = new_offset;
                        if (g_water_supply_queue.tail >= MAX_QUEUE)
                            g_water_supply_queue.tail = 0;
                    }
                }
            }
        }
        if (next_offset == -1) {
            if (g_water_supply_queue.head == g_water_supply_queue.tail) {
                return;
            }

            next_offset = g_water_supply_queue.items[g_water_supply_queue.head++];
            if (g_water_supply_queue.head >= MAX_QUEUE) {
                g_water_supply_queue.head = 0;
            }
        }
        grid_offset = next_offset;
    } while (next_offset > -1);
}


void map_update_canals_from_river() {
    for (int i = 0; i < river_access_canal_offsets_total; ++i) {
        int grid_offset = river_access_canal_offsets[i];
        map_canal_fill_from_offset(grid_offset);
    }
}

void map_update_canals() {
    OZZY_PROFILER_SECTION("Game/Update/Canals");
    // first, reset all canals
    map_terrain_remove_all(TERRAIN_IRRIGATION_RANGE);
    canals_empty_all();

    // fill canals!
    map_update_canals_from_river();
}