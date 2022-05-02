#include <core/config.h>
#include "maintenance.h"

#include "building/building.h"
#include "building/list.h"
#include "building/maintenance.h"
#include "city/figures.h"
#include "core/calc.h"
#include "core/image.h"
#include "figure/combat.h"
#include "figure/enemy_army.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "map/building.h"
#include "map/road_access.h"
#include "sound/effect.h"

#include "core/game_environment.h"

#include "figure/properties.h"

enum {
    NEARBY_ANY,
    NEARBY_ANIMAL,
    NEARBY_HOSTILE
};

int figure::is_nearby(int category, int *distance, int max_distance, bool gang_on) {
    int figure_id = 0;
    int lowest_distance = max_distance;
    for (int i = 1; i < MAX_FIGURES[GAME_ENV]; i++) {
        figure *f = figure_get(i);
        if (f->is_dead())
            continue;
        if (!gang_on && f->targeted_by_figure_id)
            continue;

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
                if (f->is_enemy() || f->type == FIGURE_RIOTER || f->is_attacking_native())
                    category_check = true;
                break;
        }

        // pass on to inner distance check
        if (category_check) {
            int dist = calc_maximum_distance(tile.x(), tile.y(), f->tile.x(), f->tile.y());
            if (dist <= max_distance) {
                if (f->targeted_by_figure_id)
                    dist *= 2; // penalty
                if (category == NEARBY_HOSTILE) {
                    if (f->type == FIGURE_RIOTER || f->type == FIGURE_ENEMY54_GLADIATOR)
                        dist = calc_maximum_distance(tile.x(), tile.y(), f->tile.x(), f->tile.y());
                    else if (f->type == FIGURE_INDIGENOUS_NATIVE && f->action_state == FIGURE_ACTION_159_NATIVE_ATTACKING)
                        dist = calc_maximum_distance(tile.x(), tile.y(), f->tile.x(), f->tile.y());
                    else if (f->is_enemy())
                        dist = 3 * calc_maximum_distance(tile.x(), tile.y(), f->tile.x(), f->tile.y());
                    else if (f->type == FIGURE_WOLF)
                        dist = 4 * calc_maximum_distance(tile.x(), tile.y(), f->tile.x(), f->tile.y());
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
//static int get_nearest_enemy(int x, int y, int *distance) {
//    int min_enemy_id = 0;
//    int min_dist = 10000;
//    for (int i = 1; i < MAX_FIGURES[GAME_ENV]; i++) {
//        figure *f = figure_get(i);
//        if (f->state != FIGURE_STATE_ALIVE || f->targeted_by_figure_id)
//            continue;
//
//        int dist;
//        if (f->type == FIGURE_RIOTER || f->type == FIGURE_ENEMY54_GLADIATOR)
//            dist = calc_maximum_distance(x, y, f->x, f->y);
//        else if (f->type == FIGURE_INDIGENOUS_NATIVE && f->action_state == FIGURE_ACTION_159_NATIVE_ATTACKING)
//            dist = calc_maximum_distance(x, y, f->x, f->y);
//        else if (f->is_enemy())
//            dist = 3 * calc_maximum_distance(x, y, f->x, f->y);
//        else if (f->type == FIGURE_WOLF)
//            dist = 4 * calc_maximum_distance(x, y, f->x, f->y);
//        else
//            continue;
//        if (dist < min_dist) {
//            min_dist = dist;
//            min_enemy_id = i;
//        }
//    }
//    *distance = min_dist;
//    return min_enemy_id;
//}
bool figure::fight_enemy(int category, int max_distance) {
    if (!city_figures_has_security_breach() && enemy_army_total_enemy_formations() <= 0)
        return false;

    switch (action_state) {
        case FIGURE_ACTION_150_ATTACK:
        case FIGURE_ACTION_149_CORPSE:
        case FIGURE_ACTION_70_PREFECT_CREATED:
        case FIGURE_ACTION_71_PREFECT_ENTERING_EXITING:
        case FIGURE_ACTION_74_PREFECT_GOING_TO_FIRE:
        case FIGURE_ACTION_75_PREFECT_AT_FIRE:
        case FIGURE_ACTION_76_PREFECT_GOING_TO_ENEMY:
        case FIGURE_ACTION_77_PREFECT_AT_ENEMY:
            return false;
    }
    wait_ticks_next_target++;
    if (wait_ticks_next_target < 10)
        return false;

    wait_ticks_next_target = 0;
    int distance;
    int enemy_id = is_nearby(2, &distance);
    if (enemy_id > 0 && distance <= max_distance) {
        figure *enemy = figure_get(enemy_id);
        wait_ticks_next_target = 0;
        action_state = FIGURE_ACTION_76_PREFECT_GOING_TO_ENEMY;
        destination_tile = enemy->tile;
//        destination_tile.x() = enemy->tile.x();
//        destination_tile.y() = enemy->tile.y();
        target_figure_id = enemy_id;
        enemy->targeted_by_figure_id = id;
        target_figure_created_sequence = enemy->created_sequence;
        route_remove();
        return true;
    }
    return false;
}
bool figure::fight_fire() {
    if (building_list_burning_size() <= 0)
        return false;

    switch (action_state) {
        case FIGURE_ACTION_150_ATTACK:
        case FIGURE_ACTION_149_CORPSE:
        case FIGURE_ACTION_70_PREFECT_CREATED:
        case FIGURE_ACTION_71_PREFECT_ENTERING_EXITING:
        case FIGURE_ACTION_74_PREFECT_GOING_TO_FIRE:
        case FIGURE_ACTION_75_PREFECT_AT_FIRE:
        case FIGURE_ACTION_76_PREFECT_GOING_TO_ENEMY:
        case FIGURE_ACTION_77_PREFECT_AT_ENEMY:
            return false;
    }
    wait_ticks_missile++;
    if (wait_ticks_missile < 20)
        return false;

    int distance;
    int ruin_id = building_maintenance_get_closest_burning_ruin(tile.x(), tile.y(), &distance);
    if (ruin_id > 0 && distance <= 25) {
        building *ruin = building_get(ruin_id);
        wait_ticks_missile = 0;
        advance_action(FIGURE_ACTION_74_PREFECT_GOING_TO_FIRE);
        destination_tile = ruin->road_access;
//        destination_tile.x() = ruin->road_access.x();
//        destination_tile.y() = ruin->road_access.y();
        set_destination(ruin_id);
        route_remove();
        ruin->set_figure(3, id);
        return true;
    }
    return false;
}
void figure::extinguish_fire() {
    building *burn = destination();
    int distance = calc_maximum_distance(tile.x(), tile.y(), burn->tile.x(), burn->tile.y());
    if ((burn->state == BUILDING_STATE_VALID || burn->state == BUILDING_STATE_MOTHBALLED) &&
        burn->type == BUILDING_BURNING_RUIN && distance < 2) {
        burn->fire_duration = 32;
        sound_effect_play(SOUND_EFFECT_FIRE_SPLASH);
    } else
        wait_ticks = 1;
    attack_direction = calc_general_direction(tile.x(), tile.y(), burn->tile.x(), burn->tile.y());
    if (attack_direction >= 8)
        attack_direction = 0;

    wait_ticks--;
    if (wait_ticks <= 0) {
        wait_ticks_missile = 20;
        advance_action(FIGURE_ACTION_73_PREFECT_RETURNING);
        if (!fight_fire()) // in Pharaoh, firemen teleport back instantly.
            poof();
    }
}
int figure::target_is_alive() {
    if (target_figure_id <= 0)
        return 0;

    figure *target = figure_get(target_figure_id);
    if (!target->is_dead() && target->created_sequence == target_figure_created_sequence)
        return 1;

    return 0;
}

void figure::engineer_action() {
//    building *b = building_get(building_id);
    switch (action_state) {
        case FIGURE_ACTION_60_ENGINEER_CREATED:
            advance_action(ACTION_10_GOING);
            break;
        case FIGURE_ACTION_61_ENGINEER_ENTERING_EXITING:
        case 9:
            do_enterbuilding(true, home());
            break;
        case ACTION_10_GOING:
        case FIGURE_ACTION_62_ENGINEER_ROAMING:
            do_roam(TERRAIN_USAGE_ROADS, ACTION_11_RETURNING_FROM_PATROL);
            break;
        case ACTION_11_RETURNING_FROM_PATROL:
        case FIGURE_ACTION_63_ENGINEER_RETURNING:
            do_returnhome(TERRAIN_USAGE_ROADS, FIGURE_ACTION_61_ENGINEER_ENTERING_EXITING);
            break;
    }
}
void figure::prefect_action() { // doubles as fireman! not as policeman!!!
    if (GAME_ENV == ENGINE_ENV_C3) {
        if (!fight_enemy(2, 22))
            fight_fire();
    } else
        fight_fire();

    building *b = home();
    switch (action_state) {
        case FIGURE_ACTION_70_PREFECT_CREATED:
            advance_action(ACTION_10_GOING);
            break;
        case ACTION_11_RETURNING_FROM_PATROL:
        case FIGURE_ACTION_73_PREFECT_RETURNING:
            do_returnhome(TERRAIN_USAGE_ROADS);
            break;
        case 9:
        case FIGURE_ACTION_71_PREFECT_ENTERING_EXITING:
            do_enterbuilding(true, home());
            break;
        case ACTION_10_GOING:
        case FIGURE_ACTION_72_PREFECT_ROAMING:
            do_roam(TERRAIN_USAGE_ROADS, ACTION_11_RETURNING_FROM_PATROL);
            break;
        case FIGURE_ACTION_74_PREFECT_GOING_TO_FIRE:
        case 12:
            if (do_goto(destination_tile.x(), destination_tile.y(), TERRAIN_USAGE_ENEMY, FIGURE_ACTION_75_PREFECT_AT_FIRE))
                wait_ticks = 50;
            break;
        case FIGURE_ACTION_75_PREFECT_AT_FIRE:
        case 13:
            extinguish_fire();
            break;
        case FIGURE_ACTION_76_PREFECT_GOING_TO_ENEMY:
            terrain_usage = TERRAIN_USAGE_ANY;
            if (!target_is_alive()) {
                int x_road, y_road;
                if (map_closest_road_within_radius(b->tile.x(), b->tile.y(), b->size, 2, &x_road, &y_road)) {
                    action_state = FIGURE_ACTION_73_PREFECT_RETURNING;
                    destination_tile.set(x_road, y_road);
//                    destination_tile.x() = x_road;
//                    destination_tile.y() = y_road;
                    route_remove();
                    roam_length = 0;
                } else
                    poof();
            }
            move_ticks(1);
            if (direction == DIR_FIGURE_NONE) {
                figure *target = figure_get(target_figure_id);
                destination_tile = target->tile;
//                destination_tile.x() = target->tile.x();
//                destination_tile.y() = target->tile.y();
                route_remove();
            } else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_CAN_NOT_REACH)
                poof();
            break;
    }

    switch (action_state) {
        default:
            break;
        case FIGURE_ACTION_75_PREFECT_AT_FIRE:
        case 13:
            direction = attack_direction;
            image_set_animation(GROUP_FIGURE_PREFECT, 104, 36);
            break;
    }
}
void figure::policeman_action() {
    fight_enemy(2, 22);

    building *b = home();
    switch (action_state) {
        case FIGURE_ACTION_70_PREFECT_CREATED:
//            is_ghost = true;
            anim_frame = 0;
            wait_ticks--;
            if (wait_ticks <= 0) {
                int x_road, y_road;
                if (map_closest_road_within_radius(b->tile.x(), b->tile.y(), b->size, 2, &x_road, &y_road)) {
                    action_state = FIGURE_ACTION_71_PREFECT_ENTERING_EXITING;
                    set_cross_country_destination(x_road, y_road);
                    roam_length = 0;
                } else
                    poof();
            }
            break;
        case 9:
        case FIGURE_ACTION_71_PREFECT_ENTERING_EXITING:
            use_cross_country = true;
//            is_ghost = true;
            if (move_ticks_cross_country(1) == 1) {
                if (map_building_at(tile.grid_offset()) == homeID()) {
                    // returned to own building
                    poof();
                } else {
                    action_state = FIGURE_ACTION_72_PREFECT_ROAMING;
                    init_roaming_from_building(0);
                    roam_length = 0;
                }
            }
            break;
        case ACTION_10_DELIVERING_FOOD:
        case FIGURE_ACTION_72_PREFECT_ROAMING:
//            is_ghost = false;
            roam_length++;
            if (roam_length >= max_roam_length) {
                int x_road, y_road;
                if (map_closest_road_within_radius(b->tile.x(), b->tile.y(), b->size, 2, &x_road, &y_road)) {
                    action_state = FIGURE_ACTION_73_PREFECT_RETURNING;
                    destination_tile.set(x_road, y_road);
//                    destination_tile.x() = x_road;
//                    destination_tile.y() = y_road;
                    route_remove();
                } else
                    poof();
            }
            roam_ticks(1);
            break;
        case ACTION_11_RETURNING_EMPTY:
        case FIGURE_ACTION_73_PREFECT_RETURNING:
            move_ticks(1);
            if (direction == DIR_FIGURE_NONE) {
                action_state = FIGURE_ACTION_71_PREFECT_ENTERING_EXITING;
                set_cross_country_destination(b->tile.x(), b->tile.y());
                roam_length = 0;
            } else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_CAN_NOT_REACH)
                poof();
            break;
        case FIGURE_ACTION_76_PREFECT_GOING_TO_ENEMY:
            terrain_usage = TERRAIN_USAGE_ANY;
            if (!target_is_alive()) {
                int x_road, y_road;
                if (map_closest_road_within_radius(b->tile.x(), b->tile.y(), b->size, 2, &x_road, &y_road)) {
                    action_state = FIGURE_ACTION_73_PREFECT_RETURNING;
                    destination_tile.set(x_road, y_road);
//                    destination_tile.x() = x_road;
//                    destination_tile.y() = y_road;
                    route_remove();
                    roam_length = 0;
                } else
                    poof();
            }
            move_ticks(1);
            if (direction == DIR_FIGURE_NONE) {
                figure *target = figure_get(target_figure_id);
                destination_tile = target->tile;
//                destination_tile.x() = target->tile.x();
//                destination_tile.y() = target->tile.y();
                route_remove();
            } else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_CAN_NOT_REACH)
                poof();
            break;
    }
    // graphic id
    int dir;
    if (action_state == FIGURE_ACTION_75_PREFECT_AT_FIRE ||
        action_state == FIGURE_ACTION_150_ATTACK) {
        dir = attack_direction;
    } else if (direction < 8)
        dir = direction;
    else
        dir = previous_tile_direction;
    dir = figure_image_normalize_direction(dir);
    switch (action_state) {
        case FIGURE_ACTION_150_ATTACK:
            if (attack_image_offset >= 12) {
                sprite_image_id = image_id_from_group(GROUP_FIGURE_POLICEMAN) + 104 + dir + 8 * ((attack_image_offset - 12) / 2);
            } else
                sprite_image_id = image_id_from_group(GROUP_FIGURE_POLICEMAN) + 104 + dir;
            break;
        case FIGURE_ACTION_149_CORPSE:
            sprite_image_id = image_id_from_group(GROUP_FIGURE_POLICEMAN) + 96 + figure_image_corpse_offset();
            break;
        default:
            sprite_image_id = image_id_from_group(GROUP_FIGURE_POLICEMAN) + dir + 8 * anim_frame;
            break;
    }
}
void figure::magistrate_action() {
    switch (action_state) {
        case FIGURE_ACTION_70_PREFECT_CREATED:
            advance_action(ACTION_10_GOING);
            break;
        case FIGURE_ACTION_71_PREFECT_ENTERING_EXITING:
            do_enterbuilding(true, home());
            break;
        case FIGURE_ACTION_72_PREFECT_ROAMING:
            do_roam(TERRAIN_USAGE_ROADS, ACTION_11_RETURNING_FROM_PATROL);
            break;
        case FIGURE_ACTION_73_PREFECT_RETURNING:
            do_returnhome(TERRAIN_USAGE_ROADS, FIGURE_ACTION_61_ENGINEER_ENTERING_EXITING);
            break;
    }
}
void figure::water_carrier_action() {
    // TODO
//    if (config_get(CONFIG_GP_CH_WATER_CARRIER_FIREFIGHT))
//        if (fight_fire())
//            image_set_animation(GROUP_FIGURE_PREFECT);

    building *b = home();
    switch (action_state) {
        case ACTION_10_GOING:
        case FIGURE_ACTION_72_PREFECT_ROAMING:
            do_roam(TERRAIN_USAGE_ROADS, ACTION_2_ROAMERS_RETURNING);
            break;
        case ACTION_11_RETURNING_FROM_PATROL:
        case FIGURE_ACTION_73_PREFECT_RETURNING:
            do_returnhome(TERRAIN_USAGE_PREFER_ROADS);
            break;
//        case FIGURE_ACTION_74_PREFECT_GOING_TO_FIRE:
//            if (do_goto(destination_x, destination_y, TERRAIN_USAGE_ENEMY, FIGURE_ACTION_75_PREFECT_AT_FIRE))
//                wait_ticks = 50;
//            break;
//        case FIGURE_ACTION_75_PREFECT_AT_FIRE:
//            extinguish_fire();
//            direction = attack_direction;
//            image_set_animation(GROUP_FIGURE_PREFECT, 104, 36);
//            break;
    }
}

// Same as policeman, but can't fight
//void figure::magistrate_action() {
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

#include "building/industry.h"

void figure::worker_action() {
    terrain_usage = TERRAIN_USAGE_ROADS;
    use_cross_country = false;
    max_roam_length = 384;
    building *b = home();
    building *b_dest = destination();
    if (b->state != BUILDING_STATE_VALID
        || b_dest->state != BUILDING_STATE_VALID || b_dest->data.industry.worker_id != id)
        poof();
    switch (action_state) {
        case 9:
            break;
        case 10:
            if (do_gotobuilding(destination())) {
                if (building_is_farm(b_dest->type)) {
                    b_dest->num_workers = 10;
                    b_dest->data.industry.worker_id = 0;
                    b_dest->data.industry.labor_state = 2;
                    b_dest->data.industry.labor_days_left = 96;
                } else if (b_dest->type == BUILDING_PYRAMID) {
                    // todo: MONUMENTSSSS
                }
            }
            break;
    }
}
