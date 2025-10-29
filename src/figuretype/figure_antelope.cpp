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

    switch (base.action_state) {
    case ACTION_24_ANIMAL_SPAWNED:     // spawning
    case 14:                           // scared
    case ACTION_15_ANIMAL_TERRIFIED:   // terrified
    case ACTION_18_ROOSTING:           // roosting
    case FIGURE_ACTION_19_ANIMAL_IDLE: // idle
    case FIGURE_ACTION_196_HERD_ANIMAL_AT_REST:
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            advance_action(ACTION_8_RECALCULATE);
        }
        break;

    case 199:
    case ACTION_8_RECALCULATE:
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            if (figure_herd_roost( &base, /*step*/4, /*bias*/8, /*max_dist*/32, TERRAIN_IMPASSABLE_OSTRICH)) {
                base.wait_ticks = 0;
                advance_action(ACTION_10_GOING);
            } else {
                base.wait_ticks = 5;
            }
        }
        break;

    case ACTION_16_FLEEING: // fleeing
    case ACTION_10_GOING:
    case FIGURE_ACTION_197_HERD_ANIMAL_MOVING:
        if (do_goto(base.destination_tile, TERRAIN_USAGE_ANIMAL, ACTION_18_ROOSTING + (random_byte() & 0x1), ACTION_8_RECALCULATE)) {
            if (map_has_figure_but(base.destination_tile, id())) {
                base.wait_ticks = 1;
                advance_action(ACTION_8_RECALCULATE);
            } else {
                base.wait_ticks = 50;
            }
        }
        break;
    }
}

void figure_antelope::update_animation() {
    switch (action_state()) {
    case ACTION_8_RECALCULATE:
    case FIGURE_ACTION_19_ANIMAL_IDLE: // idle
        image_set_animation(animkeys().idle);
        break;

    case ACTION_18_ROOSTING: // roosting
        image_set_animation(animkeys().eating);
        break;

    case ACTION_16_FLEEING: // fleeing
    case ACTION_10_GOING:   // on the move
        image_set_animation(animkeys().walk);
        break;

    case ACTION_15_ANIMAL_TERRIFIED: // terrified
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

    base.main_image_id = anim(animkeys().walk).first_img() + base.animctx.frame / 16;
}

void figure_antelope::before_poof() {

}

bool figure_antelope::play_die_sound() {
    g_sound.play_effect(SOUND_EFFECT_OSTRICH_DIE);
    return true;
}
