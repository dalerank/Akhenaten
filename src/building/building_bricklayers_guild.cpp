#include "building_bricklayers_guild.h"

#include "building/building_statue.h"
#include "building/monument_pyramid_engine.h"
#include "building/monuments.h"
#include "city/city.h"
#include "core/random.h"
#include "dev/debug.h"
#include "figuretype/figure_bricklayer.h"
#include "game/game.h"
#include "game/resource.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_bricklayers_guild);

declare_console_command(add_bricks, game_cheat_add_resource<RESOURCE_BRICKS>);

building *building_bricklayers_guild::find_statue_task() {
    int min_service_value = 9999;
    building *best = nullptr;
    buildings_valid_do([&](building &b) {
        auto *statue = b.dcast_statue();
        if (!statue) {
            return;
        }
        if (statue->get_figure_id(BUILDING_SLOT_SERVICE) != 0) {
            return;
        }
        const int value = statue->service();
        if (value < min_service_value) {
            min_service_value = value;
            best = &b;
        }
    });
    return best;
}

int building_bricklayers_guild::max_active_bricklayers() const {
    const int pct = worker_percentage();
    if (pct >= 100) {
        return 4;
    }
    if (pct >= 75) {
        return 3;
    }
    if (pct >= 50) {
        return 2;
    }
    return 0;
}

bool building_bricklayers_guild::can_spawn_bricklayer() const {
    return get_figures_number(FIGURE_BRICKLAYER) < max_active_bricklayers();
}

void building_bricklayers_guild::spawn_figure() {
    check_labor_problem();
    if (!base.has_road_access) {
        return;
    }

    common_spawn_labor_seeker(current_params().min_houses_coverage);

    if (!can_spawn_bricklayer()) {
        return;
    }

    // OG bricklayers guild: roam spawn when staffed; figure finds task while roaming.
    // Remake: only spawn when mastaba block work or (feature) statue service exists.
    bool has_mastaba_work = false;
    buildings_valid_do([&](building &b) {
        if (has_mastaba_work || !b.is_main() || !pyramid_engine_is_mastaba(&b)) {
            return;
        }
        auto *mon = b.dcast_monument();
        if (!mon || !mon->is_unfinished() || mon->phase() < 2) {
            return;
        }
        if (!pyramid_main_state_get(b.id)) {
            pyramid_engine_init_mastaba(&b);
            if (mon->phase() >= 2) {
                pyramid_engine_start_block_phase(&b);
            }
        }
        auto *ms = pyramid_main_state_get(b.id);
        if (ms && ms->block_phase_active && ms->remaining_blocks > 0 && mon->has_free_worker_slot()) {
            has_mastaba_work = true;
        }
    });

    building *statue = nullptr;
    if (!has_mastaba_work && building_statue::guild_service_enabled()) {
        statue = find_statue_task();
    }
    if (!has_mastaba_work && !statue) {
        return;
    }

    figure *f = create_roaming_figure(FIGURE_BRICKLAYER, (e_figure_action)ACTION_0_BRICKLAYER_ROAM, BUILDING_SLOT_SERVICE);
    if (!f || !f->id) {
        return;
    }

    f->roam_length = 0;
    f->wait_ticks = 0;
    auto *bricklayer = smart_cast<figure_bricklayer>(f);
    if (!bricklayer) {
        return;
    }

    if (has_mastaba_work) {
        bricklayer->try_find_task();
        return;
    }

    bricklayer->assign_statue_task(statue);
}
