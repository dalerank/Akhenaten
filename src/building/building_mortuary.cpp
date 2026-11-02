#include "building_mortuary.h"
BUILDING_RUNTIME_DATA_IMPL(building_mortuary)


#include "building/building_house.h"
#include "city/object_info.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "io/gamefiles/lang.h"
#include "game/game_config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "city/city.h"
#include "city/city_resource.h"
#include "dev/debug.h"
#include "js/js_game.h"
#include <iostream>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_mortuary);

void building_mortuary::update_count() const {
    g_city.health.add_mortuary_workers(num_workers());
}

void building_mortuary::update_month() {
    building_impl::update_month();

    auto &data = runtime_data();

    // Update statistics
    if (data.residents_served_this_month > 0) {
        data.months_active++;
    }
    data.total_residents_served += data.residents_served_this_month;
    data.residents_served_this_year += data.residents_served_this_month;

    // Reset monthly counter
    data.residents_served_this_month = 0;

    if (game_features::gameplay_change_mortuary_linen_upkeep.to_bool() && num_workers() > 0 && has_road_access()) {
        const auto &params = current_params();
        if (params.monthly_linen_consumption > 0) {
            int pct_workers = worker_percentage();
            int consumption = calc_adjust_with_percentage<int>(params.monthly_linen_consumption, pct_workers);

            int available = base.stored_amount(RESOURCE_LINEN);
            int to_consume = std::min<int>(available, consumption);
            consume_resource(RESOURCE_LINEN, to_consume);
        }
    }
}

void building_mortuary::update_year() {
    building_impl::update_year();
    runtime_data().residents_served_this_year = 0;
}