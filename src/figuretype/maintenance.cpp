#include "maintenance.h"

#include "config/config.h"
#include "building/building.h"
#include "building/building_animation.h"
#include "building/monuments.h"
#include "building/monument_mastaba.h"
#include "city/city.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "figure/combat.h"
#include "figure/enemy_army.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "graphics/image.h"
#include "grid/building.h"
#include "grid/road_access.h"
#include "sound/effect.h"
#include "core/game_environment.h"
#include "graphics/image_groups.h"
#include "figure/properties.h"
#include "building/industry.h"

#include <algorithm>

int figure::is_nearby(int category, int* distance, int max_distance, bool gang_on) {
    int figure_id = 0;
    int lowest_distance = max_distance;
    for (int i = 1; i < MAX_FIGURES; i++) {
        figure* f = figure_get(i);
        if (f->is_dead()) {
            continue;
        }

        if (!gang_on && f->targeted_by_figure_id) {
            continue;
        }

        bool category_check = false;
        auto props = figure_properties_for_type(f->type);
        switch (category) {
        case NEARBY_ANY: // any dude
            if (props->category != 0)
                category_check = true;
            break;

        case NEARBY_ANIMAL: // animal
            if (props->category == 6 || f->is_herd())
                category_check = true;
            break;

        case NEARBY_HOSTILE: // hostile
            if (f->is_enemy() || f->type == FIGURE_TOMB_ROBER || f->is_attacking_native())
                category_check = true;
            break;
        }

        // pass on to inner distance check
        if (category_check) {
            int dist = calc_maximum_distance(tile, f->tile);
            if (dist <= max_distance) {
                if (f->targeted_by_figure_id)
                    dist *= 2; // penalty
                if (category == NEARBY_HOSTILE) {
                    if (f->type == FIGURE_TOMB_ROBER || f->type == FIGURE_ENEMY54_GLADIATOR)
                        dist = calc_maximum_distance(tile, f->tile);
                    else if (f->type == FIGURE_INDIGENOUS_NATIVE
                             && f->action_state == FIGURE_ACTION_159_NATIVE_ATTACKING)
                        dist = calc_maximum_distance(tile, f->tile);
                    else if (f->is_enemy())
                        dist = 3 * calc_maximum_distance(tile, f->tile);
                    // else if (f->type == FIGURE_WOLF)
                    //     dist = 4 * calc_maximum_distance(tile.x(), tile.y(), f->tile.x(), f->tile.y());
                    //                    else
                    //                        continue;
                }
                if (dist < lowest_distance) {
                    lowest_distance = dist;
                    figure_id = i;
                    //                    if (!gang_on)
                    //                        return figure_id;
                }
            }
        }
    }
    *distance = lowest_distance;
    return figure_id;
}
// static int get_nearest_enemy(int x, int y, int *distance) {
//     int min_enemy_id = 0;
//     int min_dist = 10000;
//     for (int i = 1; i < MAX_FIGURES[GAME_ENV]; i++) {
//         figure *f = figure_get(i);
//         if (f->state != FIGURE_STATE_ALIVE || f->targeted_by_figure_id)
//             continue;
//
//         int dist;
//         if (f->type == FIGURE_RIOTER || f->type == FIGURE_ENEMY54_GLADIATOR)
//             dist = calc_maximum_distance(x, y, f->x, f->y);
//         else if (f->type == FIGURE_INDIGENOUS_NATIVE && f->action_state == FIGURE_ACTION_159_NATIVE_ATTACKING)
//             dist = calc_maximum_distance(x, y, f->x, f->y);
//         else if (f->is_enemy())
//             dist = 3 * calc_maximum_distance(x, y, f->x, f->y);
//         else if (f->type == FIGURE_WOLF)
//             dist = 4 * calc_maximum_distance(x, y, f->x, f->y);
//         else
//             continue;
//         if (dist < min_dist) {
//             min_dist = dist;
//             min_enemy_id = i;
//         }
//     }
//     *distance = min_dist;
//     return min_enemy_id;
// }

int figure::target_is_alive() {
    if (target_figure_id <= 0)
        return 0;

    figure* target = figure_get(target_figure_id);
    if (!target->is_dead() /* && target->created_sequence == target_figure_created_sequence */)
        return 1;

    return 0;
}

// Same as policeman, but can't fight
// void figure::magistrate_action() {
//    building *b = building_get(building_id);
//    switch (action_state) {
//        case FIGURE_ACTION_70_PREFECT_CREATED:
//            is_ghost = true;
//            anim_frame = 0;
//            wait_ticks--;
//            if (wait_ticks <= 0) {
//                int x_road, y_road;
//                if (map_closest_road_within_radius(b->tile.x(), b->tile.y(), b->size, 2, &x_road, &y_road)) {
//                    action_state = FIGURE_ACTION_71_PREFECT_ENTERING_EXITING;
//                    set_cross_country_destination(x_road, y_road);
//                    roam_length = 0;
//                } else
//                    poof();
//            }
//            break;
//        case 9:
//        case FIGURE_ACTION_71_PREFECT_ENTERING_EXITING:
//            use_cross_country = true;
//            is_ghost = true;
//            if (move_ticks_cross_country(1) == 1) {
//                if (map_building_at(grid_offset_figure) == building_id) {
//                    // returned to own building
//                    poof();
//                } else {
//                    action_state = FIGURE_ACTION_72_PREFECT_ROAMING;
//                    init_roaming();
//                    roam_length = 0;
//                }
//            }
//            break;
//        case ACTION_10_DELIVERING_FOOD:
//        case FIGURE_ACTION_72_PREFECT_ROAMING:
//            is_ghost = false;
//            roam_length++;
//            if (roam_length >= max_roam_length) {
//                int x_road, y_road;
//                if (map_closest_road_within_radius(b->tile.x(), b->tile.y(), b->size, 2, &x_road, &y_road)) {
//                    action_state = FIGURE_ACTION_73_PREFECT_RETURNING;
//                    destination_x = x_road;
//                    destination_y = y_road;
//                    route_remove();
//                } else
//                    poof();
//            }
//            roam_ticks(1);
//            break;
//        case ACTION_11_RETURNING_EMPTY:
//        case FIGURE_ACTION_73_PREFECT_RETURNING:
//            move_ticks(1);
//            if (direction == DIR_FIGURE_AT_DESTINATION) {
//                action_state = FIGURE_ACTION_71_PREFECT_ENTERING_EXITING;
//                set_cross_country_destination(b->tile.x(), b->tile.y());
//                roam_length = 0;
//            } else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_LOST)
//                poof();
//            break;
//    }
//    // graphic id
//    int dir;
//    if (action_state == FIGURE_ACTION_75_PREFECT_AT_FIRE ||
//        action_state == FIGURE_ACTION_150_ATTACK) {
//        dir = attack_direction;
//    } else if (direction < 8)
//        dir = direction;
//    else
//        dir = previous_tile_direction;
//    dir = figure_image_normalize_direction(dir);
//    switch (action_state) {
//        case FIGURE_ACTION_149_CORPSE:
//            sprite_image_id = image_id_from_group(GROUP_FIGURE_MAGISTRATE) + 96 + figure_image_corpse_offset();
//            break;
//        default:
//            sprite_image_id = image_id_from_group(GROUP_FIGURE_MAGISTRATE) + dir + 8 * anim_frame;
//            break;
//    }
//}
