#include "figure/figure.h"

#include "core/calc.h"
#include "figure/properties.h"
#include "graphics/image_groups.h"

void figure::hunter_action() {
    figure* prey = figure_get(target_figure_id);
    int dist = 0;
    if (target_figure_id) {
        dist = calc_maximum_distance(tile.x(), tile.y(), prey->tile.x(), prey->tile.y());
    }

    switch (action_state) {
    case ACTION_8_RECALCULATE:
    case 14: // spawning
        target_figure_id = is_nearby(1, &dist, 10000, false);
        if (target_figure_id) {
            figure_get(target_figure_id)->targeted_by_figure_id = id;
            advance_action(9);
        }
        break;
    case 13: // pitpat
        if (!target_figure_id)
            return advance_action(8);
        wait_ticks--;
        if (wait_ticks <= 0) {
            advance_action(9);
        }
        break;
    case 9: // following prey
        if (!target_figure_id)
            return advance_action(8);
        if (dist >= 2) {
            do_goto(prey->tile.x(), prey->tile.y(), TERRAIN_USAGE_ANIMAL, 15, 8);
        } else {
            wait_ticks = figure_properties_for_type(FIGURE_HUNTER_ARROW)->missile_delay;
            advance_action(15);
        }
        break;
        //        case ??: // attacking enemy
    case 15: // firing at prey
        wait_ticks--;
        if (wait_ticks <= 0) {
            if (!target_figure_id) {
                return advance_action(8);
            }
            wait_ticks = figure_properties_for_type(FIGURE_HUNTER_ARROW)->missile_delay;
            if (prey->state == FIGURE_STATE_DYING) {
                advance_action(11);
            } else if (dist >= 2) {
                //                    advance_action(9);
                //                    wait_ticks = 0;
                wait_ticks = 12;
                advance_action(13);
            } else {
                direction = calc_missile_shooter_direction(tile.x(), tile.y(), prey->tile.x(), prey->tile.y());
                missile_fire_at(target_figure_id, FIGURE_HUNTER_ARROW);
            }
        }
        break;
    case 11: // going to pick up prey
        if (!target_figure_id) {
            return advance_action(8);
        }

        if (do_goto(prey->tile.x(), prey->tile.y(), TERRAIN_USAGE_ANIMAL, 10, 11)) {
            anim_offset = 0;
        }
        break;
    case 10: // picking up prey
        if (target_figure_id) {
            prey->poof();
        }
        target_figure_id = 0;
        if (anim_frame >= 17) {
            advance_action(12);
        }
        break;
    case 12:                                     // returning with prey
        if (do_returnhome(TERRAIN_USAGE_ANIMAL)) // add game meat to hunting lodge!
            home()->stored_full_amount += 100;

        break;
    }
    switch (action_state) {
    case ACTION_8_RECALCULATE:
    case 14:
    case 13:
    case 9:
    case ACTION_11_HUNTER_WALK: // normal walk
        image_set_animation(GROUP_FIGURE_HUNTER_OSTRICH_MOVE, 0, 12);
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