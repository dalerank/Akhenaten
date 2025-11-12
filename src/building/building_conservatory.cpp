#include "building/building_conservatory.h"

#include "building/building_dance_school.h"
#include "figuretype/figure_entertainer.h"
#include "widget/city/ornaments.h"
#include "city/city_labor.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_conservatory);

void building_conservatory::spawn_figure() {
    if (!common_spawn_figure_trigger(50)) {
        return;
    }

    int dest_id = figure_entertainer::determine_venue_destination(base.road_access, FIGURE_MUSICIAN, {BUILDING_PAVILLION, BUILDING_BANDSTAND});
    building* dest = building_get(dest_id);
    if (dest->id > 0) {
        create_figure_with_destination(FIGURE_MUSICIAN, dest, (e_figure_action)ACTION_92_ENTERTAINER_GOING_TO_VENUE);
    } else {
        common_spawn_roamer(FIGURE_MUSICIAN, current_params().min_houses_coverage, (e_figure_action)ACTION_90_ENTERTAINER_AT_SCHOOL_CREATED);
    }
}

void building_conservatory::update_graphic() {
    const bool can_teach_dancers = worker_percentage() > 50;
    const xstring &animkey = (can_teach_dancers && can_play_animation())
                                ? animkeys().work
                                : animkeys().none;

    set_animation(animkey);

    building_impl::update_graphic();
}

bool building_conservatory::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);
    return true;
}