#include "figure_birds.h"

#include "city/city.h"
#include "core/random.h"
#include "figure/formation.h"
#include "figure/formation_layout.h"
#include "figure/route.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "js/js_game.h"
#include "sound/effect.h"
#include "sound/sound.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_birds);

namespace {

constexpr int k_herd_rest_base = 150;
constexpr int k_herd_rest_random = 150;
constexpr int k_no_tile_wait = 100;
constexpr int k_dying_ticks = 500;
constexpr int k_death_image_frames = 25;
constexpr int k_flock_frame_wrap = 50;

} // namespace

void figure_birds::static_params::archive_init() {
    if (scared_ticks == 0) {
        scared_ticks = 128;
    }
    if (rest_base_ticks == 0) {
        rest_base_ticks = k_herd_rest_base;
    }
    if (rest_random_ticks == 0) {
        rest_random_ticks = k_herd_rest_random;
    }
    if (no_tile_wait_ticks == 0) {
        no_tile_wait_ticks = k_no_tile_wait;
    }
    if (dying_ticks == 0) {
        dying_ticks = k_dying_ticks;
    }
}

int figure_birds::move_speed() const {
    // Honour figure::speed_multiplier (tests freeze prey at 0); fall back to params.
    if (base.speed_multiplier == 0) {
        return 0;
    }
    return std::max(1, (int)base.speed_multiplier);
}

void figure_birds::begin_rest() {
    random_generate_next();
    const auto &p = current_params();
    base.wait_ticks = (int16_t)(p.rest_base_ticks + (random_byte() % std::max<uint16_t>(1, p.rest_random_ticks)));
    advance_action(ACTION_18_BIRDS_REST);
}

void figure_birds::walk_near_home() {
    const formation *m = formation_get(base.formation_id);
    tile2i center = (m && m->home.valid()) ? m->home : base.tile;

    random_generate_next();
    const int start = random_byte() % 16;
    for (int i = 0; i < 16; i++) {
        const tile2i off = formation_layout_position(FORMATION_HERD, (start + i) % 16);
        const tile2i dest = center.shifted(off.x(), off.y());
        if (!dest.valid() || !map_grid_is_inside(dest, 1)) {
            continue;
        }
        if (map_terrain_is(dest, TERRAIN_IMPASSABLE_OSTRICH)) {
            continue;
        }
        base.destination_tile = dest;
        base.route_remove();
        advance_action(ACTION_10_BIRDS_WALK);
        return;
    }

    base.wait_ticks = (int16_t)current_params().no_tile_wait_ticks;
}

void figure_birds::figure_action() {
    g_city.figures.add_animal();

    base.terrain_usage = TERRAIN_USAGE_ANIMAL;
    base.use_cross_country = false;
    base.set_flag(e_figure_flag_invisible, false);

    auto &d = runtime_data();
    if (++d.flock_frame >= k_flock_frame_wrap) {
        d.flock_frame = 0;
    }

    if (d.scared_ticks > 0) {
        --d.scared_ticks;
    }
    if (d.scared_ticks == 0) {
        base.set_flag(e_figure_flag_scared, false);
    }

    // Remake scare bridge: damage or herd_scare → flee (OG ALERT/FLEE via hunter area scare).
    if (d.applied_damage > 0) {
        d.applied_damage = 0;
        const uint8_t duration = current_params().scared_ticks;
        if (duration > 0) {
            base.set_flag(e_figure_flag_scared);
            d.scared_ticks = duration;
        }
        walk_near_home();
        if (action_state(ACTION_10_BIRDS_WALK)) {
            advance_action(ACTION_16_BIRDS_FLEE);
        } else {
            advance_action(ACTION_14_BIRDS_ALERT);
        }
        return;
    }

    if (base.is_scared() && !action_state(ACTION_16_BIRDS_FLEE, ACTION_17_BIRDS_STAMPEDE, ACTION_10_BIRDS_WALK,
                                         ACTION_12_BIRDS_HUNTED, FIGURE_ACTION_149_CORPSE)) {
        walk_near_home();
        if (action_state(ACTION_10_BIRDS_WALK)) {
            advance_action(ACTION_16_BIRDS_FLEE);
        } else {
            advance_action(ACTION_14_BIRDS_ALERT);
        }
        return;
    }

    switch (base.action_state) {
    case FIGURE_ACTION_149_CORPSE:
        base.figure_combat_handle_corpse();
        break;

    case ACTION_12_BIRDS_HUNTED:
        if (base.wait_ticks == 0) {
            base.play_die_sound();
        }
        if (++base.wait_ticks > current_params().dying_ticks) {
            advance_action(FIGURE_ACTION_149_CORPSE);
        }
        break;

    case ACTION_24_BIRDS_SPAWNED:
        if (--base.wait_ticks < 1) {
            d.flock_frame = 0;
            advance_action(ACTION_8_BIRDS_CHOOSE);
            break;
        }
        // OG: image_id = 0 while spawned — keep ghost until wait expires.
        base.set_flag(e_figure_flag_invisible, true);
        return;

    case ACTION_8_BIRDS_CHOOSE:
    case ACTION_18_BIRDS_REST:
    case ACTION_19_BIRDS_GRAZE:
        if (--base.wait_ticks < 1) {
            walk_near_home();
        }
        break;

    case ACTION_9_BIRDS_MOVE:
    case ACTION_10_BIRDS_WALK: {
        const int spd = move_speed();
        if (spd <= 0) {
            break;
        }
        base.move_ticks(spd);
        if (base.direction == DIR_FIGURE_REROUTE) {
            base.route_remove();
        } else if (base.direction == DIR_FIGURE_CAN_NOT_REACH) {
            base.direction = base.previous_tile_direction;
            base.route_remove();
            advance_action(ACTION_8_BIRDS_CHOOSE);
            base.wait_ticks = (int16_t)(base.index_in_formation * 5);
            return;
        } else if (base.direction == DIR_FIGURE_NONE) {
            base.direction = base.previous_tile_direction;
            begin_rest();
        }
        break;
    }

    case ACTION_14_BIRDS_ALERT:
    case ACTION_15_BIRDS_ALERTED_BY_MATE:
        // Full OG herd_animal_react_to_threats is shared herd infra; scare bridge covers hunt.
        if (!base.is_scared() && base.wait_ticks > 0 && --base.wait_ticks < 1) {
            advance_action(ACTION_8_BIRDS_CHOOSE);
        }
        break;

    case ACTION_16_BIRDS_FLEE:
    case ACTION_17_BIRDS_STAMPEDE: {
        const int spd = move_speed();
        if (spd <= 0) {
            break;
        }
        base.move_ticks(spd * 2);
        if (base.direction == DIR_FIGURE_REROUTE) {
            base.route_remove();
        } else if (base.direction == DIR_FIGURE_CAN_NOT_REACH || base.direction == DIR_FIGURE_NONE) {
            base.direction = base.previous_tile_direction;
            advance_action(ACTION_14_BIRDS_ALERT);
            base.wait_ticks = 20; // OG ANIMAL_RULE_HERD_ALERT_TICKS
        }
        break;
    }

    default:
        advance_action(ACTION_8_BIRDS_CHOOSE);
        break;
    }
}

