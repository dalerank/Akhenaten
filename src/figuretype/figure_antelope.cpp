#include "figure_antelope.h"

#include "city/city.h"
#include "core/random.h"
#include "figure/formation.h"
#include "figure/formation_layout.h"
#include "figure/route.h"
#include "graphics/animation.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "js/js_game.h"
#include "sound/effect.h"
#include "sound/sound.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_antelope);

void figure_antelope::static_params::archive_init() {
    verify_no_crash(scared_ticks > 0);
    verify_no_crash(rest_base_ticks > 0);
    verify_no_crash(rest_random_ticks > 0);
    verify_no_crash(no_tile_wait_ticks > 0);
    verify_no_crash(dying_ticks > 0);
    verify_no_crash(alert_ticks > 0);
}

int figure_antelope::move_speed() const {
    if (base.speed_multiplier == 0) {
        return 0;
    }
    return std::max(1, (int)base.speed_multiplier);
}

void figure_antelope::begin_choose() {
    advance_action(ACTION_8_ANTELOPE_CHOOSE);
}

void figure_antelope::begin_rest_or_graze() {
    random_generate_next();
    const auto &p = current_params();
    base.wait_ticks = (int16_t)(p.rest_base_ticks + (random_byte() % std::max<uint16_t>(1, p.rest_random_ticks)));
    advance_action((random_byte() & 1) ? ACTION_18_ANTELOPE_REST : ACTION_19_ANTELOPE_GRAZE);
}

void figure_antelope::walk_near_destination() {
    const formation *m = formation_get(base.formation_id);
    tile2i center = base.tile;
    if (m) {
        if (m->destination.valid()) {
            center = m->destination;
        } else if (m->home.valid()) {
            center = m->home;
        }
    }

    random_generate_next();
    const int start = random_byte() % 16;
    for (int i = 0; i < 16; i++) {
        const tile2i off = formation_layout_position(FORMATION_HERD, (start + i) % 16);
        const tile2i dest = center.shifted(off.x(), off.y());
        if (!dest.valid() || !map_grid_is_inside(dest, 1)) {
            continue;
        }
        if (map_terrain_is(dest, TERRAIN_IMPASSABLE_ANTELOPE)) {
            continue;
        }
        base.destination_tile = dest;
        base.route_remove();
        advance_action(ACTION_10_ANTELOPE_WALK);
        return;
    }

    base.wait_ticks = (int16_t)current_params().no_tile_wait_ticks;
}

void figure_antelope::start_flee() {
    walk_near_destination();
    if (action_state(ACTION_10_ANTELOPE_WALK)) {
        advance_action(ACTION_16_ANTELOPE_FLEE);
    } else {
        advance_action(ACTION_14_ANTELOPE_ALERT);
        base.wait_ticks = (int16_t)current_params().alert_ticks;
    }
}

void figure_antelope::figure_action() {
    g_city.figures.add_animal();

    base.terrain_usage = TERRAIN_USAGE_ANIMAL;
    base.use_cross_country = false;
    base.set_flag(e_figure_flag_invisible, false);

    auto &d = runtime_data();
    if (d.scared_ticks > 0) {
        --d.scared_ticks;
    }
    if (d.scared_ticks == 0) {
        base.set_flag(e_figure_flag_scared, false);
    }

    if (d.applied_damage > 0) {
        d.applied_damage = 0;
        const uint8_t duration = current_params().scared_ticks;
        if (duration > 0) {
            base.set_flag(e_figure_flag_scared);
            d.scared_ticks = duration;
        }
        start_flee();
        return;
    }

    if (base.is_scared()
        && !action_state(ACTION_16_ANTELOPE_FLEE, ACTION_17_ANTELOPE_STAMPEDE, ACTION_10_ANTELOPE_WALK,
                         ACTION_12_ANTELOPE_HUNTED, FIGURE_ACTION_149_CORPSE)) {
        start_flee();
        return;
    }

    switch (action_state()) {
    case FIGURE_ACTION_149_CORPSE:
        base.figure_combat_handle_corpse();
        break;

    case ACTION_12_ANTELOPE_HUNTED:
        if (base.wait_ticks == 0) {
            base.play_die_sound();
        }
        if (++base.wait_ticks > current_params().dying_ticks) {
            advance_action(FIGURE_ACTION_149_CORPSE);
        }
        break;

    case ACTION_24_ANTELOPE_SPAWNED:
        // OG sets is_ghost while spawned.
        if (--base.wait_ticks < 1) {
            begin_choose();
            break;
        }
        base.set_flag(e_figure_flag_invisible, true);
        return;

    case ACTION_8_ANTELOPE_CHOOSE:
        begin_rest_or_graze();
        return;

    case ACTION_18_ANTELOPE_REST:
        if (--base.wait_ticks < 0) {
            base.wait_ticks = 0;
        }
        if (base.wait_ticks > 0) {
            break;
        }
        walk_near_destination();
        break;

    case ACTION_19_ANTELOPE_GRAZE:
    case ACTION_196_ANTELOPE_AT_REST:
        if (--base.wait_ticks > 0) {
            break;
        }
        advance_action(ACTION_18_ANTELOPE_REST);
        return;

    case ACTION_9_ANTELOPE_MOVE:
    case ACTION_10_ANTELOPE_WALK: {
        const int spd = move_speed();
        if (spd <= 0) {
            break;
        }
        base.move_ticks(spd);
        if (base.direction == DIR_FIGURE_REROUTE) {
            // OG antelope: route_remove only (keep direction).
            base.route_remove();
        } else if (base.direction == DIR_FIGURE_CAN_NOT_REACH) {
            base.direction = base.previous_tile_direction;
            base.route_remove();
            begin_choose();
            base.wait_ticks = (int16_t)(base.index_in_formation * 5);
            return;
        } else if (base.direction == DIR_FIGURE_NONE) {
            base.direction = base.previous_tile_direction;
            begin_rest_or_graze();
        }
        break;
    }

    case ACTION_14_ANTELOPE_ALERT:
    case ACTION_15_ANTELOPE_ALERTED_BY_MATE:
        if (!base.is_scared() && base.wait_ticks > 0 && --base.wait_ticks < 1) {
            begin_choose();
        }
        break;

    case ACTION_16_ANTELOPE_FLEE:
    case ACTION_17_ANTELOPE_STAMPEDE: {
        const int spd = move_speed();
        if (spd <= 0) {
            break;
        }
        base.move_ticks(spd * 2);
        if (base.direction == DIR_FIGURE_REROUTE) {
            base.route_remove();
        } else if (base.direction == DIR_FIGURE_CAN_NOT_REACH || base.direction == DIR_FIGURE_NONE) {
            // OG: LOST or arrival → ALERT (unlike ostrich flee LOST→dead).
            base.direction = base.previous_tile_direction;
            advance_action(ACTION_14_ANTELOPE_ALERT);
            base.wait_ticks = (int16_t)current_params().alert_ticks;
        }
        break;
    }

    default:
        begin_choose();
        break;
    }
}

