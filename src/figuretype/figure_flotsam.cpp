#include "figuretype/figure_flotsam.h"

#include "city/city_figures.h"
#include "core/random.h"
#include "figure/figure.h"
#include "game/game_config.h"
#include "graphics/animkeys.h"
#include "js/js_game.h"
#include "scenario/map.h"
#include "scenario/scenario.h"

#include <iterator>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_flotsam);

static const int FLOTSAM_BOB_FRAMES[] = {0, 1, 2, 3, 4, 4, 4, 3, 2, 1, 0, 0};
static const int FLOTSAM_DEBRIS_FRAMES[] = {0, 1, 1, 2, 2, 3, 3, 4, 4, 4, 3, 2, 1, 0, 0, 1, 1, 2, 2, 1, 1, 0, 0, 0};
static const int FLOTSAM_SINKING_FRAMES[]
  = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
static constexpr int FLOTSAM_SUNK_FRAME = -1;

// OG figure_create_flotsam's 20 kinds: drawn from at random, so the mix stays the original's.
static const uint8_t FLOTSAM_KINDS[] = {3, 1, 3, 2, 1, 3, 2, 3, 2, 1, 3, 3, 2, 3, 3, 3, 1, 2, 0, 1};

static bool flotsam_river_ready() {
    return scenario_map_has_river_entry() && scenario_map_has_river_exit() && g_scenario.env.flotsam_enabled;
}

static int flotsam_alive_count() {
    int count = 0;
    for (int i = 1; i < MAX_FIGURES; i++) {
        figure* f = figure_get(i);
        if (f->is_alive() && f->type == FIGURE_FLOTSAM) {
            count++;
        }
    }
    return count;
}

int figure_flotsam::spawn(int kind) {
    if (!flotsam_river_ready() || flotsam_alive_count() >= current_params().max_alive) {
        return 0;
    }

    figure* f = figure_create(FIGURE_FLOTSAM, scenario_map_river_entry(), DIR_0_TOP_RIGHT);
    if (!f || f->id <= 0) {
        return 0;
    }

    if (kind < FLOTSAM_KIND_BOBBING || kind > FLOTSAM_KIND_SINKING) {
        kind = FLOTSAM_KINDS[anti_scum_random_15bit() % std::size(FLOTSAM_KINDS)];
    }
    f->set_resource((e_resource)kind);
    f->wait_ticks = 0;
    f->destination_tile = scenario_map_river_exit();
    f->action_state = ACTION_9_FLOTSAM_FLOATING;
    f->set_flag(e_figure_flag_invisible, false);
    return f->id;
}

void figure_flotsam::spawn_update_day() {
    if (!game_features::gameplay_city_flotsam_enabled || !flotsam_river_ready()) {
        return;
    }

    if ((int)(anti_scum_random_15bit() % 100) >= current_params().spawn_chance_pct) {
        return;
    }

    spawn(-1);
}

void figure_flotsam::on_create() {
    figure_impl::on_create();
    base.allow_move_type = EMOVE_DEEPWATER;
}

void figure_flotsam::figure_action() {
    base.allow_move_type = EMOVE_DEEPWATER;
    if (!scenario_map_has_river_exit()) {
        poof();
        return;
    }

    auto& d = runtime_data();
    base.cart_image_id = 0;
    base.terrain_usage = TERRAIN_USAGE_ANY;

    switch (action_state()) {
    // Only OG saves carry waiting flotsam: they float once and are gone like the spawned ones.
    case ACTION_8_FLOTSAM_CREATED:
        base.wait_ticks--;
        if (base.wait_ticks < 1) {
            base.action_state = ACTION_9_FLOTSAM_FLOATING;
            base.wait_ticks = 0;
            base.destination_tile = scenario_map_river_exit();
        }
        break;

    case ACTION_9_FLOTSAM_FLOATING:
        if (!d.skip_tick) {
            d.skip_tick = true;
            base.wait_ticks++;
            base.move_ticks(1);
            base.height_adjusted_ticks = 0;
            if (direction() == DIR_FIGURE_NONE || direction() == DIR_FIGURE_REROUTE
                || direction() == DIR_FIGURE_CAN_NOT_REACH) {
                poof();
                return;
            }
        } else {
            d.skip_tick = false;
        }
        break;

    default:
        poof();
        return;
    }

    base.set_flag(e_figure_flag_invisible, action_state() != ACTION_9_FLOTSAM_FLOATING);
}

void figure_flotsam::update_animation() {
    auto& d = runtime_data();
    const int frames = (base.resource_id == FLOTSAM_KIND_BOBBING) ? (int)std::size(FLOTSAM_BOB_FRAMES)
                                                                  : (int)std::size(FLOTSAM_DEBRIS_FRAMES);
    d.frame++;
    if (d.frame < 0 || d.frame >= frames) {
        d.frame = 0;
    }
}

void figure_flotsam::main_image_update() {
    const auto& d = runtime_data();
    xstring key = animkeys().walk;
    int frame = 0;
    switch (base.resource_id) {
    case FLOTSAM_KIND_DEBRIS_A:
        key = "debris_a";
        frame = FLOTSAM_DEBRIS_FRAMES[d.frame % std::size(FLOTSAM_DEBRIS_FRAMES)];
        break;

    case FLOTSAM_KIND_DEBRIS_B:
        key = "debris_b";
        frame = FLOTSAM_DEBRIS_FRAMES[d.frame % std::size(FLOTSAM_DEBRIS_FRAMES)];
        break;

    case FLOTSAM_KIND_SINKING:
        key = "sinking";
        frame = FLOTSAM_SINKING_FRAMES[d.frame % std::size(FLOTSAM_SINKING_FRAMES)];
        break;

    default:
        key = base.min_max_seen ? xstring("special") : animkeys().walk;
        frame = FLOTSAM_BOB_FRAMES[d.frame % std::size(FLOTSAM_BOB_FRAMES)];
        break;
    }

    if (frame == FLOTSAM_SUNK_FRAME) {
        base.main_image_id = 0;
        base.set_flag(e_figure_flag_invisible, true);
        return;
    }

    base.main_image_id = anim(key).first_img() + frame;
    if (action_state() == ACTION_9_FLOTSAM_FLOATING) {
        base.set_flag(e_figure_flag_invisible, false);
    }
}
