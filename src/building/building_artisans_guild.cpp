#include "building_artisans_guild.h"

#include "building/monument_royal_tomb.h"
#include "building/monuments.h"
#include "city/city.h"
#include "figure/figure.h"
#include "figuretype/figure_tomb_artisan.h"
#include "game/resource.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_artisans_guild);

building* building_artisans_guild::find_monument_task(e_resource material) {
    // OG find_tomb_artisan_task: clay (the guild's second_input_stock, OG "paint task") is chamber
    // stage 2, paint (loads_stored, OG "lamp task") is stage 3.
    const int stage = (material == RESOURCE_CLAY) ? 2 : (material == RESOURCE_PAINT) ? 3 : -1;
    if (stage < 0) {
        return nullptr;
    }
    if (building_royal_tomb* part = building_royal_tomb::find_work(FIGURE_TOMB_ARTISAN, 0, false, stage)) {
        return &part->base;
    }
    // Not OG: the Enhanced sphinx painting stage also takes artisans.
    return buildings_valid_first([&](building& b) {
        if (!b.is_main() || !b.is_monument()) {
            return false;
        }
        auto *m = b.dcast_monument();
        return m && m->is_unfinished() && m->need_artisan_with(material);
    });
}

int building_artisans_guild::max_active_artisans() const {
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
    if (pct >= 25) {
        return 1;
    }
    return 0;
}

bool building_artisans_guild::can_spawn_tomb_artisan() const {
    return get_figures_number(FIGURE_TOMB_ARTISAN) < max_active_artisans();
}

void building_artisans_guild::update_animation() {
    building_guild::update_animation();
    // OG animation_offset: a workshop-like guild animates only with paint (its first input) in stock.
    base.play_animation = base.play_animation && stored_amount(RESOURCE_PAINT) > 0;
    es(__func__);
}

void building_artisans_guild::spawn_figure() {
    check_labor_problem();
    if (!base.has_road_access) {
        return;
    }

    const auto& params = current_params();
    common_spawn_labor_seeker(params.min_houses_coverage);

    if (!can_spawn_tomb_artisan()) {
        return;
    }
    base.figure_spawn_delay = 0;

    // OG building_artisans_guild_spawn_figure: a clay task first, then a paint task; each trip takes
    // one load of that material. OG spawns an invisible corpse when neither is possible — nothing
    // visible comes of it, so no figure is made here.
    const int load = params.material_load;
    e_resource material = RESOURCE_NONE;
    building* site = nullptr;
    for (e_resource r : {RESOURCE_CLAY, RESOURCE_PAINT}) {
        if (stored_amount(r) < load) {
            continue;
        }
        site = find_monument_task(r);
        if (site) {
            material = r;
            break;
        }
    }
    if (!site) {
        return;
    }

    figure* f = create_figure_generic(FIGURE_TOMB_ARTISAN, (e_figure_action)ACTION_12_TOMB_ARTISAN_ROAM,
      BUILDING_SLOT_SERVICE, DIR_4_BOTTOM_LEFT);
    auto* artisan = smart_cast<figure_tomb_artisan>(f);
    if (!artisan) {
        return;
    }

    f->roam_length = 0;
    f->wait_ticks = 0;
    base.progress = 0;
    if (!artisan->assign_task(site, material)) {
        f->poof();
        return;
    }
    consume_resource(material, (int16_t)load);
}
