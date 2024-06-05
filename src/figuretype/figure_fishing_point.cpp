#include "figure_fishing_point.h"

#include "js/js_game.h"
#include "core/random.h"

static const vec2i FISHPOINT_OFFSETS[] = {{0, 0}, {0, -2}, {-2, 0}, {1, 2}, {2, 0}, {-3, 1}, {4, -3}, {-2, 4}, {0, 0}};
figures::model_t<figure_fishing_point> fishing_point_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_fishing_point);
void config_load_figure_fishing_point() {
    fishing_point_m.load();
}

void figure_fishing_point::figure_action() {
    base.terrain_usage = TERRAIN_USAGE_ANY;
    base.is_ghost = false;
    base.use_cross_country = true;
    bool animation_finished = false;
    if (base.anim.frame == 0) {
        base.progress_on_tile++;
        if (base.progress_on_tile > 14) { // wrap around
            base.progress_on_tile = 0;
        }

        base.local_data.fishpoint.offset++;
        base.local_data.fishpoint.offset %= std::size(FISHPOINT_OFFSETS);
        vec2i offset = FISHPOINT_OFFSETS[base.local_data.fishpoint.offset];
        base.set_cross_country_destination(base.source_tile.shifted(offset.x, offset.y));
        animation_finished = true;
    }

    switch (action_state()) {
    case FIGURE_ACTION_196_FISHPOINT_BUBLES:
        if (animation_finished) {
            base.local_data.fishpoint.current_step++;
            if (base.local_data.fishpoint.current_step > base.local_data.fishpoint.max_step) {
                base.local_data.fishpoint.current_step = 0;
                advance_action(FIGURE_ACTION_197_FISHPOINT_JUMP);
            }
        }
        break;

    case FIGURE_ACTION_197_FISHPOINT_JUMP:
        if (animation_finished) {
            advance_action(FIGURE_ACTION_196_FISHPOINT_BUBLES);
            base.local_data.fishpoint.max_step = 5 + rand() % 10;
        }
        break;
    }
}

void figure_fishing_point::update_animation() {
    switch (action_state()) {
    case FIGURE_ACTION_196_FISHPOINT_BUBLES:
        image_set_animation(fishing_point_m.anim["bubbles"]);
        break;

    case FIGURE_ACTION_197_FISHPOINT_JUMP:
        image_set_animation(fishing_point_m.anim["point"]);
        break;
    }
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