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

    building_impl::update_graphic();
}

bool building_firehouse::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    return true;
}

void info_window_firehouse::window_info_background(object_info& c) {
    building_info_window::common_info_background(c);
}

inline bool info_window_firehouse::check(object_info& c) {
    return c.building_get()->dcast_firehouse();
}
