#include "animal_crocodile.h"

#include "js/js_game.h"
#include "core/profiler.h"
#include "grid/terrain.h"
#include "city/city.h"
#include "core/random.h"

figures::model_t<figure_crocodile> crocodile_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_crocodile);
void config_load_figure_crocodile() {
    crocodile_m.load();
}

void figure_crocodile::on_create() {
    base.allow_move_type = EMOVE_AMPHIBIAN;
}

void figure_crocodile::on_post_load() {
    base.allow_move_type = EMOVE_AMPHIBIAN;
}

void figure_crocodile::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/Crocodile");
    const formation* m = formation_get(base.formation_id);
    g_city.figures.add_animal();

    base.allow_move_type = EMOVE_AMPHIBIAN;
    base.roam_wander_freely = false;

    switch (action_state()) {
    case FIGURE_ACTION_24_CROCODILE_CREATED: // spawning
    case FIGURE_ACTION_19_CROCODILE_IDLE: // idle
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            advance_action(ACTION_8_RECALCULATE);
        }
        break;

    case ACTION_8_RECALCULATE:
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            if (base.herd_roost(/*step*/4, /*bias*/8, /*max_dist*/32, TERRAIN_IMPASSABLE_HIPPO)) {
                base.wait_ticks = 0;
                advance_action(FIGURE_ACTION_10_CROCODILE_MOVING);
                do_goto(destination_tile, TERRAIN_USAGE_ANY, 18 + (random_byte() & 0x1), ACTION_8_RECALCULATE);
            } else {
                base.wait_ticks = 5;
            }
        }
        break;

    case FIGURE_ACTION_10_CROCODILE_MOVING:
        if (do_goto(destination_tile, TERRAIN_USAGE_ANY, 18 + (random_byte() & 0x1), ACTION_8_RECALCULATE)) {
            base.wait_ticks = 50;
        }
        break;

    default:
        advance_action(ACTION_8_RECALCULATE);
    }
}

void figure_crocodile::on_destroy() {

}

void figure_crocodile::update_animation() {
    xstring anim_key = animkeys().walk;
    switch (action_state()) {
    case ACTION_8_RECALCULATE:
    case FIGURE_ACTION_19_CROCODILE_IDLE: 
        anim_key = animkeys().idle;
        break;

    case 18: 
        anim_key = animkeys().eating;
        break;

    case 16: // fleeing
    case FIGURE_ACTION_10_CROCODILE_MOVING: // on the move
        anim_key = animkeys().walk; break;
        break;

    case 15: // terrified
    case 14: // scared
        anim_key = animkeys().eating;
        base.anim.frame = 0;
        break;

    case FIGURE_ACTION_149_CORPSE:
        anim_key = animkeys().death;
        break;

    case FIGURE_ACTION_150_CROCODILE_ATTACK: // unused?
        anim_key = animkeys().attack;
        break;

    default:
        anim_key = animkeys().eating;
        break;
    }

    image_set_animation(anim_key);
}
