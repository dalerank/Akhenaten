#include "building_reed_gatherer.h"

#include "grid/terrain.h"
#include "grid/routing/routing.h"
#include "figure/figure.h"
#include "figuretype/figure_reed_gatherer.h"
#include "core/random.h"
#include "game/game_events.h"
#include "city/city_resource.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_reed_gatherer);

void building_reed_gatherer::on_create(int orientation) {
    building_industry::on_create(orientation);
    runtime_data().max_gatheres = current_params().max_gatherers;
}

bool building_reed_gatherer::can_spawn_gatherer(int max_gatherers_per_building, int carry_per_person) {
    int gatherers_this_yard = get_figures_number(FIGURE_REED_GATHERER);
    int max_storage = current_params().max_storage_amount;
    int max_loads = max_storage / carry_per_person;
    int stored_loads = base.stored_amount(base.output.resource) / carry_per_person;

    if (gatherers_this_yard >= max_gatherers_per_building || gatherers_this_yard + stored_loads >= max_loads) {
        return false;
    }

    return map_routing_citizen_found_terrain(base.road_access, nullptr, TERRAIN_MARSHLAND);
}

void building_reed_gatherer::spawn_figure() {
    check_labor_problem();
    if (!has_road_access()) {
        return;
    }

    common_spawn_labor_seeker(current_params().min_houses_coverage);
    int spawn_delay = figure_spawn_timer();
    if (spawn_delay == -1) {
        return;
    }

    base.figure_spawn_delay++;
    if (base.figure_spawn_delay > spawn_delay) {
        base.figure_spawn_delay = 0;

        if (can_spawn_gatherer(runtime_data().max_gatheres, 50)) {
            auto f = create_figure_generic(FIGURE_REED_GATHERER, ACTION_8_REED_GATHERER_RECALCULATE, BUILDING_SLOT_SERVICE, DIR_4_BOTTOM_LEFT);
            random_generate_next();
            f->wait_ticks = random_short() % 30; // ok
            return;
        }
    }

    common_spawn_goods_output_cartpusher();
}
