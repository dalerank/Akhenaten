/**
 * @file building_architect_post.cpp
 * @brief Implementation of the architect post building functionality
 * 
 * This file contains the implementation for the architect post building,
 * which is responsible for spawning architect figures and managing
 * building-related console commands for debugging purposes.
 */

#include "building_architect_post.h"

#include "building/building.h"
#include "core/svector.h"
#include "building/destruction.h"
#include "city/object_info.h"
#include "city/city_labor.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "io/gamefiles/lang.h"
#include "game/game_config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "widget/city/ornaments.h"
#include "dev/debug.h"
#include "js/js_game.h"
#include <iostream>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_architect_post);

// Global instance of the architect post info window
// Options reading from config "info_window_architect_post"
info_window_architect_post architect_post_infow;

// Console command to remove damage risk from all buildings
declare_console_command_p(nodamage) {
    buildings_valid_do([&] (building &b) {
        b.damage_risk = 0;
    });
}

// Console command to collapse a specified number of buildings (default 10)
// Excludes farms from collapse
declare_console_command_p(collapse) {
    std::string args;
    is >> args;
    int count = atoi(!args.empty() ? args.c_str() : "10");

    svector<building *, 1000> buildings;
    buildings_valid_do([&] (building &b) {
        if (!b.dcast_farm()) {
            buildings.push_back(&b);
        }
    });

    int step = std::max<int>(1, (int)buildings.size() / count);
    for (int i = 0; i < buildings.size(); i += step) {
        buildings[i]->destroy_by_collapse();
    }
}

void building_architect_post::spawn_figure() {
    common_spawn_roamer(FIGURE_ARCHITECT, current_params().min_houses_coverage, FIGURE_ACTION_60_ENGINEER_CREATED);
}

void building_architect_post::update_graphic() {
    const xstring& animkey = can_play_animation()
        ? animkeys().work
        : animkeys().none;
    set_animation(animkey);
    building_impl::update_graphic();
}

bool building_architect_post::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    return true;
}