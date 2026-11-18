#include "figure_fishing_point.h"

#include "js/js_register.h"
#include "core/random.h"
#include "city/city.h"
#include "dev/debug.h"
#include "game/game_config.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "scenario/scenario.h"

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

bool figure_fishing_point::drift_stays_on_deep_water() {
    const vec2i coords = base.cc_coords;
    const vec2i delta = base.cc_delta;
    const short delta_xy = base.cc_delta_xy;

    bool deep = true;
    for (int guard = 0; guard < 1000; guard++) {
        const tile2i t(base.cc_coords.x / 15, base.cc_coords.y / 15);
        if (!map_grid_is_inside(t, 1) || !map_terrain_is(t, TERRAIN_DEEPWATER)) {
            deep = false;
            break;
        }
        if (base.cc_delta.x + base.cc_delta.y <= 0) {
            break;
        }
        base.cross_country_advance();
    }

    base.cc_coords = coords;
    base.cc_delta = delta;
    base.cc_delta_xy = delta_xy;
    return deep;
}

bool figure_fishing_point::drift_retarget(tile2i dst) {
    if (!dst.valid() || !map_grid_is_inside(dst, 1)) {
        return false;
    }

    const tile2i destination = base.destination_tile;
    const vec2i cc_destination = base.cc_destination;
    const vec2i delta = base.cc_delta;
    const short delta_xy = base.cc_delta_xy;
    const uint8_t cc_direction = base.cc_direction;
    const uint8_t direction = base.direction;

    base.set_cross_country_destination(dst);
    if (drift_stays_on_deep_water()) {
        return true;
    }

    base.destination_tile = destination;
    base.cc_destination = cc_destination;
    base.cc_delta = delta;
    base.cc_delta_xy = delta_xy;
    base.cc_direction = cc_direction;
    base.direction = direction;
    return false;
}

void figure_fishing_point::drift(bool animation_wrapped) {
    if (g_scenario.events.blood_river_sweep_active()) {
        return;
    }

    auto& d = runtime_data();
    const vec2i target = FISHPOINT_OFFSETS[d.offset % std::size(FISHPOINT_OFFSETS)];
    const bool heading
      = base.cc_delta.x + base.cc_delta.y > 0 && base.destination_tile == base.source_tile.shifted(target.x, target.y);
    if (heading && drift_stays_on_deep_water()) {
        base.move_ticks_cross_country(1);
        return;
    }

    if (!animation_wrapped) {
        return;
    }

    base.progress_on_tile++;
    if (base.progress_on_tile > 14) {
        base.progress_on_tile = 0;
    }

    for (size_t i = 0; i < std::size(FISHPOINT_OFFSETS); i++) {
        d.offset = (short)((d.offset + 1) % std::size(FISHPOINT_OFFSETS));
        const vec2i offset = FISHPOINT_OFFSETS[d.offset];
        if (drift_retarget(base.source_tile.shifted(offset.x, offset.y))) {
            break;
        }
    }
}

void figure_fishing_point::figure_action() {
    spot_tick();

    base.terrain_usage = TERRAIN_USAGE_ANY;
    base.use_cross_country = true;
    auto &d = runtime_data();
    const bool animation_finished = (base.animctx.frame == 0);
    if (!!game_features::gameplay_change_fishing_points_drift) {
        drift(animation_finished);
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