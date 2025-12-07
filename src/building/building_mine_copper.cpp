#include "building_mine_copper.h"

#include "building/building.h"
#include "construction/build_planner.h"
#include "game/game_config.h"
#include "city/city_finance.h"
#include "game/game_events.h"
#include "js/js_game.h"
#include "grid/copper.h"
#include "grid/grid.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_mine_copper);

bool building_mine_copper::preview::is_need_flag(build_planner &planer, e_building_flags flag) const {
    const auto &params = building_static_params::get(planer.build_type);
    switch (flag) {
    case e_building_flag::Ore:
        return !game_features::gameplay_copper_mine_can_build_near_mountains && params.needs.ore;
    }

    return building_planer_renderer::is_need_flag(planer, flag);
}

void building_mine_copper::update_production() {
    auto &d = runtime_data();
    int current_progress = d.progress;

    tile2i best_tile = tile2i::invalid;
    int best_resource = 0;

    grid_area search_area = map_grid_get_area(base.tile, base.size, 0);
    map_grid_area_foreach(search_area.tmin, search_area.tmax, [&] (tile2i t) {
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

void building_mine_copper::on_before_collapse() {
    building_mine::on_before_collapse();

    if (!!game_features::gameplay_change_random_mine_or_pit_collapses_take_money) {
        events::emit(event_finance_request{ efinance_request_disasters, 250 });
    }
}

