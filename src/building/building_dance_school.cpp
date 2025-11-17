#include "building_dance_school.h"
#include "building_dance_school.h"

#include "building/building.h"
#include "building/building_conservatory.h"
#include "city/object_info.h"
#include "city/city_labor.h"
#include "city/city_buildings.h"
#include "game/resource.h"
#include "game/game.h"
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

void building_dancer_school::update_day() {
    building_impl::update_day();
}

void building_dancer_school::on_tick(bool refresh_only) {
    building_impl::on_tick(refresh_only);

    if (!!game_features::gameplay_conservatory_helps_dance_school) {
        auto &d = runtime_data();
        if (d.conservatory_help > 0) {
            d.conservatory_help--;
        }
    }
}

uint8_t building_dancer_school::conservatory_help() const {
    auto &d = runtime_data();
    return d.conservatory_help;
}

void building_dancer_school::spawn_figure() {
    check_labor_problem();
    if (!base.has_road_access) {
        return;
    }

    if (main() == this) {
        common_spawn_labor_seeker(50);
    }

    if (has_figure(BUILDING_SLOT_SERVICE)) {
        return;
    }

    int spawn_delay = figure_spawn_timer();
    if (spawn_delay == -1) {
        return;
    }

    if (!!game_features::gameplay_conservatory_helps_dance_school) {
        if (conservatory_help() > 0 && spawn_delay > 0) {
            int reduction_percent = calc_percentage<int>(30, 100 - conservatory_help());
            spawn_delay = calc_percentage<int>(spawn_delay, reduction_percent);
        }
    }

    base.figure_spawn_delay++;
    if (base.figure_spawn_delay > spawn_delay) {
        base.figure_spawn_delay = 0;

        int building_id = figure_entertainer::determine_venue_destination(base.road_access, FIGURE_DANCER, {BUILDING_PAVILLION});        
        building* dest= building_get(building_id);
        if (dest->id > 0) {
            create_figure_with_destination(FIGURE_DANCER, dest, (e_figure_action)ACTION_92_ENTERTAINER_GOING_TO_VENUE);
        } else {
            common_spawn_roamer(FIGURE_DANCER, current_params().min_houses_coverage, (e_figure_action)ACTION_90_ENTERTAINER_AT_SCHOOL_CREATED);
        }
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