void figure_birds::update_animation() {
    switch (action_state()) {
    case ACTION_24_BIRDS_SPAWNED:
        break;

    case ACTION_12_BIRDS_HUNTED:
    case FIGURE_ACTION_149_CORPSE:
        image_set_animation(animkeys().death);
        break;

    default:
        // OG flock: SprMain 114 frames cycle without direction (see main_image_update).
        image_set_animation(animkeys().walk);
        break;
    }
}

void figure_birds::main_image_update() {
    auto &d = runtime_data();

    if (action_state(ACTION_24_BIRDS_SPAWNED)) {
        base.main_image_id = 0;
        return;
    }

    if (action_state(ACTION_12_BIRDS_HUNTED, FIGURE_ACTION_149_CORPSE)) {
        if (base.wait_ticks < k_death_image_frames) {
            const animation_t &death = anim(animkeys().death);
            const int base_img = death.first_img();
            if (base_img > 0 || base.force_valid_animation) {
                base.main_image_id = base_img + base.wait_ticks;
            } else {
                base.main_image_id = 0;
            }
        } else {
            base.main_image_id = 0;
        }
        return;
    }

    // OG: image_id = (animation_frame >> 1) + IMAGE_GROUP_FIGURE_BIRDS — no direction.
    const animation_t &walk = anim(animkeys().walk);
    const int base_img = walk.first_img();
    if (base_img > 0 || base.force_valid_animation) {
        base.main_image_id = base_img + (d.flock_frame >> 1);
    }
}

void figure_birds::before_poof() {
}

bool figure_birds::play_die_sound() {
    // Match figure::play_die_sound FIGURE_BIRDS branch (SHEEP_DIE placeholder).
    g_sound.play_effect(SOUND_EFFECT_SHEEP_DIE);
    return true;
}

void figure_birds::apply_damage(int hit_dmg, figure_id attacker_id) {
    figure_impl::apply_damage(hit_dmg, attacker_id);
    runtime_data().applied_damage += hit_dmg;
}

void figure_birds::herd_moved() {
    advance_action(ACTION_8_BIRDS_CHOOSE);
}

void figure_birds::herd_rest() {
    begin_rest();
}

void figure_birds::herd_scare() {
    if (action_state(ACTION_12_BIRDS_HUNTED, FIGURE_ACTION_149_CORPSE)) {
        return;
    }
    const uint8_t duration = current_params().scared_ticks;
    if (duration == 0) {
        return;
    }
    base.set_flag(e_figure_flag_scared);
    runtime_data().scared_ticks = duration;
    if (!action_state(ACTION_16_BIRDS_FLEE, ACTION_17_BIRDS_STAMPEDE)) {
        walk_near_home();
        if (action_state(ACTION_10_BIRDS_WALK)) {
            advance_action(ACTION_16_BIRDS_FLEE);
        } else {
            advance_action(ACTION_14_BIRDS_ALERT);
        }
    }
}

void figure_birds::moveto(tile2i tile) {
    base.destination_tile = tile;
    base.route_remove();
    advance_action(ACTION_10_BIRDS_WALK);
}
