#include "building_dance_school.h"
#include "building_dance_school.h"

#include "building/building.h"
#include "city/object_info.h"
#include "city/city_labor.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "game/game_config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "widget/city/ornaments.h"
#include "graphics/animation.h"
#include "figuretype/figure_entertainer.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_dancer_school);

void building_dancer_school::spawn_figure() {
    if (!common_spawn_figure_trigger(50)) {
        return;
    }

    int building_id = figure_entertainer::determine_venue_destination(base.road_access, FIGURE_DANCER, {BUILDING_PAVILLION});
    
    building* dest= building_get(building_id);
    if (dest->id > 0) {
        create_figure_with_destination(FIGURE_DANCER, dest, (e_figure_action)ACTION_92_ENTERTAINER_GOING_TO_VENUE);
    } else {
        common_spawn_roamer(FIGURE_DANCER, current_params().min_houses_coverage, (e_figure_action)ACTION_90_ENTERTAINER_AT_SCHOOL_CREATED);
    }
}

void building_dancer_school::update_graphic() {
    const xstring &animkey = can_play_animation()
                                ? animkeys().work
                                : animkeys().none;

    set_animation(animkey);

    building_impl::update_graphic();
}

bool building_dancer_school::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);
    return true;
}

