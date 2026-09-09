#include "building_artisans_guild.h"

#include "building/monuments.h"
#include "city/city.h"
#include "core/random.h"
#include "figure/figure.h"
#include "figuretype/figure_tomb_artisan.h" // ACTION_10_TOMB_ARTISAN_CREATED
#include "game/resource.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_artisans_guild);

void building_artisans_guild::on_create(int orientation) {
    building_guild::on_create(orientation);
    // Same as bricklayers: walker cap from JS static_params.max_workers.
    runtime_data().max_workers = current_params().max_workers;
    if (runtime_data().max_workers < 1) {
        runtime_data().max_workers = 1;
    }
}

bool building_artisans_guild::has_paint_and_clay() const {
    return stored_amount(RESOURCE_PAINT) >= 100 && stored_amount(RESOURCE_CLAY) >= 100;
}

bool building_artisans_guild::can_spawn_tomb_artisan() {
    if (get_figures_number(FIGURE_TOMB_ARTISAN) >= runtime_data().max_workers) {
        return false;
    }

    building *monument = buildings_valid_first([&](building &b) {
        if (!b.is_main() || !b.is_monument()) {
            return false;
        }

        auto *m = b.dcast_monument();
        if (!m || !m->is_unfinished()) {
            return false;
        }

        return m->need_artisan();
    });

    return monument != nullptr;
}

void building_artisans_guild::spawn_figure() {
    check_labor_problem();
    if (!base.has_road_access) {
        return;
    }

    common_spawn_labor_seeker(current_params().min_houses_coverage);
    if (base.worker_percentage() < 50) {
        return;
    }

    if (!has_paint_and_clay()) {
        return;
    }

    int spawn_delay = figure_spawn_timer();
    if (spawn_delay == -1) {
        return;
    }

    base.figure_spawn_delay++;
    if (base.figure_spawn_delay < spawn_delay) {
        return;
    }

    base.figure_spawn_delay = 0;
    if (!can_spawn_tomb_artisan()) {
        return;
    }

    building *monument = buildings_valid_first([&](building &b) {
        if (!b.is_main() || !b.is_monument()) {
            return false;
        }

        auto *m = b.dcast_monument();
        if (!m || !m->is_unfinished()) {
            return false;
        }

        return m->need_artisan();
    });

    if (!monument) {
        return;
    }

    auto *f = create_figure_with_destination(FIGURE_TOMB_ARTISAN, monument,
                                                 (e_figure_action)ACTION_10_TOMB_ARTISAN_CREATED, BUILDING_SLOT_SERVICE);
    if (!f || !f->id) {
        return;
    }

    // Artisan carries a load of paint+clay from the guild to the tomb.
    consume_resource(RESOURCE_PAINT, 100);
    consume_resource(RESOURCE_CLAY, 100);

    // Set destination_tile before figures.update(): TERRAIN_USAGE_ROADS poofs walkers
    // that are off-road with an empty destination_tile (action_perform runs that check
    // before figure_action, so ACTION_10 would be too late).
    auto *mm = monument->dcast_monument();
    f->destination_tile = mm ? mm->access_point() : monument->access_tile();
    f->terrain_usage = TERRAIN_USAGE_PREFER_ROADS;

    // Before first figure_action — if the walker poofs before ACTION_10, on_destroy
    // still clears the monument worker slot filled below.
    if (auto *impl = f->dcast()) {
        static_cast<figure_tomb_artisan *>(impl)->runtime_data().destination_bid = monument->id;
    }

    monument->dcast()->add_workers(f->id);
    f->wait_ticks = random_short() % 30;
}
