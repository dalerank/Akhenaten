#include "building_guild_carpenters.h"

#include "dev/debug.h"
#include "game/game.h"
#include "core/random.h"
#include "city/city_resource.h"
#include "building/monument_mastaba.h"
#include "building/building_statue.h"
#include "city/city_buildings.h"
#include "figuretype/figure_carpenter.h"
#include "city/city.h"
#include <iostream>
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_carpenters_guild);
declare_console_command(add_timber, game_cheat_add_resource<RESOURCE_TIMBER>);

void building_carpenters_guild::update_graphic() {
    const xstring &animkey = can_play_animation() ? animkeys().work : animkeys().none;
    set_animation(animkey);

    building_impl::update_graphic();
}

void building_carpenters_guild::on_create(int orientation) {
    runtime_data().max_workers = 1;
}

bool building_carpenters_guild::can_spawn_carpenter(int max_gatherers_per_building) {
    bool has_free_man = (base.get_figures_number(FIGURE_CARPENTER) < runtime_data().max_workers);
    if (!has_free_man) {
        return false;
    }

    return true;
}

void building_carpenters_guild::spawn_figure() {
    base.check_labor_problem();
    if (!base.has_road_access) {
        return;
    }

    base.common_spawn_labor_seeker(current_params().min_houses_coverage);
    int pct_workers = base.worker_percentage();
    if (pct_workers < 50) {
        return;
    }

    int spawn_delay = base.figure_spawn_timer();
    if (spawn_delay == -1) {
        return;
    }

    base.figure_spawn_delay++;
    if (base.figure_spawn_delay < spawn_delay) {
        return;
    }

    base.figure_spawn_delay = 0;
    if (!can_spawn_carpenter(runtime_data().max_workers)) {
        return;
    }

    // Check if TIMBER resource is available (not mothballed)
    if (g_city.resource.is_mothballed(RESOURCE_TIMBER)) {
        return;
    }

    building *monument = buildings_valid_first([&] (building &b) {
        if (!b.is_monument() || !building_monument_is_unfinished(&b)) {
            return false;
        }

        if (!b.is_main()) {
            return false;
        }

        return building_monument_need_carpenter(&b);
    });

    if (monument) {
        auto f = base.create_figure_with_destination(FIGURE_CARPENTER, monument, (e_figure_action)ACTION_10_CARPENTER_CREATED, BUILDING_SLOT_SERVICE);
        monument->dcast()->add_workers(f->id);
        f->wait_ticks = random_short() % 30; // ok
        return;
    }

    // If no monument is found, create a carpenter figure with a statue/garden destination
    int min_service_value = 9999;
    building_impl *min_service_statue = nullptr;
    buildings_valid_do([&] (building &b) {
        const auto statue = b.dcast_statue();
        if (!statue) {
            return;
        }

        const bool has_worker = statue->get_figure_id(BUILDING_SLOT_SERVICE) != 0;
        if (has_worker) {
            return;
        }

        const int value = statue->service();
        if (value < min_service_value) {
            min_service_value = value;
            min_service_statue = statue;
        }
    });

    if (min_service_statue) {
        auto f = base.create_figure_with_destination(FIGURE_CARPENTER, &min_service_statue->base, (e_figure_action)ACTION_30_CARPENTER_CREATED_ROAMING, BUILDING_SLOT_SERVICE);
        min_service_statue->add_workers(f->id);
        f->wait_ticks = random_short() % 30;
        auto carpenter = smart_cast<figure_carpenter>(f);
        if (carpenter) {
            carpenter->runtime_data().destination_bid = min_service_statue->id();
        }
        return;
    }
}

bool building_carpenters_guild::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    building_impl::draw_ornaments_and_animations_height(ctx, point, tile, color_mask);

    return true;
}