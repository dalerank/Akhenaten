#include "building_firehouse.h"

#include "building/destruction.h"
#include "city/city_buildings.h"
#include "figuretype/figure_fireman.h"
#include "dev/debug.h"
#include "graphics/animation.h"
#include "widget/city/ornaments.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_firehouse);

declare_console_command_p(fire_no) {
    buildings_valid_do([&] (building &b) {
        b.fire_risk = 0;
    });
}

declare_console_command_p(fire_start) {
    std::string args;
    is >> args;
    int count = atoi(!args.empty() ? args.c_str() : "1");

    svector<building *, 1000> buildings;
    buildings_valid_do([&] (building &b) {
        buildings.push_back(&b);
    });

    for (int i = 0; i < count; i++) {
        building *b = buildings.at(rand() % buildings.size());
        b->main()->destroy_by_fire();
    }
}

void building_firehouse::spawn_figure() {
    base.common_spawn_roamer(FIGURE_FIREMAN, current_params().min_houses_coverage, (e_figure_action)ACTION_70_FIREMAN_CREATED);
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
