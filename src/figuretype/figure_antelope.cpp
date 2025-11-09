#include "figure_antelope.h"

#include "figure/figure.h"
#include "city/city.h"
#include "grid/terrain.h"
#include "grid/figure.h"
#include "core/random.h"
#include "graphics/image_groups.h"
#include "graphics/image.h"
#include "sound/sound.h"
#include "graphics/animation.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_antelope)

void figure_antelope::figure_action() {
    const formation* m = formation_get(base.formation_id);
    g_city.figures.add_animal();

    // Check if the antelope has taken damage from arrows
    auto &d = runtime_data();
    if (d.applied_damage > 0) {
        d.applied_damage = 0;
        advance_action(ACTION_16_ANTELOPE_FLEEING);
        return;
    }

    switch (action_state()) {
    case ACTION_24_ANTELOPE_SPAWNED:     // spawning
    case ACTION_15_ANTELOPE_TERRIFIED:   // terrified
    case ACTION_18_ANTELOPE_ROOSTING:    // roosting
    case ACTION_19_ANTELOPE_IDLE:        // idle
    case ACTION_196_ANTELOPE_AT_REST:
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            advance_action(ACTION_8_ANTELOPE_RECALCULATE);
        }
        break;

    case ACTION_8_ANTELOPE_RECALCULATE:
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            if (figure_herd_roost( &base, /*step*/4, /*bias*/8, /*max_dist*/32, TERRAIN_IMPASSABLE_ANTELOPE)) {
                base.wait_ticks = 0;
                advance_action(ACTION_10_ANTELOPE_GOING);
            } else {
                base.wait_ticks = 5;
            }
        }
        break;

    case ACTION_16_ANTELOPE_FLEEING: // fleeing
        // When fleeing, search for a more distant place
        if (figure_herd_roost( &base, /*step*/8, /*bias*/16, /*max_dist*/64, TERRAIN_IMPASSABLE_ANTELOPE)) {
            base.wait_ticks = 0;
            advance_action(ACTION_10_ANTELOPE_GOING);
        } else {
            base.wait_ticks = 2;
        }
        break;
        
    case ACTION_10_ANTELOPE_GOING:
        if (do_goto(base.destination_tile, TERRAIN_USAGE_ANIMAL, ACTION_18_ANTELOPE_ROOSTING + (random_byte() & 0x1), ACTION_8_ANTELOPE_RECALCULATE)) {
            if (map_has_figure_but(base.destination_tile, id())) {
                base.wait_ticks = 1;
                advance_action(ACTION_8_ANTELOPE_RECALCULATE);
            } else {
                base.wait_ticks = 50;
            }
        }
        break;

    default:
        advance_action(ACTION_8_ANTELOPE_RECALCULATE);
        break;
    }
}

void figure_antelope::update_animation() {
    switch (action_state()) {
    case ACTION_8_ANTELOPE_RECALCULATE:
    case ACTION_19_ANTELOPE_IDLE: 
        image_set_animation(animkeys().idle);
        break;

    case ACTION_18_ANTELOPE_ROOSTING:
        image_set_animation(animkeys().eating);
        break;

    case ACTION_16_ANTELOPE_FLEEING: 
    case ACTION_10_ANTELOPE_GOING: 
        image_set_animation(animkeys().walk);
        break;

    case ACTION_15_ANTELOPE_TERRIFIED: 
    case 14:                      
        image_set_animation(animkeys().idle);
        base.animctx.frame = 0;
        break;

    case FIGURE_ACTION_149_CORPSE:
        image_set_animation(animkeys().death);
        break;

    case FIGURE_ACTION_150_ATTACK:
        // TODO: dalerank antelope want to attack anybody
        //advance_action(ACTION_8_ANTELOPE_RECALCULATE);
        //image_set_animation(GROUP_FIGURE_ANTELOPE_ATTACK, 0, 8);
        break;

    default:
        // In any strange situation load eating/roosting animation
        image_set_animation(animkeys().eating);
        break;
    }
}

void figure_antelope::before_poof() {

}

bool figure_antelope::play_die_sound() {
    g_sound.play_effect(SOUND_EFFECT_OSTRICH_DIE);
    return true;
}

void figure_antelope::apply_damage(int hit_dmg, figure_id attacker_id) {
    figure_impl::apply_damage(hit_dmg, attacker_id);

    auto& d = runtime_data();
    d.applied_damage += hit_dmg;
}

void figure_antelope::herd_moved() {
    advance_action(ACTION_8_ANTELOPE_RECALCULATE);
}

void figure_antelope::moveto(tile2i tile) {
    advance_action(ACTION_10_ANTELOPE_GOING, tile);
}
