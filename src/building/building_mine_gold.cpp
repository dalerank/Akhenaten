#include "building_mine_gold.h"

#include "building/building.h"
#include "grid/golden.h"
#include "grid/grid.h"
#include "game/game_config.h"
#include "city/city_finance.h"
#include "game/game_events.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_mine_gold);

int building_mine_gold::produce_uptick_per_day() const {
    if (base.num_workers <= 0) {
        return 0;
    }
    
    const auto &params = current_params();
    int divider = std::max<int>(1, params.production_divider);
    
    if (!!game_features::gameplay_change_goldmine_twice_production) {
        divider = std::max(1, divider / 2);
    }
    
    int production = base.num_workers / divider;
    return std::max<int>(1, production);
}

void building_mine_gold::production_finished() {
    const auto &params = current_params();
    if (stored_amount(params.output.resource) >= base.max_storage_amount(params.output.resource)) {
        return;
    }

    auto &d = runtime_data();
    if (d.progress >= d.progress_max) {
        store_resource(RESOURCE_GOLD, ready_production());

        d.progress = 0;
        //d.has_raw_materials = false;
    }
}

void building_mine_gold::update_production() {
    auto &d = runtime_data();
    int current_progress = d.progress;

    tile2i best_tile = tile2i::invalid;
    int best_resource = 0;

    grid_area search_area = map_grid_get_area(base.tile, base.size, 0);
    map_grid_area_foreach(search_area.tmin, search_area.tmax, [&] (tile2i t) {
        int resource = map_get_golden(t);
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
   
    map_golden_deplete(best_tile, delta_progress);
}

void building_mine_gold::on_before_collapse() {
    building_mine::on_before_collapse();

    if (!!game_features::gameplay_change_random_mine_or_pit_collapses_take_money) {
        events::emit(event_finance_request{ efinance_request_disasters, 250 });
    }
}

