#include "vegetation.h"

#include "figure.h"
#include "grid.h"
#include "grid/routing/routing.h"
#include "city/city_figures.h"
#include "game/game_config.h"
#include "io/io_buffer.h"
#include "terrain.h"
#include "tiles.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "core/random.h"
#include "figure/figure.h"
#include "game/resource.h"
#include "grid/routing/queue.h"
#include "js/js_game.h"

tile_cache marshland_tiles_cache;
grid_xx g_terrain_vegetation_growth = {0, FS_UINT8};

void foreach_marshland_tile(void (*callback)(int grid_offset)) {
    for (int grid_offset: marshland_tiles_cache)
        callback(grid_offset);
}

int map_get_vegetation_growth(int grid_offset) {
    return map_grid_get(g_terrain_vegetation_growth, grid_offset);
}

void map_vegetation_deplete(int grid_offset) {
    map_grid_set(g_terrain_vegetation_growth, grid_offset, 0);
    map_tiles_update_vegetation(grid_offset);
}

void map_vegetation_deplete(tile2i tile, int delta) {
    int grid_offset = tile.grid_offset();
    int value = map_grid_get(g_terrain_vegetation_growth, grid_offset);
    map_grid_set(g_terrain_vegetation_growth, grid_offset, std::max(0, value - delta));
    map_tiles_update_vegetation(grid_offset);
}

void vegetation_tile_update(int grid_offset, vegetation_opt opt) {
    int growth = g_terrain_vegetation_growth.get(grid_offset);
    if (opt.random_max == 0) {
        return;
    }

    if (growth < 255) {
        random_generate_next();
        int r = random_short() % opt.random_max + opt.random_min;
        growth = std::clamp(growth + r, 0, 255);

        map_grid_set(g_terrain_vegetation_growth, grid_offset, growth);
        if (growth == 255) {
            map_tiles_update_vegetation(grid_offset);
        }
    }
}

void map_vegetation_growth_update() {
    OZZY_PROFILER_FUNCTION();
    const auto &opt = g_scenario.env.marshland_grow;
    for (int tile_offset : marshland_tiles_cache) {
        vegetation_tile_update(tile_offset, opt);
    }
}

io_buffer* iob_vegetation_growth = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &g_terrain_vegetation_growth);
});

int gatherers_harvesting_point(int grid_offset) {
    // check if there's any figure already gathering at the spot
    int figure_id = map_figure_id_get(grid_offset);
    int gatherers_present = 0;
    while (figure_id) {
        figure* f = figure_get(figure_id);
        if (f->action_state == 10) { // someone is already gathering at this spot!
            gatherers_present++;
        }

        figure_id = f->next_figure;
    }
    return gatherers_present;
}

bool can_harvest_point(int grid_offset, int max_gatherers) {
    // check if harvestable
    if (map_get_vegetation_growth(grid_offset) != 255) {
        return false;
    }

    // check if there's any figure already gathering at the spot
    if (!game_features::gameplay_change_multiple_gatherers) {
        if (gatherers_harvesting_point(grid_offset) >= max_gatherers)
            return false;
    }

    return true;
}