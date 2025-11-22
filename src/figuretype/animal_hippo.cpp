#include "animal_hippo.h"

#include "core/profiler.h"
#include "grid/terrain.h"
#include "city/city.h"
#include "core/random.h"
#include "figure/figure.h"
#include "graphics/animation.h"
#include "sound/sound.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_hippo);

void figure_hippo::on_create() {
    figure_impl::on_create();
    base.allow_move_type = EMOVE_AMPHIBIAN;
}

void figure_hippo::on_post_load() {
    base.allow_move_type = EMOVE_AMPHIBIAN;
}

void figure_hippo::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/Hippo");
    const formation* m = formation_get(base.formation_id);
    g_city.figures.add_animal();

    base.allow_move_type = EMOVE_AMPHIBIAN;
    base.roam_wander_freely = false;

    // Check if the hippo has taken damage from arrows
    auto &d = runtime_data();
    if (d.applied_damage > 0) {
        d.applied_damage = 0;
        
        // Hippo is aggressive - chase the attacker!
        if (d.attacker_id > 0) {
            figure *attacker = figure_get(d.attacker_id);
            if (attacker && attacker->is_alive()) {
                base.destination_tile = attacker->tile;
                advance_action(ACTION_16_HIPPO_CHASING);
                return;
            }
        }
        // If no valid attacker, just recalculate position
        advance_action(ACTION_8_HIPPO_RECALCULATE);
        return;
    }

    switch (action_state()) {
    case ACTION_24_HIPPO_SPAWNED:     // spawning
    case ACTION_15_HIPPO_TERRIFIED:   // terrified
    case ACTION_18_HIPPO_ROOSTING:    // roosting
    case ACTION_19_HIPPO_IDLE:        // idle
    case ACTION_196_HIPPO_AT_REST:
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            advance_action(ACTION_8_HIPPO_RECALCULATE);
        }
        break;

    case ACTION_8_HIPPO_RECALCULATE:
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            if (figure_herd_roost(&base, /*step*/4, /*bias*/8, /*max_dist*/32, TERRAIN_IMPASSABLE_HIPPO)) {
                base.wait_ticks = 0;
                advance_action(ACTION_10_HIPPO_GOING);
            } else {
                base.wait_ticks = 5;
            }
        }
        break;

    case ACTION_16_HIPPO_CHASING: {
        // Chase the attacker
        figure *attacker = figure_get(d.attacker_id);
        if (!attacker || !attacker->is_alive()) {
            // Attacker is gone, return to normal behavior
            advance_action(ACTION_8_HIPPO_RECALCULATE);
            break;
        }
        
        base.destination_tile = attacker->tile;
        
        // Check if we're close enough to attack
        int distance = calc_maximum_distance(tile(), attacker->tile);
        if (distance <= 1) {
            advance_action(ACTION_11_HIPPO_ATTACKING);
            base.wait_ticks = 12; // Attack animation duration
        } else {
            // Keep chasing
            do_goto(base.destination_tile, TERRAIN_USAGE_ANY, ACTION_11_HIPPO_ATTACKING, ACTION_16_HIPPO_CHASING);
        }
        break;
    }

    case ACTION_11_HIPPO_ATTACKING: {
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            // Deal damage to the attacker
            figure *attacker = figure_get(d.attacker_id);
            if (attacker && attacker->is_alive()) {
                int distance = calc_maximum_distance(tile(), attacker->tile);
                if (distance <= 1) {
                    // Attack!
                    attacker->dcast()->apply_damage(50, base.id); // Hippos are dangerous!
                    base.wait_ticks = 12; // Wait before next attack
                } else {
                    // Target moved away, chase again
                    advance_action(ACTION_16_HIPPO_CHASING);
                }
            } else {
                // Target is gone
                advance_action(ACTION_8_HIPPO_RECALCULATE);
            }
        }
        break;
    }
        
    case ACTION_10_HIPPO_GOING:
        if (do_goto(base.destination_tile, TERRAIN_USAGE_ANY, ACTION_18_HIPPO_ROOSTING + (random_byte() & 0x1), ACTION_8_HIPPO_RECALCULATE)) {
            if (map_has_figure_but(base.destination_tile, id())) {
                base.wait_ticks = 1;
                advance_action(ACTION_8_HIPPO_RECALCULATE);
            } else {
                base.wait_ticks = 50;
            }
        }
        break;

    default:
        advance_action(ACTION_8_HIPPO_RECALCULATE);
        break;
    }
}

void figure_hippo::update_animation() {
    switch (action_state()) {
    case ACTION_8_HIPPO_RECALCULATE:
    case ACTION_19_HIPPO_IDLE:
        image_set_animation(animkeys().idle);
        break;

    case ACTION_18_HIPPO_ROOSTING:
        image_set_animation(animkeys().eating);
        break;

    case ACTION_16_HIPPO_CHASING:
    case ACTION_10_HIPPO_GOING:
        image_set_animation(animkeys().walk);
        break;

    case ACTION_11_HIPPO_ATTACKING:
        image_set_animation(animkeys().attack);
        break;

    case ACTION_15_HIPPO_TERRIFIED:
    case 14:
        image_set_animation(animkeys().idle);
        base.animctx.frame = 0;
        break;

    case FIGURE_ACTION_149_CORPSE:
        image_set_animation(animkeys().death);
        break;

    default:
        // In any strange situation load eating/roosting animation
        image_set_animation(animkeys().eating);
        break;
    }
}

void figure_hippo::apply_damage(int hit_dmg, figure_id attacker_id) {
    figure_impl::apply_damage(hit_dmg, attacker_id);

    auto& d = runtime_data();
    d.applied_damage += hit_dmg;
    if (attacker_id > 0) {
        d.attacker_id = attacker_id;
    }
}

void figure_hippo::herd_moved() {
    advance_action(ACTION_8_HIPPO_RECALCULATE);
}

void figure_hippo::moveto(tile2i tile) {
    advance_action(ACTION_10_HIPPO_GOING, tile);
}
