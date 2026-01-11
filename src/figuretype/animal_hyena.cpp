#include "animal_hyena.h"

#include "city/city.h"
#include "figure/formation_layout.h"
#include "figure/formation.h"
#include "figuretype/figure_soldier.h"
#include "figuretype/animal_ostrich.h"
#include "figuretype/figure_animal.h"
#include "grid/hyena_strength.h"
#include "grid/terrain.h"
#include "core/random.h"
#include "figure/figure.h"
#include "figure/figure_type.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_hyena)

int figure_combat_get_target_for_hyena(tile2i tile, int max_distance) {
    int min_figure_id = 0;
    int min_distance = 10000;
    for (figure *f : map_figures()) {
        if (!f->is_valid() || f->is_dead() || !f->type) {
            continue;
        }

        switch (f->type) {
        case FIGURE_EXPLOSION:
        case FIGURE_STANDARD_BEARER:
        case FIGURE_TRADE_SHIP:
        case FIGURE_FISHING_BOAT:
        case FIGURE_MAP_FLAG:
        case FIGURE_FLOTSAM:
        case FIGURE_SHIPWRECK:
        case FIGURE_INDIGENOUS_NATIVE:
        case FIGURE_TOWER_SENTRY:
        case FIGURE_NATIVE_TRADER:
        case FIGURE_ARROW:
        case FIGURE_JAVELIN:
        case FIGURE_BOLT:
        case FIGURE_BALLISTA:
        case FIGURE_CREATURE:
            continue;

        default:
            ; // nothing
        }
        if (f->is_enemy() || f->is_herd()) {
            continue;
        }
        if (::smart_cast<figure_soldier>(f) && f->action_state == ACTION_80_SOLDIER_AT_REST) {
            continue;
        }
        int distance = calc_maximum_distance(tile, f->tile);
        if (f->targeted_by_figure_id) {
            distance *= 2;
        }
        if (distance < min_distance) {
            min_distance = distance;
            min_figure_id = f->id;
        }
    }
    if (min_distance <= max_distance && min_figure_id) {
        return min_figure_id;
    }
    return 0;
}

void figure_hyena::on_create() {
    figure_impl::on_create();
    auto &d = runtime_data();
    d.hungry = rand() % current_params().max_hungry;
    base.allow_move_type = EMOVE_TERRAIN;
}

void figure_hyena::on_post_load() {
    base.allow_move_type = EMOVE_TERRAIN;
}

