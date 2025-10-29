#include "animal_hippo.h"

#include "core/profiler.h"
#include "grid/terrain.h"
#include "city/city.h"
#include "core/random.h"

figures::model_t<figure_hippo> hippo_m;

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

    switch (action_state()) {
    case FIGURE_ACTION_24_HIPPO_CREATED: // spawning
    case 14: // scared
    case 15: // terrified
    case 18: // roosting
    case FIGURE_ACTION_19_HIPPO_IDLE: // idle
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
            if (figure_herd_roost(&base, /*step*/4, /*bias*/8, /*max_dist*/32, TERRAIN_IMPASSABLE_HIPPO)) {
                base.wait_ticks = 0;
                advance_action(FIGURE_ACTION_10_HIPPO_MOVING);
                do_goto(base.destination_tile, TERRAIN_USAGE_ANY, 18 + (random_byte() & 0x1), ACTION_8_RECALCULATE);
            } else {
                base.wait_ticks = 5;
            }
        }
        break;

    case 16: // fleeing
    case FIGURE_ACTION_10_HIPPO_MOVING:
    case FIGURE_ACTION_197_HERD_ANIMAL_MOVING:
        if (do_goto(base.destination_tile, TERRAIN_USAGE_ANY, 18 + (random_byte() & 0x1), ACTION_8_RECALCULATE)) {
            base.wait_ticks = 50;
        }
        break;
    }
}

void figure_hippo::update_animation() {
    xstring anim_key = animkeys().walk;
    switch (action_state()) {
    case ACTION_8_RECALCULATE:
    case FIGURE_ACTION_19_HIPPO_IDLE: anim_key = animkeys().idle; break;
    case 18: anim_key = animkeys().eating; break;

    case 16: // fleeing
    case FIGURE_ACTION_10_HIPPO_MOVING: // on the move
        anim_key = animkeys().walk; break;
        break;

    case 15: // terrified
    case 14: // scared
        anim_key = animkeys().eating;
        base.animctx.frame = 0;
        break;

    case FIGURE_ACTION_149_CORPSE:
        anim_key = animkeys().death;
        break;

    case FIGURE_ACTION_150_ATTACK: // unused?
        anim_key = animkeys().attack;
        break;

    default:
        anim_key = animkeys().eating;
        break;
    }

    image_set_animation(anim_key);
}
