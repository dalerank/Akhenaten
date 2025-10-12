#include "animal_ostrich.h"

#include "figure/figure.h"
#include "city/city.h"
#include "grid/terrain.h"
#include "grid/figure.h"
#include "core/random.h"
#include "graphics/image_groups.h"
#include "graphics/image.h"
#include "sound/sound.h"
#include "graphics/animation.h"
#include "figuretype/figure_ostrich_hunter.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_ostrich);

void figure_ostrich::figure_action() {
    const formation* m = formation_get(base.formation_id);
    g_city.figures.add_animal();

    switch (base.action_state) {
    case ACTION_24_OSTRICH_SPAWNED:     // spawning
    case ACTION_15_OSTRICH_TERRIFIED:   // terrified
    case ACTION_18_OSTRICH_ROOSTING:           // roosting
    case ACTION_19_OSTRICH_IDLE: // idle
    case ACTION_196_OSTRICH_AT_REST:
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            advance_action(ACTION_8_OSTRICH_RECALCULATE);
        }
        break;

    case ACTION_8_OSTRICH_RECALCULATE:
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            if (base.herd_roost(/*step*/4, /*bias*/8, /*max_dist*/32, TERRAIN_IMPASSABLE_OSTRICH)) {
                base.wait_ticks = 0;
                advance_action(ACTION_10_OSTRICH_GOING);
            } else {
                base.wait_ticks = 5;
            }
        }
        break;

    case ACTION_16_OSTRICH_FLEEING: // fleeing
    case ACTION_10_OSTRICH_GOING:
        if (do_goto(base.destination_tile, TERRAIN_USAGE_ANIMAL, ACTION_18_OSTRICH_ROOSTING + (random_byte() & 0x1), ACTION_8_OSTRICH_RECALCULATE)) {
            if (map_has_figure_but(base.destination_tile, id())) {
                base.wait_ticks = 1;
                advance_action(ACTION_8_OSTRICH_RECALCULATE);
            } else {
                base.wait_ticks = 50;
            }
        }
        break;
    }
}

void figure_ostrich::update_animation() {
    switch (action_state()) {
    case ACTION_8_OSTRICH_RECALCULATE:
    case ACTION_19_OSTRICH_IDLE: // idle
        image_set_animation(animkeys().idle);
        break;

    case ACTION_18_OSTRICH_ROOSTING: // roosting
        image_set_animation(animkeys().eating);
        break;

    case ACTION_16_OSTRICH_FLEEING: // fleeing
    case ACTION_10_OSTRICH_GOING:   // on the move
        image_set_animation(animkeys().walk);
        break;

    case ACTION_15_OSTRICH_TERRIFIED: // terrified
    case 14:                         // scared
        image_set_animation(animkeys().idle);
        base.animctx.frame = 0;
        break;

    case FIGURE_ACTION_149_CORPSE:
        image_set_animation(animkeys().death);
        break;

    case FIGURE_ACTION_150_ATTACK:
        // TODO: dalerank ostrich want to attack anybody
        //advance_action(ACTION_8_RECALCULATE);
        //image_set_animation(GROUP_FIGURE_OSTRICH_ATTACK, 0, 8);
        break;

    default:
        // In any strange situation load eating/roosting animation
        image_set_animation(animkeys().eating);
        break;
    }
}

void figure_ostrich::before_poof() {

}

bool figure_ostrich::play_die_sound() {
    g_sound.play_effect(SOUND_EFFECT_OSTRICH_DIE);
    return true;
}
