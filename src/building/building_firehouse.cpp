#include "building_firehouse.h"

#include "building/destruction.h"
#include "city/city_buildings.h"

#include "dev/debug.h"
#include "graphics/animation.h"
#include "widget/city/ornaments.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_firehouse);

declare_console_command_p(nofire) {
    buildings_valid_do([&] (building &b) {
        b.fire_risk = 0;
    });
}

declare_console_command_p(startfire) {
    std::string args;
    is >> args;
    int count = atoi(!args.empty() ? args.c_str() : "10");

    svector<building *, 1000> buildings;
    buildings_valid_do([&] (building &b) {
        buildings.push_back(&b);
    });

    int step = std::max<int>(1, (int)buildings.size() / count);
    for (int i = 0; i < buildings.size(); i += step) {
        buildings[i]->main()->destroy_by_fire();
    }
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