void figure_hyena::figure_action() {
    const formation* m = formation_get(base.formation_id);
    if (!m || !m->in_use) {
        return;
    }
    g_city.figures.add_animal();

    base.allow_move_type = EMOVE_TERRAIN;
    base.roam_wander_freely = false;
    base.speed_multiplier = current_params().speed_mult;
    auto &d = runtime_data();

    figure *prey = base.target_figure_id ? figure_get(base.target_figure_id) : nullptr;
    const int maxdist = (base.target_figure_id && prey && !prey->is_dead())
                         ? calc_maximum_distance(tile(), prey->tile)
                         : 999;

    switch (action_state()) {
    case ACTION_24_HYENA_CREATED: // spawning
    case ACTION_19_HYENA_IDLE: // idle
    case ACTION_26_HYENA_AT_REST:
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            advance_action(ACTION_8_HYENA_RECALCULATE);
        }

        if (d.hungry <= 0) {
            advance_action(ACTION_25_HYENA_LOOKING_FOR_ATTACK);
        }
        break;

    case ACTION_9_HYENA_CHASE_PREY: // following prey
        base.speed_multiplier = current_params().chase_speed_mult;
        if (!base.target_figure_id || !prey || prey->is_dead()) {
            return advance_action(ACTION_8_HYENA_RECALCULATE);
        }

        if (maxdist == 0) { // on the same tile
            advance_action(ACTION_20_HYENA_ATTACK);
            base.wait_ticks = 30 + (random_byte() % 20);
        } else {
            do_goto(prey->tile, TERRAIN_USAGE_ANIMAL, ACTION_25_HYENA_LOOKING_FOR_ATTACK, ACTION_8_HYENA_RECALCULATE);
            if (direction() == DIR_FIGURE_CAN_NOT_REACH || direction() == DIR_FIGURE_REROUTE) {
                base.direction = DIR_0_TOP_RIGHT;
                advance_action(ACTION_8_HYENA_RECALCULATE);
            }
        }
        break;

    case ACTION_25_HYENA_LOOKING_FOR_ATTACK: {
            // Search for ostriches or humans (citizens) as prey
            nearby_result result = {0, 9999};
            
            // First try to find ostriches
            for (int i = 1; i < MAX_FIGURES; i++) {
                figure *f = figure_get(i);
                if (f->is_dead() || f->targeted_by_figure_id) {
                    continue;
                }
                
                if (f->type == FIGURE_OSTRICH) {
                    int dist = calc_maximum_distance(tile(), f->tile);
                    if (dist <= current_params().max_hunting_distance && dist < result.distance) {
                        result.fid = i;
                        result.distance = dist;
                    }
                }
            }
            
            // If no ostrich found, look for humans (citizens, but not soldiers at rest, not enemies)
            if (!result.fid) {
                for (int i = 1; i < MAX_FIGURES; i++) {
                    figure *f = figure_get(i);
                    if (f->is_dead() || f->targeted_by_figure_id || f->is_enemy()) {
                        continue;
                    }
                    
                    // Check if it's a citizen but not a soldier at rest
                    if (f->is_citizen() && !(::smart_cast<figure_soldier>(f) && f->action_state == ACTION_80_SOLDIER_AT_REST)) {
                        int dist = calc_maximum_distance(tile(), f->tile);
                        if (dist <= current_params().max_hunting_distance && dist < result.distance) {
                            result.fid = i;
                            result.distance = dist;
                        }
                    }
                }
            }

            base.target_figure_id = result.fid;
            if (base.target_figure_id) {
                figure_get(base.target_figure_id)->targeted_by_figure_id = id();
                advance_action(ACTION_9_HYENA_CHASE_PREY);
            } else {
                advance_action(ACTION_12_HYENA_INVESTIGATE);
                tile2i base_tile = m->tile;
                max_hyena_strength_tile max_tile = map_hyena_strength_get_max(tile(), m->reseach_radius > 0 ? m->reseach_radius : 5);
                if (max_tile.strength > 0) {
                    base.destination_tile = max_tile.tile;
                } else {
                    base.destination_tile = random_around_point(base_tile, tile(), /*step*/4, /*bias*/8, /*max_dist*/32);
                }
            }
        }
        break;

    case ACTION_12_HYENA_INVESTIGATE:
        do_goto(base.destination_tile, TERRAIN_USAGE_ANIMAL, ACTION_8_HYENA_RECALCULATE, ACTION_8_HYENA_RECALCULATE);
        if (direction() == DIR_FIGURE_CAN_NOT_REACH || direction() == DIR_FIGURE_REROUTE) {
            base.direction = DIR_0_TOP_RIGHT;
            advance_action(ACTION_8_HYENA_RECALCULATE);
        }
        break;

    case ACTION_18_HYENA_EATING:
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            if (d.hungry <= 0) {
                advance_action(ACTION_8_HYENA_RECALCULATE);
            } else {
                tile2i base_tile = m->tile;
                route_remove();
                max_hyena_strength_tile max_tile = map_hyena_strength_get_max(tile(), m->reseach_radius > 0 ? m->reseach_radius : 5);
                if (max_tile.strength > 0) {
                    base.destination_tile = max_tile.tile;
                } else {
                    base.destination_tile = random_around_point(base_tile, base_tile, /*step*/4, /*bias*/4, /*max_dist*/0);
                }
                base.direction = calc_general_direction(tile(), base.destination_tile);
                advance_action(ACTION_19_HYENA_IDLE);
            }
        }
        break;

    case ACTION_21_HYENA_SUCCESS_KILL:
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            advance_action(ACTION_18_HYENA_EATING);
            base.wait_ticks = 30 + (random_byte() % 20);
        }
        break;

    case ACTION_22_HYENA_RUN_TO_CARRION:
        base.speed_multiplier = current_params().chase_speed_mult;
        if (base.destination_tile.valid()) {
            if (calc_maximum_distance(tile(), base.destination_tile) == 0) {
                advance_action(ACTION_23_HYENA_EAT_OTHER_FOOD);
                base.wait_ticks = 30 + (random_byte() % 20);
                route_remove();
            } else {
                do_goto(base.destination_tile, TERRAIN_USAGE_ANIMAL, ACTION_23_HYENA_EAT_OTHER_FOOD, ACTION_8_HYENA_RECALCULATE);
                if (direction() == DIR_FIGURE_CAN_NOT_REACH || direction() == DIR_FIGURE_REROUTE) {
                    base.direction = DIR_0_TOP_RIGHT;
                    advance_action(ACTION_8_HYENA_RECALCULATE);
                }
            }
        } else {
            advance_action(ACTION_8_HYENA_RECALCULATE);
        }
        break;

    case ACTION_23_HYENA_EAT_OTHER_FOOD:
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            advance_action(ACTION_8_HYENA_RECALCULATE);
            d.hungry = rand() % current_params().max_hungry;
        }
        break;
       
    case ACTION_20_HYENA_ATTACK: {
            if (base.target_figure_id == INVALID_FIGURE_ID || !prey || prey->is_dead()) {
                return advance_action(ACTION_8_HYENA_RECALCULATE);
            }
            base.direction = calc_general_direction_safe(base.tile, prey->tile);
            auto prey_impl = prey->dcast();
            if (prey_impl) {
                if (maxdist == 0) { // on the same tile
                    prey_impl->on_attacked(&base);
                    if (prey->is_dead()) {
                        base.target_figure_id = 0;
                        route_remove();
                        
                        int attracted_count = 0;
                        const int max_attract = 4;
                        
                        for (int i = 0; i < formation::max_figures_count && attracted_count < max_attract; i++) {
                            if (!m->figures[i] || m->figures[i] == id()) {
                                continue;
                            }
                            
                            figure *other_hyena = figure_get(m->figures[i]);
                            if (!other_hyena || other_hyena->is_dead() || other_hyena->type != FIGURE_HYENA) {
                                continue;
                            }
                                                      
                            if (other_hyena->action_state == ACTION_18_HYENA_EATING ||
                                other_hyena->action_state == ACTION_22_HYENA_RUN_TO_CARRION ||
                                other_hyena->action_state == ACTION_23_HYENA_EAT_OTHER_FOOD) {
                                continue;
                            }
                            
                            other_hyena->route_remove();
                            other_hyena->advance_action(ACTION_22_HYENA_RUN_TO_CARRION);
                            other_hyena->destination_tile = prey->tile;
                            attracted_count++;
                        }
                        
                        advance_action(ACTION_21_HYENA_SUCCESS_KILL);
                        d.hungry = rand() % current_params().max_hungry;
                        base.wait_ticks = 30 + (random_byte() % 20);
                    } else {
                        base.wait_ticks = 10;
                    }
                } else {
                    base.wait_ticks = 12;
                    advance_action(ACTION_9_HYENA_CHASE_PREY);
                }
            }
        }
        break;

    case ACTION_8_HYENA_RECALCULATE:
        base.wait_ticks--;
        if (d.hungry <= 0) {
            advance_action(ACTION_25_HYENA_LOOKING_FOR_ATTACK);
            break;
        }

        if (base.wait_ticks <= 0) {
            tile2i base_tile = m->tile;
            max_hyena_strength_tile max_tile = map_hyena_strength_get_max(tile(), m->reseach_radius > 0 ? m->reseach_radius : 5);
            if (max_tile.strength > 0) {
                base.destination_tile = max_tile.tile;
            } else if (figure_herd_roost(&base, /*step*/4, /*bias*/8, /*max_dist*/32, TERRAIN_IMPASSABLE_HYENA)) {
                base.wait_ticks = 0;
                advance_action(ACTION_10_HYENA_MOVING);
                do_goto(base.destination_tile, TERRAIN_USAGE_ANIMAL, 18 + (random_byte() & 0x1), ACTION_8_HYENA_RECALCULATE);
            } else {
                base.wait_ticks = 5;
            }
        }
        break;

    case ACTION_10_HYENA_MOVING:
        if (do_goto(base.destination_tile, TERRAIN_USAGE_ANIMAL, 18 + (random_byte() & 0x1), ACTION_8_HYENA_RECALCULATE)) {
            base.wait_ticks = 50;
        }
        break;

    default:
        advance_action(ACTION_8_HYENA_RECALCULATE);
    }
}

