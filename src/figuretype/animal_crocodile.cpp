#include "animal_crocodile.h"

#include "core/profiler.h"
#include "grid/terrain.h"
#include "city/city.h"
#include "core/random.h"

figure_crocodile::static_params crocodile_m;

void figure_crocodile::static_params::archive_load(archive arch) {
    max_hungry = arch.r_int("max_hungry", 25);
    max_hunting_distance = arch.r_int("max_hunting_distance", 10);
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
    auto &d = runtime_data();

    figure *prey = figure_get(base.target_figure_id);
    int dist = 0;
    if (base.target_figure_id) {
        dist = calc_maximum_distance(tile(), prey->tile);
    }

    switch (action_state()) {
    case FIGURE_ACTION_24_CROCODILE_CREATED: // spawning
    case FIGURE_ACTION_19_CROCODILE_IDLE: // idle
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            advance_action(ACTION_8_RECALCULATE);
        }

        if (d.hungry <= 0) {
            advance_action(FIGURE_ACTION_24_CROCODILE_LOOKING_FOR_ATTACK);
        }
        break;

    case ACTION_9_CROCODILE_CHASE_PREY: // following prey
        if (!base.target_figure_id) {
            return advance_action(ACTION_8_RECALCULATE);
        }

        if (dist >= 1) {
            do_goto(prey->tile, TERRAIN_USAGE_AMPHIBIA, FIGURE_ACTION_24_CROCODILE_LOOKING_FOR_ATTACK, ACTION_8_RECALCULATE);
        } else {
            advance_action(FIGURE_ACTION_24_CROCODILE_LOOKING_FOR_ATTACK);
        }
        break;

    case FIGURE_ACTION_24_CROCODILE_LOOKING_FOR_ATTACK:
        base.target_figure_id = base.is_nearby(NEARBY_ANY, &dist, current_params().max_hunting_distance, false, [] (figure* f) {
            return f->type == FIGURE_CROCODILE;
        });
        if (base.target_figure_id) {
            figure_get(base.target_figure_id)->targeted_by_figure_id = id();
            advance_action(ACTION_9_CROCODILE_CHASE_PREY);
        } else {
            advance_action(FIGURE_ACTION_12_CROCODILE_INVESTIGATE);
            tile2i base_tile = m->tile;
            base.destination_tile = random_around_point(base_tile, tile(), /*step*/4, /*bias*/8, /*max_dist*/32);
        }
        break;

    case FIGURE_ACTION_12_CROCODILE_INVESTIGATE:
        do_goto(base.destination_tile, TERRAIN_USAGE_AMPHIBIA, ACTION_8_RECALCULATE, ACTION_8_RECALCULATE);
        if (direction() == DIR_FIGURE_CAN_NOT_REACH || direction() == DIR_FIGURE_REROUTE) {
            base.direction = DIR_0_TOP_RIGHT;
            advance_action(ACTION_8_RECALCULATE);
        }
        break;

    case FIGURE_ACTION_20_CROCODILE_ATTACK:
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            base.direction = calc_general_direction(base.tile, prey->tile);
            if (!base.target_figure_id) {
                return advance_action(ACTION_8_RECALCULATE);
            }

            if (prey->state == FIGURE_STATE_DYING) {
                d.hungry += static_params().max_hungry;
                advance_action(FIGURE_ACTION_19_CROCODILE_IDLE);
            } else if (dist >= 1) {
                base.wait_ticks = 12;
                advance_action(ACTION_9_CROCODILE_CHASE_PREY);
            }
        }
        break;

    case ACTION_8_RECALCULATE:
        base.wait_ticks--;
        if (d.hungry <= 0) {
            advance_action(FIGURE_ACTION_24_CROCODILE_LOOKING_FOR_ATTACK);
            break;
        }

        if (base.wait_ticks <= 0) {
            if (base.herd_roost(/*step*/4, /*bias*/8, /*max_dist*/32, TERRAIN_IMPASSABLE_HIPPO)) {
                base.wait_ticks = 0;
                advance_action(FIGURE_ACTION_10_CROCODILE_MOVING);
                do_goto(base.destination_tile, TERRAIN_USAGE_AMPHIBIA, 18 + (random_byte() & 0x1), ACTION_8_RECALCULATE);
            } else {
                base.wait_ticks = 5;
            }
        }
        break;

    case FIGURE_ACTION_10_CROCODILE_MOVING:
        if (do_goto(base.destination_tile, TERRAIN_USAGE_AMPHIBIA, 18 + (random_byte() & 0x1), ACTION_8_RECALCULATE)) {
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

    case FIGURE_ACTION_18_CROCODILE_EATING:
        anim_key = animkeys().eating;
        break;

    case FIGURE_ACTION_12_CROCODILE_INVESTIGATE:
    case FIGURE_ACTION_10_CROCODILE_MOVING: // on the move
        anim_key = animkeys().walk;
        break;

    case FIGURE_ACTION_149_CORPSE:
        anim_key = animkeys().death;
        break;

    case FIGURE_ACTION_20_CROCODILE_ATTACK: // unused?
        anim_key = animkeys().attack;
        break;

    default:
        anim_key = animkeys().idle;
        break;
    }

    image_set_animation(anim_key);
}

void figure_crocodile::update_day() {
    figure_impl::update_day();

    auto &d = runtime_data();
    if (d.hungry > 0) {
        d.hungry--;
    }
}
