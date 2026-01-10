#include "figure_hyena.h"

#include "city/city.h"
#include "figure/formation_layout.h"
#include "figuretype/figure_soldier.h"
#include "grid/hyena_strength.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_hyena);

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
}

void figure_hyena::figure_action() {
    formation *m = formation_get(base.formation_id);
    if (!m || !m->in_use) {
        return;
    }
    g_city.figures.add_animal();

    switch (action_state()) {
    case ACTION_196_HYENA_AT_REST:
        base.wait_ticks++;
        if (base.wait_ticks > 400) {
            base.wait_ticks = id() & 0x1f;
            base.action_state = ACTION_197_HYENA_MOVING;
            tile2i formation_t = formation_layout_position(FORMATION_HERD, base.index_in_formation);
            tile2i target_tile = m->destination.shifted(formation_t);
            
            // Check if target tile is within hyena territory
            // If not, find a tile within territory near the current position
            int hyena_strength = map_hyena_strength_get(target_tile);
            if (hyena_strength == 0) {
                // Find a tile with maximum hyena strength in the area
                max_hyena_strength_tile max_tile = map_hyena_strength_get_max(tile(), m->reseach_radius > 0 ? m->reseach_radius : 5);
                if (max_tile.strength > 0) {
                    target_tile = max_tile.tile;
                } else {
                    // If no territory found, stay near formation destination
                    target_tile = m->destination;
                }
            }
            
            base.destination_tile = target_tile;
            base.roam_length = 0;
        }
        break;

    case ACTION_197_HYENA_MOVING:
        base.move_ticks(2);
        if (direction() == DIR_FIGURE_NONE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            base.direction = base.previous_tile_direction;
            base.action_state = ACTION_196_HYENA_AT_REST;
            base.wait_ticks = id() & 0x1f;
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else {
            // Check if we're moving outside territory - if so, stop and rest
            int current_hyena_strength = map_hyena_strength_get(tile());
            if (current_hyena_strength == 0) {
                base.direction = base.previous_tile_direction;
                base.action_state = ACTION_196_HYENA_AT_REST;
                base.wait_ticks = id() & 0x1f;
                route_remove();
            }
        }
        break;

    case ACTION_199_HYENA_ATTACKING:
        base.move_ticks(2);
        if (direction() == DIR_FIGURE_NONE) {
            int target_id = figure_combat_get_target_for_hyena(tile(), 6);
            if (target_id) {
                figure *target = figure_get(target_id);
                base.destination_tile = target->tile;
                base.target_figure_id = target_id;
                target->targeted_by_figure_id = id();
                route_remove();
            } else {
                base.direction = base.previous_tile_direction;
                base.action_state = ACTION_196_HYENA_AT_REST;
                base.wait_ticks = id() & 0x1f;
            }

        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();

        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            base.direction = base.previous_tile_direction;
            base.action_state = ACTION_196_HYENA_AT_REST;
            base.wait_ticks = id() & 0x1f;
        }
        break;

    default:
        advance_action(ACTION_196_HYENA_AT_REST);
        break;
    }
}

void figure_hyena::on_destroy() {
}

void figure_hyena::update_animation() {
    int dir = base.figure_image_direction();
    if (action_state(FIGURE_ACTION_149_CORPSE)) {
        base.main_image_id = image_id_from_group(GROUP_FIGURE_HYENA_DEATH) + base.figure_image_corpse_offset();
    } else if (action_state(ACTION_150_HYENA_ATTACK)) {
        base.main_image_id = image_id_from_group(GROUP_FIGURE_HYENA_ATTACK) + 104 + dir + 8 * (base.attack_image_offset / 4);
    } else if (action_state(ACTION_196_HYENA_AT_REST)) {
        base.main_image_id = image_id_from_group(GROUP_FIGURE_HYENA_IDLE) + 152 + dir;
    } else {
        base.main_image_id = image_id_from_group(GROUP_FIGURE_HYENA_WALK) + dir + 8 * base.animctx.frame;
    }
}
