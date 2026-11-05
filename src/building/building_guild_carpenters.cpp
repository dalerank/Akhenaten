#include "building_guild_carpenters.h"

#include "building/building_statue.h"
#include "building/monuments.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "core/random.h"
#include "dev/debug.h"
#include "figuretype/figure_carpenter.h"
#include "game/game.h"
#include "js/js_game.h"

#include <algorithm>
#include <initializer_list>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_carpenters_guild);
declare_console_command(add_timber, game_cheat_add_resource<RESOURCE_TIMBER>);

namespace {
constexpr int k_carpenter_progress_ready = 400;
constexpr int k_carpenter_timber_load = 100;

bool monument_needs_carpenter(building &b) {
    if (!b.is_main() || !b.is_monument()) {
        return false;
    }
    auto *monument = b.dcast_monument();
    return monument && monument->is_unfinished() && monument->need_carpenter();
}

building *first_monument_of_types(std::initializer_list<e_building_type> types) {
    for (e_building_type type : types) {
        building *found = buildings_valid_first([&](building &b) {
            return b.type == type && monument_needs_carpenter(b);
        });
        if (found) {
            return found;
        }
    }
    return nullptr;
}
} // namespace

building *building_carpenters_guild::find_monument_task(tile2i /*from*/) {
    // OG monument_find_task_carpenter priority order.
    if (building *b = first_monument_of_types({
            BUILDING_SMALL_PYRAMID,
            BUILDING_MEDIUM_PYRAMID,
            BUILDING_LARGE_PYRAMID,
            BUILDING_PYRAMID_COMPLEX,
            BUILDING_GRAND_PYRAMID_COMPLEX,
            BUILDING_SMALL_STEPPED_PYRAMID,
            BUILDING_MEDIUM_STEPPED_PYRAMID,
            BUILDING_LARGE_STEPPED_PYRAMID,
            BUILDING_STEPPED_PYRAMID_COMPLEX,
            BUILDING_GRAND_STEPPED_PYRAMID_COMPLEX,
            BUILDING_SMALL_BENT_PYRAMID,
            BUILDING_MEDIUM_BENT_PYRAMID,
            BUILDING_SMALL_MUDBRICK_PYRAMID,
            BUILDING_MEDIUM_MUDBRICK_PYRAMID,
            BUILDING_LARGE_MUDBRICK_PYRAMID,
            BUILDING_MUDBRICK_PYRAMID_COMPLEX,
            BUILDING_GRAND_MUDBRICK_PYRAMID_COMPLEX,
            BUILDING_PYRAMID,
        })) {
        return b;
    }

    if (building *b = first_monument_of_types({BUILDING_SPHINX})) {
        return b;
    }
    if (building *b = first_monument_of_types({BUILDING_SMALL_OBELISK, BUILDING_LARGE_OBELISK})) {
        return b;
    }
    if (building *b = first_monument_of_types({BUILDING_CAESAREUM})) {
        return b;
    }
    if (building *b = first_monument_of_types({BUILDING_PHAROS_LIGHTHOUSE})) {
        return b;
    }
    if (building *b = first_monument_of_types({BUILDING_SUN_TEMPLE})) {
        return b;
    }
    if (building *b = first_monument_of_types({BUILDING_ALEXANDRIA_LIBRARY, BUILDING_ALEXANDRIAS_LIBRARY})) {
        return b;
    }
    if (building *b = first_monument_of_types({BUILDING_ABU_SIMBEL})) {
        return b;
    }
    return first_monument_of_types({BUILDING_MAUSOLEUM});
}

building *building_carpenters_guild::find_statue_task() {
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

int building_carpenters_guild::max_active_carpenters() const {
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
    // OG carpenter guild uses one_below_25: any staffing above 0 → 1 walker.
    if (pct >= 1) {
        return 1;
    }
    return 0;
}

bool building_carpenters_guild::can_spawn_carpenter() const {
    return get_figures_number(FIGURE_CARPENTER) < max_active_carpenters();
}

void building_carpenters_guild::update_day() {
    building_impl::update_day();

    if (base.num_workers <= 0) {
        return;
    }

    // OG: progress while staffed and (no input subtype OR any timber stock).
    if (base.input.resource != RESOURCE_NONE && stored_amount(base.input.resource) <= 0) {
        return;
    }

    const int cap = std::max<int>(base.progress_max, k_carpenter_progress_ready) * 2;
    int next = (int)base.progress + base.num_workers;
    if (next > cap) {
        next = cap;
    }
    base.progress = (uint16_t)next;
}

void building_carpenters_guild::spawn_figure() {
    check_labor_problem();
    if (!base.has_road_access) {
        return;
    }

    common_spawn_labor_seeker(current_params().min_houses_coverage);

    if (!can_spawn_carpenter()) {
        return;
    }

    if (base.progress < k_carpenter_progress_ready) {
        return;
    }

    building *monument = find_monument_task(base.road_access);
    building *statue = nullptr;
    if (!monument && building_statue::guild_service_enabled()) {
        statue = find_statue_task();
    }
    if (!monument && !statue) {
        // OG creates a ghost corpse here; remake skips the useless spawn.
        return;
    }

    figure *f = create_roaming_figure(FIGURE_CARPENTER, (e_figure_action)ACTION_0_CARPENTER_ROAM, BUILDING_SLOT_SERVICE);
    if (!f || !f->id) {
        return;
    }

    f->roam_length = 0;
    f->wait_ticks = 0;
    auto *carpenter = smart_cast<figure_carpenter>(f);
    if (!carpenter) {
        return;
    }

    if (monument) {
        base.progress = 0;
        int stock = stored_amount(RESOURCE_TIMBER);
        if (stock >= k_carpenter_timber_load) {
            consume_resource(RESOURCE_TIMBER, k_carpenter_timber_load);
        } else if (stock > 0) {
            consume_resource(RESOURCE_TIMBER, (int16_t)stock);
        }
        carpenter->assign_monument_task(monument);
        return;
    }

    carpenter->assign_statue_task(statue);
}
