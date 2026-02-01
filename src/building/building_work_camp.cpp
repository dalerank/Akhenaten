#include "building/building_work_camp.h"

#include "building/monuments.h"
#include "city/object_info.h"
#include "city/city_floods.h"
#include "city/city_buildings.h"
#include "figure/figure.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "figuretype/figure_worker.h"
#include "building/building_farm.h"
#include "graphics/graphics.h"
#include "io/gamefiles/lang.h"
#include "game/game_config.h"
#include "sound/sound_building.h"
#include "building/monuments.h"
#include "widget/city/ornaments.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_work_camp);

building* building_work_camp::determine_worker_needed() {
    building *result = nullptr;
    float mindist_sq = 9999.f;

    const bool floodplain = g_floods.state_is(FLOOD_STATE_FARMABLE);
    buildings_valid_do([&] (building &b) {
        const float curdist_sq = b.tile.dist_sq(this->tile());

        if (curdist_sq >= mindist_sq) {
            return;
        }

        auto farm = b.dcast_farm();
        if (floodplain && farm && farm->is_floodplain_farm()) {
            if (farm->has_road_access() && farm->requested_workers()) {
                mindist_sq = curdist_sq;
                result = &farm->base;
                return;
            }
        }

        auto monument = b.dcast_monument();
        if (monument && monument->phase() < 2 && monument->need_workers()) {
            mindist_sq = curdist_sq;
            result = &monument->base;
            return;
        }
    });

    return result;
}

void building_work_camp::spawn_figure() {
    if (!common_spawn_figure_trigger(current_params().min_houses_coverage)) {
        return;
    }

    if (!!game_features::gameplay_change_work_camp_one_worker_per_month 
        && base.spawned_worker_this_month) {
        return;
    }

    building* dest = determine_worker_needed();
    if (!dest) {
        return;
    }

    figure *f = base.create_figure_with_destination(FIGURE_LABORER, dest, (e_figure_action)ACTION_9_WORKER_CREATED, BUILDING_SLOT_SERVICE);
    base.spawned_worker_this_month = true;

    dest->dcast()->add_workers(f->id);
}

bool building_work_camp::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    building_impl::draw_ornaments_and_animations_height(ctx, point, tile, color_mask);

    return true;
}

void building_work_camp::update_graphic() {
    set_animation(can_play_animation() ? animkeys().work : animkeys().none);

    building_impl::update_graphic();
}

void building_work_camp::update_month() {
    base.spawned_worker_this_month = false;
}
