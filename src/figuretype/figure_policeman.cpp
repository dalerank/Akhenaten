#include "figure/figure.h"

#include "core/calc.h"
#include "grid/road_access.h"
#include "grid/building.h"
#include "figure/image.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"

building* find_most_crime_building(figure *f) {
    //buildings_valid_do([] (building &b) {
    //
    //});

    return nullptr;
}

void figure::policeman_action() {
    policeman_fight_enemy(2, 22);

    building* b = home();
    switch (action_state) {
    case FIGURE_ACTION_70_POLICEMAN_CREATED:
        anim_frame = 0;
        wait_ticks--;
        if (wait_ticks <= 0) {
            tile2i road_tile;
            if (map_closest_road_within_radius(b->tile, b->size, 2, road_tile)) {
                action_state = FIGURE_ACTION_71_POLICEMAN_ENTERING_EXITING;
                set_cross_country_destination(road_tile.x(), road_tile.y());
                roam_length = 0;
            } else {
                poof();
            }
        }
        break;

    case 9:
    case FIGURE_ACTION_71_POLICEMAN_ENTERING_EXITING:
        use_cross_country = true;
        if (move_ticks_cross_country(1) == 1) {
            if (map_building_at(tile.grid_offset()) == homeID()) {
                // returned to own building
                poof();
            } else {
                action_state = FIGURE_ACTION_72_POLICEMAN_ROAMING;
                init_roaming_from_building(0);
                direction = calc_general_direction(tile, destination_tile);
                roam_length = 0;
            }
        }
        break;

    case ACTION_10_DELIVERING_FOOD:
    case FIGURE_ACTION_72_POLICEMAN_ROAMING:
        roam_length++;
        if (roam_length >= max_roam_length) {
            tile2i road_tile;
            if (map_closest_road_within_radius(b->tile, b->size, 2, road_tile)) {
                action_state = FIGURE_ACTION_73_POLICEMAN_RETURNING;
                destination_tile = road_tile;
                route_remove();
            } else {
                poof();
            }
        }
        roam_ticks(1);
        break;

    case ACTION_11_RETURNING_EMPTY:
    case FIGURE_ACTION_73_POLICEMAN_RETURNING:
        move_ticks(1);
        if (direction == DIR_FIGURE_NONE) {
            action_state = FIGURE_ACTION_71_POLICEMAN_ENTERING_EXITING;
            set_cross_country_destination(b->tile.x(), b->tile.y());
            roam_length = 0;
        } else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }
        break;

    case FIGURE_ACTION_76_POLICEMAN_GOING_TO_ENEMY:
        terrain_usage = TERRAIN_USAGE_ANY;
        if (!target_is_alive()) {
            tile2i road_tile;
            if (map_closest_road_within_radius(b->tile, b->size, 2, road_tile)) {
                action_state = FIGURE_ACTION_73_POLICEMAN_RETURNING;
                destination_tile = road_tile;
                route_remove();
                roam_length = 0;
            } else {
                poof();
            }
        }
        move_ticks(1);
        if (direction == DIR_FIGURE_NONE) {
            figure* target = figure_get(target_figure_id);
            destination_tile = target->tile;
            route_remove();
        } else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }
        break;
    }
    // graphic id
    int dir;
    if (action_state == FIGURE_ACTION_150_ATTACK) {
        dir = attack_direction;
    } else if (direction < 8) {
        dir = direction;
    } else {
        dir = previous_tile_direction;
    }

    dir = figure_image_normalize_direction(dir);
    switch (action_state) {
    case FIGURE_ACTION_150_ATTACK:
    if (attack_image_offset >= 12) {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_POLICEMAN) + 104 + dir + 8 * ((attack_image_offset - 12) / 2);
    } else {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_POLICEMAN) + 104 + dir;
    }
    break;

    case FIGURE_ACTION_149_CORPSE:
    sprite_image_id = image_id_from_group(GROUP_FIGURE_POLICEMAN) + 96 + figure_image_corpse_offset();
    break;

    default:
    sprite_image_id = image_id_from_group(GROUP_FIGURE_POLICEMAN) + dir + 8 * anim_frame;
    break;
    }
}