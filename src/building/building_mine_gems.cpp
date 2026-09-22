#include "building_mine_gems.h"

#include "building/building.h"
#include "grid/gems.h"
#include "grid/grid.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_mine_gems);

void building_mine_gems::update_production() {
    auto &d = runtime_data();
    int current_progress = d.progress;

    tile2i best_tile = tile2i::invalid;
    int best_resource = 0;

    grid_area search_area = map_grid_get_area(base.tile, base.size, 0);
    map_grid_area_foreach(search_area, [&] (tile2i t) {
        int resource = map_get_gems(t);
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
        map_gems_deplete(best_tile, delta_progress);
    }
}
