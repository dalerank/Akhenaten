#include "building_reed_gatherer.h"

#include "grid/terrain.h"
#include "grid/routing/routing.h"
#include "figure/figure.h"
#include "core/random.h"
#include "game/game_events.h"
#include "city/city_resource.h"

building_reed_gatherer::static_params building_reed_gatherer_m;

void building_reed_gatherer::on_create(int orientation) {
    runtime_data().max_gatheres = 1;
}

bool building_reed_gatherer::can_spawn_gatherer(int max_gatherers_per_building, int carry_per_person) {
    bool resource_reachable = false;
    resource_reachable = map_routing_citizen_found_terrain(base.road_access, nullptr, TERRAIN_MARSHLAND);

    if (!resource_reachable) {
        return false;
    }

    int gatherers_this_yard = base.get_figures_number(FIGURE_REED_GATHERER);

    // can only spawn if there's space for more reed in the building
    int max_loads = 500 / carry_per_person;
    if (gatherers_this_yard < max_gatherers_per_building
        && gatherers_this_yard + (base.stored_amount() / carry_per_person) < (max_loads - gatherers_this_yard)) {
        return true;
    }

    return false;
}

bool building_reed_gatherer::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    return true;
}

void building_reed_gatherer::spawn_figure() {
    check_labor_problem();
    if (!has_road_access()) {
        return;
    }

    common_spawn_labor_seeker(params().min_houses_coverage);
    int spawn_delay = figure_spawn_timer();
    if (spawn_delay == -1) {
        return;
    }

    base.figure_spawn_delay++;
    if (base.figure_spawn_delay > spawn_delay) {
        base.figure_spawn_delay = 0;

        if (can_spawn_gatherer(runtime_data().max_gatheres, 50)) {
            auto f = create_figure_generic(FIGURE_REED_GATHERER, ACTION_8_RECALCULATE, BUILDING_SLOT_SERVICE, DIR_4_BOTTOM_LEFT);
            random_generate_next();
            f->wait_ticks = random_short() % 30; // ok
            return;
        }
    }

    figure* fcart = base.common_spawn_goods_output_cartpusher();
    if (fcart) {
        events::emit(event_produced_resources{ base.output.resource, fcart->get_carrying_amount() });
    }
}