void figure_antelope::update_animation() {
    switch (action_state()) {
    case ACTION_24_ANTELOPE_SPAWNED:
        break;

    case ACTION_12_ANTELOPE_HUNTED:
    case FIGURE_ACTION_149_CORPSE:
        image_set_animation(animkeys().death);
        break;

    case ACTION_18_ANTELOPE_REST:
        image_set_animation(animkeys().idle);
        break;

    case ACTION_19_ANTELOPE_GRAZE:
    case ACTION_196_ANTELOPE_AT_REST:
        image_set_animation(animkeys().eating);
        break;

    case ACTION_8_ANTELOPE_CHOOSE:
    case ACTION_14_ANTELOPE_ALERT:
    case ACTION_15_ANTELOPE_ALERTED_BY_MATE:
        // OG: walk group + direction only.
        image_set_animation(animkeys().walk);
        base.animctx.frame = 0;
        break;

    case ACTION_16_ANTELOPE_FLEE:
    case ACTION_17_ANTELOPE_STAMPEDE:
        image_set_animation("run");
        break;

    case ACTION_9_ANTELOPE_MOVE:
    case ACTION_10_ANTELOPE_WALK:
        image_set_animation(animkeys().walk);
        break;

    default:
        image_set_animation(animkeys().walk);
        break;
    }
}

void figure_antelope::main_image_update() {
    if (action_state(ACTION_24_ANTELOPE_SPAWNED)) {
        base.main_image_id = 0;
        return;
    }

    if (action_state(ACTION_12_ANTELOPE_HUNTED)) {
        const animation_t &death = anim(animkeys().death);
        const int base_img = death.first_img();
        // OG death group: wait_ticks frames, capped at 7.
        const int frame = base.wait_ticks < 8 ? base.wait_ticks : 7;
        if (base_img > 0 || base.force_valid_animation) {
            base.main_image_id = base_img + frame;
        }
        return;
    }

    if (action_state(FIGURE_ACTION_149_CORPSE)) {
        const animation_t &death = anim(animkeys().death);
        const int base_img = death.first_img();
        if (base_img > 0 || base.force_valid_animation) {
            base.main_image_id = base_img + 7;
        }
        return;
    }

    figure_impl::main_image_update();
}

void figure_antelope::before_poof() {
}

bool figure_antelope::play_die_sound() {
    g_sound.play_effect(SOUND_EFFECT_ZEBRA_DIE);
    return true;
}

void figure_antelope::apply_damage(int hit_dmg, figure_id attacker_id) {
    figure_impl::apply_damage(hit_dmg, attacker_id);
    runtime_data().applied_damage += hit_dmg;
}

void figure_antelope::herd_moved() {
    begin_choose();
}

void figure_antelope::herd_rest() {
    begin_rest_or_graze();
}

void figure_antelope::herd_scare() {
    const uint8_t duration = current_params().scared_ticks;
    if (duration == 0) {
        return;
    }
    base.set_flag(e_figure_flag_scared);
    runtime_data().scared_ticks = duration;
    if (!action_state(ACTION_16_ANTELOPE_FLEE, ACTION_17_ANTELOPE_STAMPEDE)) {
        start_flee();
    }
}

void figure_antelope::moveto(tile2i tile) {
    base.destination_tile = tile;
    base.route_remove();
    advance_action(ACTION_10_ANTELOPE_WALK);
}
