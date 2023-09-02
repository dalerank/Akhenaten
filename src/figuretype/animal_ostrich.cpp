#include "animal.h"

#include "figure/figure.h"
#include "city/figures.h"
#include "grid/terrain.h"
#include "grid/figure.h"
#include "core/random.h"
#include "graphics/image_groups.h"
#include "graphics/image.h"

void figure::ostrich_action() {
    const formation* m = formation_get(formation_id);
    city_figures_add_animal();

    switch (action_state) {
    case ACTION_24_ANIMAL_SPAWNED:     // spawning
    case 14:                           // scared
    case ACTION_15_ANIMAL_TERRIFIED:   // terrified
    case ACTION_18_ROOSTING:           // roosting
    case FIGURE_ACTION_19_ANIMAL_IDLE: // idle
    case FIGURE_ACTION_196_HERD_ANIMAL_AT_REST:
        wait_ticks--;
        //            if (wait_ticks % 5 == 0 && is_nearby(NEARBY_ANY, 6))
        //                advance_action(ACTION_16_FLEEING);
        if (wait_ticks <= 0) {
            advance_action(ACTION_8_RECALCULATE);
        }
        break;

    case 199:
    case ACTION_8_RECALCULATE:
        wait_ticks--;
        if (wait_ticks <= 0) {
            if (herd_roost(/*step*/4, /*bias*/8, /*max_dist*/32, TERRAIN_IMPASSABLE_OSTRICH)) {
                wait_ticks = 0;
                advance_action(ACTION_10_GOING);
            } else {
                wait_ticks = 5;
            }
        }
        break;

    case ACTION_16_FLEEING: // fleeing
    case ACTION_10_GOING:
    case FIGURE_ACTION_197_HERD_ANIMAL_MOVING:
        //            if (action_state == 16)
        //                while (destination_x == 0 || destination_y == 0)
        //                    herd_roost(4, 8, 22);
        if (do_goto(destination_tile, TERRAIN_USAGE_ANIMAL, ACTION_18_ROOSTING + (random_byte() & 0x1), ACTION_8_RECALCULATE)) {
            if (map_has_figure_at(destination_tile)) {
                wait_ticks = 1;
                advance_action(ACTION_8_RECALCULATE);
            } else {
                wait_ticks = 50;
            }
        }
        break;
    }

    switch (action_state) {
        case ACTION_8_RECALCULATE:
        case FIGURE_ACTION_19_ANIMAL_IDLE: // idle
        image_set_animation(GROUP_FIGURE_OSTRICH_IDLE, 0, 8);
        break;

    case ACTION_18_ROOSTING: // roosting
        image_set_animation(GROUP_FIGURE_OSTRICH_IDLE, 0, 8);
        break;

    case ACTION_16_FLEEING: // fleeing
    case ACTION_10_GOING:   // on the move
        image_set_animation(GROUP_FIGURE_OSTRICH_WALK, 0, 11);
        break;

    case ACTION_15_ANIMAL_TERRIFIED: // terrified
    case 14:                         // scared
        image_set_animation(GROUP_FIGURE_OSTRICH_IDLE, 0, 8);
        anim_frame = 0;
        break;

    case FIGURE_ACTION_149_CORPSE:
        sprite_image_id = image_id_from_group(GROUP_FIGURE_OSTRICH_DEATH);
        break;

    case FIGURE_ACTION_150_ATTACK:
    // TODO: dalerank ostrich want to attack anybody
        advance_action(ACTION_8_RECALCULATE);
        image_set_animation(GROUP_FIGURE_OSTRICH_ATTACK, 0, 8);
        break;

    default:
        // In any strange situation load eating/roosting animation
        image_set_animation(GROUP_FIGURE_OSTRICH_EATING, 0, 7);
        break;
    }
}
