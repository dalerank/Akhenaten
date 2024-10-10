#include "building_jugler_school.h"

#include "building/building_dance_school.h"
#include "figuretype/figure_entertainer.h"
#include "city/labor.h"
#include "widget/city/ornaments.h"
#include "building/count.h"
#include "graphics/graphics.h"
#include "graphics/image.h"

#include "js/js_game.h"

buildings::model_t<building_juggler_school> juggler_school_m;

void building_juggler_school::update_month() {
    data.entertainment.spawned_entertainer_this_month = false;
}

void building_juggler_school::update_graphic() {
    const xstring &animkey = can_play_animation() ? animkeys().work : animkeys().none;
    set_animation(animkey);

    building_impl::update_graphic();
}

void building_juggler_school::spawn_figure() {
    if (!common_spawn_figure_trigger(50)) {
        return;
    }

    if (data.entertainment.spawned_entertainer_this_month) {
        return;
    }

    int venue_destination = figure_entertainer::determine_venue_destination(base.road_access, FIGURE_JUGGLER, {BUILDING_PAVILLION, BUILDING_BANDSTAND, BUILDING_BOOTH});

    building* dest = building_get(venue_destination);
    if (dest->id > 0) {
        create_figure_with_destination(FIGURE_JUGGLER, dest, FIGURE_ACTION_92_ENTERTAINER_GOING_TO_VENUE);
        data.entertainment.spawned_entertainer_this_month = true;
    } else {
        common_spawn_roamer(FIGURE_JUGGLER, 50, FIGURE_ACTION_90_ENTERTAINER_AT_SCHOOL_CREATED);
    }
}

bool building_juggler_school::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    return true;
}