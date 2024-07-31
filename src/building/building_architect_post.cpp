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

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_architect_post);
void config_load_building_architect_post() {
    architect_post_m.load();
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

void building_architect_post::window_info_background(object_info &c) {
    building *b = building_get(c.building_id);
    const auto &params = b->dcast()->params();

    c.help_id = params.meta.help_id;
    int group_id = params.meta.text_id;

    window_building_play_sound(&c, snd::get_building_info_sound(type()));
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(group_id, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);

    if (!c.has_road_access) {
        window_building_draw_description(c, 69, 25);
    } else if (!b->num_workers) {
        window_building_draw_description(c, group_id, 9);
    } else {
        if (b->has_figure(0)) {
            window_building_draw_description(c, group_id, 2);
        } else {
            window_building_draw_description(c, group_id, 3);
        }

        if (c.worker_percentage >= 100) {
            window_building_draw_description_at(c, 72, group_id, 4);
        } else if (c.worker_percentage >= 75) {
            window_building_draw_description_at(c, 72, group_id, 5);
        } else if (c.worker_percentage >= 50) {
            window_building_draw_description_at(c, 72, group_id, 6);
        } else if (c.worker_percentage >= 25) {
            window_building_draw_description_at(c, 72, group_id, 7);
        } else {
            window_building_draw_description_at(c, 72, group_id, 8);
        }
    }

    inner_panel_draw(c.offset.x + 16, c.offset.y + 136, c.bgsize.x - 2, 4);
    window_building_draw_employment(&c, 142);
}

void building_architect_post::spawn_figure() {
    common_spawn_roamer(FIGURE_ARCHITECT, 50, FIGURE_ACTION_60_ENGINEER_CREATED);
}

bool building_architect_post::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    const animation_t &anim = architect_post_m.anim["work"];
    building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);

    return true;
}