void figure_hyena::on_destroy() {
}

void figure_hyena::update_animation() {
    xstring anim_key = animkeys().walk;
    switch (action_state()) {
    case ACTION_8_HYENA_RECALCULATE:
    case ACTION_19_HYENA_IDLE:
    case ACTION_26_HYENA_AT_REST:
    case ACTION_24_HYENA_CREATED:
        anim_key = animkeys().idle;
        break;

    case ACTION_18_HYENA_EATING:
        anim_key = animkeys().eating;
        break;

    case ACTION_12_HYENA_INVESTIGATE:
    case ACTION_10_HYENA_MOVING:
    case ACTION_9_HYENA_CHASE_PREY:
    case ACTION_22_HYENA_RUN_TO_CARRION:
        anim_key = animkeys().walk;
        break;

    case FIGURE_ACTION_149_CORPSE:
        anim_key = animkeys().death;
        break;

    case ACTION_20_HYENA_ATTACK:
    case ACTION_21_HYENA_SUCCESS_KILL:
        anim_key = animkeys().attack;
        break;

    case ACTION_23_HYENA_EAT_OTHER_FOOD:
        anim_key = animkeys().eating;
        break;

    default:
        anim_key = animkeys().idle;
        break;
    }

    image_set_animation(anim_key);
}

void figure_hyena::update_day() {
    figure_impl::update_day();

    auto &d = runtime_data();
    if (d.hungry > 0) {
        d.hungry--;
    }
}
