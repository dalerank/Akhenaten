#include "figure_fishing_point.h"

#include "js/js_game.h"
#include "core/random.h"
#include "city/city.h"
#include "dev/debug.h"
#include "grid/terrain.h"

#include <iostream>

static const vec2i FISHPOINT_OFFSETS[] = {{0, 0}, {0, -2}, {-2, 0}, {1, 2}, {2, 0}, {-3, 1}, {4, -3}, {-2, 4}, {0, 0}};
figures::model_t<figure_fishing_point> fishing_point_m;
figures::model_t<figure_fishing_spot> fishing_spot_m;

declare_console_command_p(addfishpoints) {
    std::string args; is >> args;
    int count = atoi(args.empty() ? (pcstr)"0" : args.c_str());

    g_city.fishing_points.update(count);
}

void figure_fishing_point::figure_action() {
    base.terrain_usage = TERRAIN_USAGE_ANY;
    base.use_cross_country = true;
    bool animation_finished = false;
    if (base.anim.frame == 0) {
        base.progress_on_tile++;
        if (base.progress_on_tile > 14) { // wrap around
            base.progress_on_tile = 0;
        }

        data.fishpoint.offset++;
        data.fishpoint.offset %= std::size(FISHPOINT_OFFSETS);
        vec2i offset = FISHPOINT_OFFSETS[data.fishpoint.offset];
        base.set_cross_country_destination(base.source_tile.shifted(offset.x, offset.y));
        animation_finished = true;
    }

    switch (action_state()) {
    case FIGURE_ACTION_196_FISHPOINT_BUBLES:
        if (animation_finished) {
            data.fishpoint.current_step++;
            if (data.fishpoint.current_step > data.fishpoint.max_step) {
                data.fishpoint.current_step = 0;
                advance_action(FIGURE_ACTION_197_FISHPOINT_JUMP);
            }
        }
        break;

    case FIGURE_ACTION_197_FISHPOINT_JUMP:
        if (animation_finished) {
            advance_action(FIGURE_ACTION_196_FISHPOINT_BUBLES);
            data.fishpoint.max_step = 5 + rand() % 10;
        }
        break;
    }
}

void figure_fishing_point::update_animation() {
    xstring animkey = animkeys().bubbles;
    switch (action_state()) {
    case FIGURE_ACTION_196_FISHPOINT_BUBLES:
        animkey = animkeys().bubbles;
        break;

    case FIGURE_ACTION_197_FISHPOINT_JUMP:
        animkey = animkeys().point;
        break;
    }

    image_set_animation(animkey);
}

bool figure_fishing_point::can_move_by_water() const {
    return map_terrain_is(tile(), TERRAIN_DEEPWATER);
}

void figure_fishing_point::main_update_image() {
    base.sprite_image_id = base.anim.start() + base.anim.current_frame();
}

figure *figure_fishing_point::create(tile2i tile) {
    random_generate_next();
    figure* fish = figure_create(FIGURE_FISHING_POINT, tile, DIR_0_TOP_RIGHT);
    fish->anim.frame = random_byte() & 0x1f;
    fish->progress_on_tile = random_byte() & 7;
    fish->advance_action(FIGURE_ACTION_196_FISHPOINT_BUBLES);
    fish->set_cross_country_direction(fish->cc_coords.x, fish->cc_coords.y, 15 * fish->destination_tile.x(), 15 * fish->destination_tile.y(), 0);
    fish->image_set_animation(fishing_point_m.anim["point"]);
    return fish;
}