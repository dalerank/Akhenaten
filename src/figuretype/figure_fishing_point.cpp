#include "figure_fishing_point.h"

#include "js/js_game.h"
#include "core/random.h"
#include "city/city.h"
#include "dev/debug.h"
#include "grid/terrain.h"

static const vec2i FISHPOINT_OFFSETS[] = {{0, 0}, {0, -2}, {-2, 0}, {1, 2}, {2, 0}, {-3, 1}, {4, -3}, {-2, 4}, {0, 0}};

enum {
    FISHING_SPOT_FRAMES = 24,
    FISHING_SPOT_RANDOM_PAUSE = 100,
    FISHING_SPOT_PAUSE = 25,
    FISHING_SPOT_FRAME_MASK = 0x1F,
};

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_fishing_point);

declare_console_command_p(addfishpoints) {
    int count = args.next_int(0);

    g_city.fishing_points.update_month(count);
}

// OG boats.c figure_fishing_spot_action. Its frame/pause counters drive nothing visible here (the art runs on
// animctx), but every animating tick advances both the LFSR and the crt stream, so they must keep running.
void figure_fishing_point::spot_tick() {
    auto& d = runtime_data();
    if (d.spot_frame < FISHING_SPOT_FRAMES) {
        d.spot_frame++;
        random_generate_next();
        d.spot_wait_ticks = (uint8_t)(anti_scum_random_15bit() % FISHING_SPOT_RANDOM_PAUSE);
    } else {
        d.spot_frame = FISHING_SPOT_FRAMES;
        d.spot_pause_ticks++;
        if (d.spot_pause_ticks >= d.spot_wait_ticks + FISHING_SPOT_PAUSE) {
            d.spot_pause_ticks = 0;
            d.spot_frame = 0;
        }
    }
}

void figure_fishing_point::figure_action() {
    spot_tick();

    base.terrain_usage = TERRAIN_USAGE_ANY;
    base.use_cross_country = true;
    bool animation_finished = false;
    auto &d = runtime_data();
    if (base.animctx.frame == 0) {
        base.progress_on_tile++;
        if (base.progress_on_tile > 14) { // wrap around
            base.progress_on_tile = 0;
        }

        d.offset++;
        d.offset %= std::size(FISHPOINT_OFFSETS);
        vec2i offset = FISHPOINT_OFFSETS[d.offset];
        base.set_cross_country_destination(base.source_tile.shifted(offset.x, offset.y));
        animation_finished = true;
    }

    switch (action_state()) {
    case ACTION_196_FISHPOINT_BUBLES:
        if (animation_finished) {
            d.current_step++;
            if (d.current_step > d.max_step) {
                d.current_step = 0;
                advance_action(ACTION_197_FISHPOINT_JUMP);
            }
        }
        break;

    case ACTION_197_FISHPOINT_JUMP:
        if (animation_finished) {
            advance_action(ACTION_196_FISHPOINT_BUBLES);
            d.max_step = 5 + d.spot_wait_ticks % 10;
        }
        break;
    }
}

void figure_fishing_point::update_animation() {
    xstring animkey = animkeys().bubbles;
    switch (action_state()) {
    case ACTION_196_FISHPOINT_BUBLES:
        animkey = animkeys().bubbles;
        break;

    case ACTION_197_FISHPOINT_JUMP:
        animkey = animkeys().point;
        break;
    }

    image_set_animation(animkey);
}

bool figure_fishing_point::can_move_by_water() const {
    return map_terrain_is(tile(), TERRAIN_DEEPWATER);
}

void figure_fishing_point::main_image_update() {
    base.main_image_id = base.animctx.start_frame() + base.animctx.current_frame();
}

figure *figure_fishing_point::create(tile2i tile) {
    random_generate_next();
    figure* fish = figure_create(FIGURE_FISHING_POINT, tile, DIR_0_TOP_RIGHT);
    const uint8_t spot_frame = (uint8_t)(anti_scum_random_15bit() & FISHING_SPOT_FRAME_MASK);
    if (auto* spot = fish->dcast<figure_fishing_point>()) {
        auto& d = spot->runtime_data();
        d.spot_frame = spot_frame;
        d.spot_wait_ticks = 0;
        d.spot_pause_ticks = 0;
    }
    fish->animctx.frame = random_byte() & 0x1f;
    fish->progress_on_tile = random_byte() & 7;
    fish->advance_action(ACTION_196_FISHPOINT_BUBLES);
    fish->set_cross_country_direction(fish->cc_coords.x, fish->cc_coords.y, 15 * fish->destination_tile.x(), 15 * fish->destination_tile.y(), 0);
    fish->image_set_animation("point");
    return fish;
}