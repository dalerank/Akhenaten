#include "animal_ostrich.h"

#include "figure/figure.h"
#include "city/figures.h"
#include "grid/terrain.h"
#include "grid/figure.h"
#include "core/random.h"
#include "graphics/image_groups.h"
#include "graphics/image.h"
#include "sound/effect.h"
#include "graphics/animation.h"

#include "js/js_game.h"

namespace model {

struct ostrich_t {
    static constexpr e_figure_type type = FIGURE_OSTRICH;
    animations_t anim;
};

ostrich_t ostrich;
}

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_ostrich);
void config_load_figure_ostrich() {
    g_config_arch.r_section("figure_ostrich", [] (archive arch) {
        model::ostrich.anim.load(arch);
    });
}

void figure_ostrich::figure_action() {
    const formation* m = formation_get(base.formation_id);
    city_figures_add_animal();

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
            if (base.herd_roost(/*step*/4, /*bias*/8, /*max_dist*/32, TERRAIN_IMPASSABLE_OSTRICH)) {
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

    switch (base.action_state) {
    case ACTION_8_RECALCULATE:
    case FIGURE_ACTION_19_ANIMAL_IDLE: // idle
        image_set_animation(model::ostrich.anim["idle"]);
        break;

    case ACTION_18_ROOSTING: // roosting
        image_set_animation(model::ostrich.anim["eating"]);
        break;

    case ACTION_16_FLEEING: // fleeing
    case ACTION_10_GOING:   // on the move
        image_set_animation(model::ostrich.anim["walk"]);
        break;

    case ACTION_15_ANIMAL_TERRIFIED: // terrified
    case 14:                         // scared
        image_set_animation(model::ostrich.anim["idle"]);
        base.anim_frame = 0;
        break;

    case FIGURE_ACTION_149_CORPSE:
        image_set_die_animation(model::ostrich.anim["death"]);
        break;

    case FIGURE_ACTION_150_ATTACK:
        // TODO: dalerank ostrich want to attack anybody
        //advance_action(ACTION_8_RECALCULATE);
        //image_set_animation(GROUP_FIGURE_OSTRICH_ATTACK, 0, 8);
        break;

    default:
        // In any strange situation load eating/roosting animation
        image_set_animation(model::ostrich.anim["eating"]);
        break;
    }
}

bool figure_ostrich::play_die_sound() {
    sound_effect_play(SOUND_EFFECT_OSTRICH_DIE);
    return true;
}
