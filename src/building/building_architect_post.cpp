#include "building_architect_post.h"

#include "building/building.h"
#include "core/svector.h"
#include "building/destruction.h"
#include "city/object_info.h"
#include "city/labor.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "widget/city/ornaments.h"
#include "dev/debug.h"

#include <iostream>

declare_console_command_p(nodamage, console_command_nodamage);
declare_console_command_p(collapse, console_command_collapse);

buildings::model_t<building_architect_post> architect_post_m;
info_window_architect_post architect_post_infow;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_architect_post);
void config_load_building_architect_post() {
    architect_post_m.load();
    architect_post_infow.load("building_info_window");
}

void console_command_nodamage(std::istream &, std::ostream &) {
    buildings_valid_do([&] (building &b) {
        b.damage_risk = 0;
    });
}

void console_command_collapse(std::istream &is, std::ostream &) {
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
        building_destroy_by_collapse(buildings[i]);
    }
}

void building_architect_post::spawn_figure() {
    common_spawn_roamer(FIGURE_ARCHITECT, 50, FIGURE_ACTION_60_ENGINEER_CREATED);
}

void building_architect_post::update_graphic() {
    const xstring& animkey = can_play_animation()
        ? animkeys().work
        : animkeys().none;
    set_animation(animkey);
}

bool building_architect_post::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    return true;
}

void info_window_architect_post::window_info_background(object_info &c) {
    building_info_window::window_info_background(c);

    building* b = building_get(c.building_id);

    auto& ui = *c.ui;
    auto params = b->dcast()->params();

    c.help_id = params.meta.help_id;
    int group_id = params.meta.text_id;

    window_building_play_sound(&c, b->get_sound()); // TODO: change to firehouse

    ui["title"] = ui::str(group_id, 0);

    std::pair<int, int> reason = { group_id, 0 };
    std::pair<int, int> workers = { group_id, 8 };
    if (!c.has_road_access) {
        reason = { 69, 25 };
    } else if (!b->num_workers) {
        reason.second = 9;
    } else {
        reason.second = b->has_figure(0) ? 2 : 3;

        if (c.worker_percentage >= 100) workers.second = 4;
        else if (c.worker_percentage >= 75) workers.second = 5;
        else if (c.worker_percentage >= 50) workers.second = 6;
        else if (c.worker_percentage >= 25) workers.second = 7;
    }

    ui["warning_text"] = ui::str(reason.first, reason.second);
    ui["workers_desc"] = ui::str(workers.first, workers.second);

    draw_employment_details_ui(ui, c, b, -1);
}

inline bool info_window_architect_post::check(object_info& c) {
    return building_get(c.building_id)->dcast_architect_post();
}