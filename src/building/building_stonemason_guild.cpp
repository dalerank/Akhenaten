#include "building_stonemason_guild.h"

#include "building/building_statue.h"
#include "building/monuments.h"
#include "figuretype/figure_stonemason.h"
#include "city/city.h"
#include "city/city_labor.h"
#include "core/calc.h"
#include "figure/figure.h"
#include "core/random.h"
#include "game/game_config.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "widget/city/ornaments.h"
#include "game/game.h"
#include "dev/debug.h"
#include "js/js_game.h"
#include <iostream>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_stonemason_guild);

declare_console_command(addstone, game_cheat_add_resource<RESOURCE_STONE>);
declare_console_command(addlimestone, game_cheat_add_resource<RESOURCE_LIMESTONE>);
declare_console_command(addgranite, game_cheat_add_resource<RESOURCE_GRANITE>);
declare_console_command(addsandstone, game_cheat_add_resource<RESOURCE_SANDSTONE>);

void building_stonemason_guild::update_graphic() {
    const xstring &animkey = can_play_animation() ? animkeys().work : animkeys().none;
    set_animation(animkey);

    building_impl::update_graphic();
}

void building_stonemason_guild::on_create(int orientation) {
    runtime_data().max_workers = 1;
}

bool building_stonemason_guild::can_spawn_stonemason_man(int max_gatherers_per_building) {
   bool has_free_man = (base.get_figures_number(FIGURE_STONEMASON) < runtime_data().max_workers);
   if (!has_free_man) {
       return false;
   }

   return true;
}

void building_stonemason_guild::spawn_figure() {
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
    if (!can_spawn_stonemason_man(runtime_data().max_workers)) {
        return;
    }

    building* monument = buildings_valid_first([&] (building &b) {
        if (!b.is_main()) {
            return false;
        }

        if (!b.is_monument()) {
            return false;
        }

        auto monument = b.dcast_monument();
        if (!monument->is_unfinished()) {
            return false;
        }

        return monument->need_stonemason();
    });

    if (monument) {
        auto f = base.create_figure_with_destination(FIGURE_STONEMASON, monument, (e_figure_action)FIGURE_ACTION_10_MASON_CREATED, BUILDING_SLOT_SERVICE);
        monument->dcast()->add_workers(f->id);
        f->wait_ticks = random_short() % 30; // ok
        return;
    }

    // If no monument is found, create a stonemason figure with a statue destination
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
        auto f = base.create_figure_with_destination(FIGURE_STONEMASON, &min_service_statue->base, (e_figure_action)FIGURE_ACTION_30_MASON_CREATED_ROAMING, BUILDING_SLOT_SERVICE);
        min_service_statue->add_workers(f->id);
        f->wait_ticks = random_short() % 30;
        auto mason = smart_cast<figure_stonemason>(f);
        if (mason) {
            mason->runtime_data().destination_bid = min_service_statue->id();
        }
        return;
    }
}

bool building_stonemason_guild::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    building_impl::draw_ornaments_and_animations_height(ctx, point, tile, color_mask);

    return true;
}
