#include "figure/figure.h"

#include "core/calc.h"
#include "figure/properties.h"
#include "graphics/image_groups.h"
#include "figuretype/maintenance.h"
#include "core/random.h"

void figure::ostrich_hunter_action() {
    figure* prey = figure_get(target_figure_id);
    int dist = 0;
    if (target_figure_id) {
        dist = calc_maximum_distance(tile, prey->tile);
    }

    if (tile == previous_tile) {
        movement_ticks_watchdog++;
    } else {
        movement_ticks_watchdog = 0;
    }

    if (movement_ticks_watchdog > 60) {
        movement_ticks_watchdog = 0;
        route_remove();
        advance_action(ACTION_8_RECALCULATE);
    }

    switch (action_state) {
    case ACTION_8_RECALCULATE:
    //case ACTION_14_RETURNING_WITH_FOOD: // spawning
        target_figure_id = is_nearby(NEARBY_ANIMAL, &dist, 10000, false);
        if (target_figure_id) {
            figure_get(target_figure_id)->targeted_by_figure_id = id;
            advance_action(ACTION_9_CHASE_PREY);
        } else {
            advance_action(ACTION_16_HUNTER_INVESTIGATE);
            map_point base_tile;
            int figure_id = is_nearby(NEARBY_ANIMAL, &dist, 10000, /*gang*/true);
            if (figure_id) {
                base_tile = figure_get(figure_id)->tile;
            } else {
                base_tile = home()->tile;
            }
            int dx;
            int dy;
            random_around_point(base_tile.x(), base_tile.y(), tile.x(), tile.y(), &dx, &dy, /*step*/4, /*bias*/8, /*max_dist*/32);
            destination_tile = map_point(dx, dy);
        }
        break;

    case ACTION_16_HUNTER_INVESTIGATE:
        do_goto(destination_tile, TERRAIN_USAGE_ANIMAL, ACTION_8_RECALCULATE, ACTION_8_RECALCULATE);
        if (direction == DIR_FIGURE_CAN_NOT_REACH) {
            direction = DIR_0_TOP_RIGHT;
            advance_action(ACTION_8_RECALCULATE);
        }
        break;

    case ACTION_13_WAIT_FOR_ACTION: // pitpat
        if (!target_figure_id) {
            return advance_action(ACTION_8_RECALCULATE);
        }

        wait_ticks--;
        if (wait_ticks <= 0) {
            advance_action(ACTION_9_CHASE_PREY);
        }
        break;

    case ACTION_9_CHASE_PREY: // following prey
        if (!target_figure_id) {
            return advance_action(ACTION_8_RECALCULATE);
        }

        if (dist >= 2) {
            do_goto(prey->tile, TERRAIN_USAGE_ANIMAL, ACTION_15_HUNTER_HUNT, ACTION_8_RECALCULATE);
        } else {
            wait_ticks = figure_properties_for_type(FIGURE_HUNTER_ARROW)->missile_delay;
            advance_action(ACTION_15_HUNTER_HUNT);
        }
        break;

    case ACTION_15_HUNTER_HUNT: // firing at prey
        wait_ticks--;
        if (wait_ticks <= 0) {
            if (!target_figure_id) {
                return advance_action(ACTION_8_RECALCULATE);
            }
            wait_ticks = figure_properties_for_type(FIGURE_HUNTER_ARROW)->missile_delay;
            if (prey->state == FIGURE_STATE_DYING) {
                advance_action(ACTION_11_HUNTER_WALK);
            } else if (dist >= 2) {
                //                    advance_action(9);
                //                    wait_ticks = 0;
                wait_ticks = 12;
                advance_action(ACTION_13_WAIT_FOR_ACTION);
            } else {
                direction = calc_missile_shooter_direction(tile.x(), tile.y(), prey->tile.x(), prey->tile.y());
                missile_fire_at(target_figure_id, FIGURE_HUNTER_ARROW);
            }
        }
        break;

    case ACTION_11_GOING_TO_PICKUP_POINT: // going to pick up prey
        if (!target_figure_id) {
            return advance_action(ACTION_8_RECALCULATE);
        }

        if (do_goto(prey->tile, TERRAIN_USAGE_ANIMAL, ACTION_10_PICKUP_ANIMAL, ACTION_11_GOING_TO_PICKUP_POINT)) {
            anim_offset = 0;
        }
        break;

    case ACTION_10_PICKUP_ANIMAL: // picking up prey
        if (target_figure_id) {
            prey->poof();
        }
        target_figure_id = 0;
        if (anim_frame >= 17) {
            advance_action(ACTION_12_GOING_HOME_AND_UNLOAD);
        }
        break;

    case ACTION_12_GOING_HOME_AND_UNLOAD:                                     // returning with prey
        if (do_returnhome(TERRAIN_USAGE_ANIMAL)) { // add game meat to hunting lodge!
            home()->stored_full_amount += 100;
        }

        break;
    }

    switch (action_state) {
    case ACTION_14_RETURNING_WITH_FOOD:
    case ACTION_9_CHASE_PREY:
    case ACTION_11_HUNTER_WALK: // normal walk
        image_set_animation(GROUP_FIGURE_HUNTER_OSTRICH_MOVE, 0, 12);
        break;

    case ACTION_8_RECALCULATE:
    case ACTION_13_WAIT_FOR_ACTION:
        image_set_animation(GROUP_FIGURE_HUNTER_OSTRICH_FIGHT, 0, 12);
        break;

    case ACTION_15_HUNTER_HUNT: // hunting
        image_set_animation(GROUP_FIGURE_HUNTER_OSTRICH_HUNT, 0, 12);
        break;
        //        case ??: // attacking
        //            image_set_animation(GROUP_FIGURE_HUNTER, 200, 12);
        //        case ??: // attacking w/ prey on his back
        //            image_set_animation(GROUP_FIGURE_HUNTER, 296, 12);
    case ACTION_15_HUNTER_PACK:
        image_set_animation(GROUP_FIGURE_HUNTER_OSTRICH_PACK, 0, 18);
        break;

    case ACTION_15_HUNTER_MOVE_PACKED:
        image_set_animation(GROUP_FIGURE_HUNTER_OSTRICH_MOVE_PACKED, 0, 12);
        break;
    }
}