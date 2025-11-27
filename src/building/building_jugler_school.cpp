#include "building_jugler_school.h"

#include "building/building_dance_school.h"
#include "figuretype/figure_entertainer.h"
#include "city/city_labor.h"
#include "widget/city/ornaments.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_juggler_school);

void building_juggler_school::update_day() {
    building_impl::update_day();

    auto &d = runtime_data();
    if (d.spawned_entertainer_days > 0) {
        d.spawned_entertainer_days--;
    }
}

void building_juggler_school::update_graphic() {
    const xstring &animkey = can_play_animation() ? animkeys().work : animkeys().none;
    set_animation(animkey);

    building_impl::update_graphic();
}

void building_juggler_school::spawn_figure() {
    if (!common_spawn_figure_trigger(current_params().min_houses_coverage, BUILDING_SLOT_JUGGLER)) {
        return;
    }

    auto &d = runtime_data();
    if (d.spawned_entertainer_days > 0) {
        return;
    }

    int pct_workers = worker_percentage();
    int spawn_interval_days;
    
    const auto &params = current_params();
    if (pct_workers >= 100) {
        spawn_interval_days = params.spawn_delay_100_percent;
    } else if (pct_workers >= 75) {
        spawn_interval_days = params.spawn_delay_75_percent;
    } else if (pct_workers >= 50) {
        spawn_interval_days = params.spawn_delay_50_percent;
    } else if (pct_workers >= 25) {
        spawn_interval_days = params.spawn_delay_25_percent;
    } else if (pct_workers >= 1) {
        spawn_interval_days = params.spawn_delay_default;
    } else {
        return;
    }

    int venue_destination = figure_entertainer::determine_venue_destination(base.road_access, FIGURE_JUGGLER, {BUILDING_PAVILLION, BUILDING_BANDSTAND, BUILDING_BOOTH});

    building* dest = building_get(venue_destination);
    if (dest->id > 0) {
        create_figure_with_destination(FIGURE_JUGGLER, dest, (e_figure_action)ACTION_92_ENTERTAINER_GOING_TO_VENUE, BUILDING_SLOT_JUGGLER);
        d.spawned_entertainer_days = spawn_interval_days;
    } else {
        create_roaming_figure(FIGURE_JUGGLER, (e_figure_action)ACTION_90_ENTERTAINER_AT_SCHOOL_CREATED, BUILDING_SLOT_JUGGLER);
        d.spawned_entertainer_days = spawn_interval_days;
    }
}

bool building_juggler_school::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    return true;
}