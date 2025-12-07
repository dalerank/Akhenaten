#include "building_mine_copper.h"

#include "building/building.h"
#include "construction/build_planner.h"
#include "game/game_config.h"
#include "city/city_finance.h"
#include "game/game_events.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_mine_copper);

bool building_mine_copper::preview::is_need_flag(build_planner &planer, e_building_flags flag) const {
    const auto &params = building_static_params::get(planer.build_type);
    switch (flag) {
    case e_building_flag::Ore:
        return !game_features::gameplay_copper_mine_can_build_near_mountains && params.needs.ore;
    }

    return building_planer_renderer::is_need_flag(planer, flag);
}

void building_mine_copper::on_before_collapse() {
    building_mine::on_before_collapse();

    if (!!game_features::gameplay_change_random_mine_or_pit_collapses_take_money) {
        events::emit(event_finance_request{ efinance_request_disasters, 250 });
    }
}

