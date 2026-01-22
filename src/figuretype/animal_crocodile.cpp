#include "animal_crocodile.h"

#include "core/profiler.h"
#include "grid/terrain.h"
#include "city/city.h"
#include "core/random.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_crocodile);

void figure_crocodile::on_create() {
    figure_impl::on_create();
    base.allow_move_type = EMOVE_AMPHIBIAN;
}

void figure_crocodile::on_post_load() {
    base.allow_move_type = EMOVE_AMPHIBIAN;
}

void figure_crocodile::figure_action() {
    OZZY_PROFILER_FUNCTION();
    const formation* m = formation_get(base.formation_id);
    g_city.figures.add_animal();

    base.allow_move_type = EMOVE_AMPHIBIAN;
    base.roam_wander_freely = false;
    base.speed_multiplier = current_params().speed_mult;
    auto &d = runtime_data();

    figure *prey = figure_get(base.target_figure_id);
    const int maxdist = base.target_figure_id 
                         ? calc_maximum_distance(tile(), prey->tile)
                         : 999;

    switch (action_state()) {
    case ACTION_24_CROCODILE_CREATED: // spawning
    case ACTION_19_CROCODILE_IDLE: // idle
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            advance_action(ACTION_8_RECALCULATE);
        }

        if (d.hungry <= 0) {
            advance_action(ACTION_25_CROCODILE_LOOKING_FOR_ATTACK);
        }
        break;

    case ACTION_9_CROCODILE_CHASE_PREY: // following prey
        base.speed_multiplier = current_params().chase_speed_mult;
        if (!base.target_figure_id) {
            return advance_action(ACTION_8_RECALCULATE);
        }

        if (maxdist == 0) { // on the same tile
            advance_action(ACTION_20_CROCODILE_ATTACK);
            base.wait_ticks = 30 + (random_byte() % 20);
        } else {
            do_goto(prey->tile, TERRAIN_USAGE_AMPHIBIA, ACTION_25_CROCODILE_LOOKING_FOR_ATTACK, ACTION_8_RECALCULATE);
            if (direction() == DIR_FIGURE_CAN_NOT_REACH || direction() == DIR_FIGURE_REROUTE) {
                base.direction = DIR_0_TOP_RIGHT;
                advance_action(ACTION_8_RECALCULATE);
            }
        }
        break;

    case ACTION_25_CROCODILE_LOOKING_FOR_ATTACK: {
            auto result = base.is_nearby(NEARBY_ANY, current_params().max_hunting_distance, false, [] (figure *f) {
                return f->type == FIGURE_CROCODILE;
            });

            base.target_figure_id = result.fid;
            if (base.target_figure_id) {
                figure_get(base.target_figure_id)->targeted_by_figure_id = id();
                advance_action(ACTION_9_CROCODILE_CHASE_PREY);
            } else {
                advance_action(ACTION_12_CROCODILE_INVESTIGATE);
                tile2i base_tile = m->tile;
                base.destination_tile = random_around_point(base_tile, tile(), /*step*/4, /*bias*/8, /*max_dist*/32);
            }
        }
        break;

    case ACTION_12_CROCODILE_INVESTIGATE:
        do_goto(base.destination_tile, TERRAIN_USAGE_AMPHIBIA, ACTION_8_RECALCULATE, ACTION_8_RECALCULATE);
        if (direction() == DIR_FIGURE_CAN_NOT_REACH || direction() == DIR_FIGURE_REROUTE) {
            base.direction = DIR_0_TOP_RIGHT;
            advance_action(ACTION_8_RECALCULATE);
        }
        break;

    case ACTION_18_CROCODILE_EATING:
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            if (d.hungry <= 0) {
                advance_action(ACTION_8_RECALCULATE);
            } else {
                tile2i base_tile = m->tile;
                route_remove();
                base.destination_tile = random_around_point(base_tile, base_tile, /*step*/4, /*bias*/4, /*max_dist*/0);
                base.direction = calc_general_direction(tile(), base.destination_tile);
                advance_action(ACTION_26_CROCODILE_GOING_TO_RIVER);
            }
        }
        break;

    case ACTION_26_CROCODILE_GOING_TO_RIVER:
        do_goto(base.destination_tile, TERRAIN_USAGE_AMPHIBIA, ACTION_27_CROCODILE_IDLE_FULL, ACTION_8_RECALCULATE);
        break;

    case ACTION_27_CROCODILE_IDLE_FULL:
        if (d.hungry <= 0) {
            advance_action(ACTION_8_RECALCULATE);
        }
        break;

    case ACTION_21_CROCODILE_SUCCESS_KILL:
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            advance_action(ACTION_18_CROCODILE_EATING);
            base.wait_ticks = 30 + (random_byte() % 20);
        }
        break;
       
    case ACTION_20_CROCODILE_ATTACK: {
            if (base.target_figure_id == INVALID_FIGURE_ID) {
                return advance_action(ACTION_8_RECALCULATE);
            }
            base.direction = calc_general_direction(base.tile, prey->tile);
            auto prey_impl = prey->dcast();
            if (prey_impl) {
                if (maxdist == 0) { // on the same tile
                    prey_impl->on_attacked(&base);
                    if (prey->is_dead()) {
                        base.target_figure_id = 0;
                        route_remove();
                        advance_action(ACTION_21_CROCODILE_SUCCESS_KILL);
                        d.hungry = rand() % current_params().max_hungry;
                        base.wait_ticks = 30 + (random_byte() % 20);
                    } else {
                        base.wait_ticks = 10;
                    }
                } else {
                    base.wait_ticks = 12;
                    advance_action(ACTION_9_CROCODILE_CHASE_PREY);
                }
            }
        }
        break;

    case ACTION_8_RECALCULATE:
        base.wait_ticks--;
        if (d.hungry <= 0) {
            advance_action(ACTION_25_CROCODILE_LOOKING_FOR_ATTACK);
            break;
        }

        if (base.wait_ticks <= 0) {
            if (figure_herd_roost( &base, /*step*/4, /*bias*/8, /*max_dist*/32, TERRAIN_IMPASSABLE_HIPPO)) {
                base.wait_ticks = 0;
                advance_action(ACTION_10_CROCODILE_MOVING);
                do_goto(base.destination_tile, TERRAIN_USAGE_AMPHIBIA, 18 + (random_byte() & 0x1), ACTION_8_RECALCULATE);
            } else {
                base.wait_ticks = 5;
            }
        }
        break;

    case ACTION_10_CROCODILE_MOVING:
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
    const bool is_water_tile = map_terrain_is(tile(), TERRAIN_WATER);
    switch (action_state()) {
    case ACTION_8_RECALCULATE:
    case ACTION_19_CROCODILE_IDLE: 
    case ACTION_27_CROCODILE_IDLE_FULL:
        anim_key = is_water_tile ? animkeys().swim_idle : animkeys().idle;
        break;

    case ACTION_18_CROCODILE_EATING:
        anim_key = animkeys().eating;
        break;

    case ACTION_12_CROCODILE_INVESTIGATE:
    case ACTION_26_CROCODILE_GOING_TO_RIVER:
    case ACTION_10_CROCODILE_MOVING: // on the move
    case ACTION_9_CROCODILE_CHASE_PREY:
        anim_key = is_water_tile ? animkeys().swim : animkeys().walk;
        break;

    case FIGURE_ACTION_149_CORPSE:
        anim_key = animkeys().death;
        break;

    case ACTION_20_CROCODILE_ATTACK:
    case ACTION_21_CROCODILE_SUCCESS_KILL:
        anim_key = animkeys().attack;
        break;

    default:
        anim_key = is_water_tile ? animkeys().swim_idle : animkeys().idle;
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
