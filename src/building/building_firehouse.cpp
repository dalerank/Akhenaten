#include "building_firehouse.h"

#include "window/building/common.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"

#include "dev/debug.h"
#include "graphics/animation.h"
#include "city/labor.h"
#include "widget/city/ornaments.h"

buildings::model_t<building_firehouse> firehouse_m;
info_window_firehouse firehouse_infow;

declare_console_command_p(nofire, console_command_nofire);
void console_command_nofire(std::istream &, std::ostream &) {
    buildings_valid_do([&] (building &b) {
        b.fire_risk = 0;
    });
}

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_firehouse);
void config_load_building_firehouse() {
    firehouse_m.load();
    firehouse_infow.load("building_info_window");
}

void building_firehouse::spawn_figure() {
    base.common_spawn_roamer(FIGURE_FIREMAN, 50, FIGURE_ACTION_70_FIREMAN_CREATED);
}

void building_firehouse::update_graphic() {
    const xstring &animkey = can_play_animation()
                                ? animkeys().work
                                : animkeys().none;
    set_animation(animkey);
}

bool building_firehouse::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    return true;
}

void info_window_firehouse::window_info_background(object_info& c) {
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

inline bool info_window_firehouse::check(object_info& c) {
    return building_get(c.building_id)->dcast_firehouse();
}
