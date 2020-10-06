#include "entertainer.h"

#include "building/building.h"
#include "building/list.h"
#include "core/calc.h"
#include "core/image.h"
#include "figure/combat.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "map/grid.h"
#include "map/road_access.h"
#include "map/road_network.h"
#include "scenario/gladiator_revolt.h"

static int determine_destination(int x, int y, int type1, int type2) {
    int road_network = map_road_network_get(map_grid_offset(x, y));

    building_list_small_clear();

    for (int i = 1; i < MAX_BUILDINGS[GAME_ENV]; i++) {
        building *b = building_get(i);
        if (b->state != BUILDING_STATE_VALID)
            continue;

        if (b->type != type1 && b->type != type2)
            continue;

        if (b->distance_from_entry && b->road_network_id == road_network) {
            if (b->type == BUILDING_HIPPODROME && b->prev_part_building_id)
                continue;

            building_list_small_add(i);
        }
    }
    int total_venues = building_list_small_size();
    if (total_venues <= 0)
        return 0;

    const int *venues = building_list_small_items();
    int min_building_id = 0;
    int min_distance = 10000;
    for (int i = 0; i < total_venues; i++) {
        building *b = building_get(venues[i]);
        int days_left;
        if (b->type == type1)
            days_left = b->data.entertainment.days1;
        else if (b->type == type2)
            days_left = b->data.entertainment.days2;
        else {
            days_left = 0;
        }
        int dist = days_left + calc_maximum_distance(x, y, b->x, b->y);
        if (dist < min_distance) {
            min_distance = dist;
            min_building_id = venues[i];
        }
    }
    return min_building_id;
}

