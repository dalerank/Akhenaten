#include "building_mine_copper.h"

#include "building/building.h"
#include "js/js_game.h"
#include "grid/copper.h"
#include "grid/grid.h"
#include "game/resource.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_mine_copper);

void building_mine_copper::update_production() {
    auto &d = runtime_data();
    int current_progress = d.progress;

    tile2i best_tile = tile2i::invalid;
    int best_resource = 0;

    grid_area search_area = map_grid_get_area(base.tile, base.size, 0);
    map_grid_area_foreach(search_area, [&] (tile2i t) {
        int resource = map_get_copper(t);
        if (resource > 0 && resource > best_resource) {
            best_tile = t;
            best_resource = resource;
        }
    });

    if (best_resource <= 0) {
        return;
    }

    building_industry::update_production();
    int delta_progress = d.progress - current_progress;

    if (delta_progress > 0) {
        map_copper_deplete(best_tile, delta_progress);
    }
}

void building_mine_copper::spawn_figure() {
    check_labor_problem();
    if (!has_road_access()) {
        return;
    }

    common_spawn_labor_seeker(current_params().min_houses_coverage);

    auto &d = runtime_data();
    if (d.progress >= d.progress_max) {
        production_finished();
    }

    common_spawn_goods_output_cartpusher();
}
