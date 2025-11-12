#include "building_health.h"

#include "building/building_house.h"
#include "city/object_info.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "figuretype/figure_herbalist.h"
#include "graphics/graphics.h"
#include "io/gamefiles/lang.h"
#include "game/game_config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "widget/city/ornaments.h"
#include "city/city.h"
#include "dev/debug.h"
#include "js/js_game.h"
#include <iostream>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_apothecary);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_mortuary);

declare_console_command_p(plague_start) {
    std::string args; is >> args;
    int plague_people = atoi(args.empty() ? "100" : args.c_str());

    int total_population = 0;
    buildings_house_do([&] (building_house *house) {
        if (house->house_population() <= 0) {
            return;
        }
        total_population += house->house_population();
    });
    g_city.health.start_disease(total_population, true, plague_people);
}

declare_console_command_p(plague_no) {
    buildings_house_do([&] (building_house* house) {
        if (house->house_population() <= 0) {
            return;
        }

        house->base.disease_days = 0;
        house->base.has_plague = false;
        house->base.common_health = 100;
    });
}

void building_apothecary::spawn_figure() {
    common_spawn_roamer(FIGURE_HERBALIST, current_params().min_houses_coverage, (e_figure_action)ACTION_62_HERBALIST_ROAMING);
    //    check_labor_problem();
    //    if (has_figure_of_type(FIGURE_DOCTOR))
    //        return;
    //    map_point road;
    //    if (map_has_road_access(x, y, size, &road)) {
    //        spawn_labor_seeker(50);
    //        int spawn_delay = figure_spawn_timer();
    //        if (spawn_delay == -1)
    //            return;
    //        figure_spawn_delay++;
    //        if (figure_spawn_delay > spawn_delay) {
    //            figure_spawn_delay = 0;
    //            create_roaming_figure(road.x, road.y, FIGURE_DOCTOR);
    //        }
    //    }
}

void building_apothecary::update_graphic() {
    const xstring &animkey = can_play_animation() ? animkeys().work : animkeys().none;
    set_animation(animkey);

    building_impl::update_graphic();
}

bool building_apothecary::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    return true;
}

void building_mortuary::spawn_figure() {
    common_spawn_roamer(FIGURE_EMBALMER, current_params().min_houses_coverage, (e_figure_action)ACTION_125_ROAMER_ROAMING);
}

void building_mortuary::update_graphic() {
    const xstring &animkey = can_play_animation() ? animkeys().work : animkeys().none;
    set_animation(animkey);

    building_impl::update_graphic();
}

bool building_mortuary::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    return false;
}

void building_mortuary::update_count() const {
    g_city.health.add_mortuary_workers(num_workers());
}