void figure::entertainer_update_shows() {
    building *b = building_get(destination_building_id);
    switch (type) {
        case FIGURE_ACTOR:
            b->data.entertainment.play++;
            if (b->data.entertainment.play >= 5)
                b->data.entertainment.play = 0;

            if (b->type == BUILDING_THEATER)
                b->data.entertainment.days1 = 32;
            else {
                b->data.entertainment.days2 = 32;
            }
            break;
        case FIGURE_GLADIATOR:
            if (b->type == BUILDING_AMPHITHEATER)
                b->data.entertainment.days1 = 32;
            else {
                b->data.entertainment.days2 = 32;
            }
            break;
        case FIGURE_LION_TAMER:
        case FIGURE_CHARIOTEER:
            b->data.entertainment.days1 = 32;
            break;
    }
}
void figure::entertainer_update_image() {
    int dir = figure_image_normalize_direction(direction < 8 ? direction : previous_tile_direction);

    if (type == FIGURE_CHARIOTEER) {
        cart_image_id = 0;
        if (action_state == FIGURE_ACTION_150_ATTACK ||
            action_state == FIGURE_ACTION_149_CORPSE) {
            sprite_image_id = image_id_from_group(GROUP_FIGURE_CHARIOTEER) + dir;
        } else
            sprite_image_id = image_id_from_group(GROUP_FIGURE_CHARIOTEER) + dir + 8 * anim_frame;
        return;
    }
    int image_id;
    if (type == FIGURE_ACTOR)
        image_id = image_id_from_group(GROUP_FIGURE_ACTOR);
    else if (type == FIGURE_GLADIATOR)
        image_id = image_id_from_group(GROUP_FIGURE_GLADIATOR);
    else if (type == FIGURE_LION_TAMER) {
        image_id = image_id_from_group(GROUP_FIGURE_LION_TAMER);
        if (wait_ticks_missile >= 96)
            image_id = image_id_from_group(GROUP_FIGURE_LION_TAMER_WHIP);
        cart_image_id = image_id_from_group(GROUP_FIGURE_LION);
    } else
        return;
    if (action_state == FIGURE_ACTION_150_ATTACK) {
        if (type == FIGURE_GLADIATOR)
            image_id = image_id + 104 + dir + 8 * (anim_frame / 2);
        else
            image_id = image_id + dir;
    } else if (action_state == FIGURE_ACTION_149_CORPSE) {
        image_id = image_id + 96 + figure_image_corpse_offset();
        cart_image_id = 0;
    } else
        image_id = image_id + dir + 8 * anim_frame;
    if (cart_image_id) {
        cart_image_id += dir + 8 * anim_frame;
        figure_image_set_cart_offset(dir);
    }
}
void figure::entertainer_action() {
//    building *b = building_get(building_id);
//    cart_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER_CART);
//    terrain_usage = TERRAIN_USAGE_ROADS;
//    use_cross_country = 0;
//    max_roam_length = 512;
//    figure_image_increase_offset(12);
    wait_ticks_missile++;
    if (wait_ticks_missile >= 120)
        wait_ticks_missile = 0;

    building *b = building_get(building_id);
    if (scenario_gladiator_revolt_is_in_progress() && type == FIGURE_GLADIATOR) {
        if (action_state == FIGURE_ACTION_92_ENTERTAINER_GOING_TO_VENUE ||
            action_state == FIGURE_ACTION_94_ENTERTAINER_ROAMING ||
            action_state == FIGURE_ACTION_95_ENTERTAINER_RETURNING) {
            type = FIGURE_ENEMY54_GLADIATOR;
            route_remove();
            roam_length = 0;
            action_state = FIGURE_ACTION_158_NATIVE_CREATED;
            return;
        }
    }
    int speed_factor = type == FIGURE_CHARIOTEER ? 2 : 1;
    switch (action_state) {
        case FIGURE_ACTION_150_ATTACK:
            figure_combat_handle_attack();
//            figure_image_increase_offset(32);
            break;
        case FIGURE_ACTION_149_CORPSE:
            figure_combat_handle_corpse();
            break;
        case FIGURE_ACTION_90_ENTERTAINER_AT_SCHOOL_CREATED:
            is_ghost = 1;
            anim_frame = 0;
            wait_ticks_missile = 0;
            wait_ticks--;
            if (wait_ticks <= 0) {
                int x_road, y_road;
                if (map_closest_road_within_radius(b->x, b->y, b->size, 2, &x_road, &y_road)) {
                    action_state = FIGURE_ACTION_91_ENTERTAINER_EXITING_SCHOOL;
                    set_cross_country_destination(x_road, y_road);
                    roam_length = 0;
                } else
                    state = FIGURE_STATE_DEAD;
            }
            break;
        case FIGURE_ACTION_91_ENTERTAINER_EXITING_SCHOOL:
            use_cross_country = 1;
            is_ghost = 1;
            if (move_ticks_cross_country(1) == 1) {
                int dst_building_id = 0;
                switch (type) {
                    case FIGURE_ACTOR:
                        dst_building_id = determine_destination(tile_x, tile_y, BUILDING_THEATER, BUILDING_AMPHITHEATER);
                        break;
                    case FIGURE_GLADIATOR:
                        dst_building_id = determine_destination(tile_x, tile_y, BUILDING_AMPHITHEATER, BUILDING_COLOSSEUM);
                        break;
                    case FIGURE_LION_TAMER:
                        dst_building_id = determine_destination(tile_x, tile_y, BUILDING_COLOSSEUM, 0);
                        break;
                    case FIGURE_CHARIOTEER:
                        dst_building_id = determine_destination(tile_x, tile_y, BUILDING_HIPPODROME, 0);
                        break;
                }
                if (dst_building_id) {
                    building *b_dst = building_get(dst_building_id);
                    int x_road, y_road;
                    if (map_closest_road_within_radius(b_dst->x, b_dst->y, b_dst->size, 2, &x_road, &y_road)) {
                        destination_building_id = dst_building_id;
                        action_state = FIGURE_ACTION_92_ENTERTAINER_GOING_TO_VENUE;
                        destination_x = x_road;
                        destination_y = y_road;
                        roam_length = 0;
                    } else
                        state = FIGURE_STATE_DEAD;
                } else
                    state = FIGURE_STATE_DEAD;
            }
            is_ghost = 1;
            break;
        case FIGURE_ACTION_92_ENTERTAINER_GOING_TO_VENUE:
            is_ghost = 0;
            roam_length++;
            if (roam_length >= 3200)
                state = FIGURE_STATE_DEAD;

            move_ticks(speed_factor);
            if (direction == DIR_FIGURE_AT_DESTINATION) {
                entertainer_update_shows();
                state = FIGURE_STATE_DEAD;
            } else if (direction == DIR_FIGURE_REROUTE)
                route_remove();
            else if (direction == DIR_FIGURE_LOST)
                state = FIGURE_STATE_DEAD;
            break;
        case ACTION_10_DELIVERING_FOOD:
        case FIGURE_ACTION_94_ENTERTAINER_ROAMING:
            is_ghost = 0;
            roam_length++;
            if (roam_length >= max_roam_length) {
                int x_road, y_road;
                if (map_closest_road_within_radius(b->x, b->y, b->size, 2, &x_road, &y_road)) {
                    action_state = FIGURE_ACTION_95_ENTERTAINER_RETURNING;
                    destination_x = x_road;
                    destination_y = y_road;
                } else
                    state = FIGURE_STATE_DEAD;
            }
            roam_ticks(speed_factor);
            break;
        case ACTION_11_RETURNING_EMPTY:
        case FIGURE_ACTION_95_ENTERTAINER_RETURNING:
            move_ticks(speed_factor);
            if (direction == DIR_FIGURE_AT_DESTINATION || direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_LOST) {
                state = FIGURE_STATE_DEAD;
            }
            break;
    }
    entertainer_update_image();
}
