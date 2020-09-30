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

void figure::engineer_action() {
    building *b = building_get(building_id);

    terrain_usage = TERRAIN_USAGE_ROADS;
    use_cross_country = 0;
    max_roam_length = 640;
    if (b->state != BUILDING_STATE_IN_USE || b->figure_id != id)
        state = FIGURE_STATE_DEAD;

    figure_image_increase_offset(12);

    switch (action_state) {
        case FIGURE_ACTION_150_ATTACK:
            figure_combat_handle_attack();
            break;
        case FIGURE_ACTION_149_CORPSE:
            figure_combat_handle_corpse();
            break;
        case FIGURE_ACTION_60_ENGINEER_CREATED:
            is_ghost = 1;
            image_offset = 0;
            wait_ticks--;
            if (wait_ticks <= 0) {
                int x_road, y_road;
                if (map_closest_road_within_radius(b->x, b->y, b->size, 2, &x_road, &y_road)) {
                    action_state = FIGURE_ACTION_61_ENGINEER_ENTERING_EXITING;
                    set_cross_country_destination(x_road, y_road);
                    roam_length = 0;
                } else {
                    state = FIGURE_STATE_DEAD;
                }
            }
            break;
        case FIGURE_ACTION_61_ENGINEER_ENTERING_EXITING:
            use_cross_country = 1;
            is_ghost = 1;
            if (move_ticks_cross_country(1) == 1) {
                if (map_building_at(grid_offset) == building_id) {
                    // returned to own building
                    state = FIGURE_STATE_DEAD;
                } else {
                    action_state = FIGURE_ACTION_62_ENGINEER_ROAMING;
                    init_roaming();
                    roam_length = 0;
                }
            }
            break;
        case FIGURE_ACTION_62_ENGINEER_ROAMING:
            is_ghost = 0;
            roam_length++;
            if (roam_length >= max_roam_length) {
                int x_road, y_road;
                if (map_closest_road_within_radius(b->x, b->y, b->size, 2, &x_road, &y_road)) {
                    action_state = FIGURE_ACTION_63_ENGINEER_RETURNING;
                    destination_x = x_road;
                    destination_y = y_road;
                } else {
                    state = FIGURE_STATE_DEAD;
                }
            }
            roam_ticks(1);
            break;
        case FIGURE_ACTION_63_ENGINEER_RETURNING:
            move_ticks(1);
            if (direction == DIR_FIGURE_AT_DESTINATION) {
                action_state = FIGURE_ACTION_61_ENGINEER_ENTERING_EXITING;
                set_cross_country_destination(b->x, b->y);
                roam_length = 0;
            } else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_LOST)
                state = FIGURE_STATE_DEAD;

            break;
    }
    figure_image_update(image_id_from_group(GROUP_FIGURE_ENGINEER));
}

static int get_nearest_enemy(int x, int y, int *distance) {
    int min_enemy_id = 0;
    int min_dist = 10000;
    for (int i = 1; i < MAX_FIGURES[GAME_ENV]; i++) {
        figure *f = figure_get(i);
        if (f->state != FIGURE_STATE_ALIVE || f->targeted_by_figure_id)
            continue;

        int dist;
        if (f->type == FIGURE_RIOTER || f->type == FIGURE_ENEMY54_GLADIATOR)
            dist = calc_maximum_distance(x, y, x, y);
        else if (f->type == FIGURE_INDIGENOUS_NATIVE && f->action_state == FIGURE_ACTION_159_NATIVE_ATTACKING)
            dist = calc_maximum_distance(x, y, x, y);
        else if (f->is_enemy())
            dist = 3 * calc_maximum_distance(x, y, x, y);
        else if (f->type == FIGURE_WOLF)
            dist = 4 * calc_maximum_distance(x, y, x, y);
        else
            continue;
        if (dist < min_dist) {
            min_dist = dist;
            min_enemy_id = i;
        }
    }
    *distance = min_dist;
    return min_enemy_id;
}
int figure::fight_enemy() {
    if (!city_figures_has_security_breach() && enemy_army_total_enemy_formations() <= 0)
        return 0;

    switch (action_state) {
        case FIGURE_ACTION_150_ATTACK:
        case FIGURE_ACTION_149_CORPSE:
        case FIGURE_ACTION_70_PREFECT_CREATED:
        case FIGURE_ACTION_71_PREFECT_ENTERING_EXITING:
        case FIGURE_ACTION_74_PREFECT_GOING_TO_FIRE:
        case FIGURE_ACTION_75_PREFECT_AT_FIRE:
        case FIGURE_ACTION_76_PREFECT_GOING_TO_ENEMY:
        case FIGURE_ACTION_77_PREFECT_AT_ENEMY:
            return 0;
    }
    wait_ticks_next_target++;
    if (wait_ticks_next_target < 10)
        return 0;

    wait_ticks_next_target = 0;
    int distance;
    int enemy_id = get_nearest_enemy(x, y, &distance);
    if (enemy_id > 0 && distance <= 30) {
        figure *enemy = figure_get(enemy_id);
        wait_ticks_next_target = 0;
        action_state = FIGURE_ACTION_76_PREFECT_GOING_TO_ENEMY;
        destination_x = enemy->x;
        destination_y = enemy->y;
        target_figure_id = enemy_id;
        enemy->targeted_by_figure_id = id;
        target_figure_created_sequence = enemy->created_sequence;
        route_remove();
        return 1;
    }
    return 0;
}
int figure::fight_fire() {
    if (building_list_burning_size() <= 0)
        return 0;

    switch (action_state) {
        case FIGURE_ACTION_150_ATTACK:
        case FIGURE_ACTION_149_CORPSE:
        case FIGURE_ACTION_70_PREFECT_CREATED:
        case FIGURE_ACTION_71_PREFECT_ENTERING_EXITING:
        case FIGURE_ACTION_74_PREFECT_GOING_TO_FIRE:
        case FIGURE_ACTION_75_PREFECT_AT_FIRE:
        case FIGURE_ACTION_76_PREFECT_GOING_TO_ENEMY:
        case FIGURE_ACTION_77_PREFECT_AT_ENEMY:
            return 0;
    }
    wait_ticks_missile++;
    if (wait_ticks_missile < 20)
        return 0;

    int distance;
    int ruin_id = building_maintenance_get_closest_burning_ruin(x, y, &distance);
    if (ruin_id > 0 && distance <= 25) {
        building *ruin = building_get(ruin_id);
        wait_ticks_missile = 0;
        action_state = FIGURE_ACTION_74_PREFECT_GOING_TO_FIRE;
        destination_x = ruin->road_access_x;
        destination_y = ruin->road_access_y;
        destination_building_id = ruin_id;
        route_remove();
        ruin->figure_id4 = id;
        return 1;
    }
    return 0;
}
void figure::extinguish_fire() {
    building *burn = building_get(destination_building_id);
    int distance = calc_maximum_distance(x, y, burn->x, burn->y);
    if ((burn->state == BUILDING_STATE_IN_USE || burn->state == BUILDING_STATE_MOTHBALLED) &&
        burn->type == BUILDING_BURNING_RUIN && distance < 2) {
        burn->fire_duration = 32;
        sound_effect_play(SOUND_EFFECT_FIRE_SPLASH);
    } else {
        wait_ticks = 1;
    }
    attack_direction = calc_general_direction(x, y, burn->x, burn->y);
    if (attack_direction >= 8)
        attack_direction = 0;

    wait_ticks--;
    if (wait_ticks <= 0) {
        wait_ticks_missile = 20;
        if (!fight_fire()) {
            building *b = building_get(building_id);
            int x_road, y_road;
            if (map_closest_road_within_radius(b->x, b->y, b->size, 2, &x_road, &y_road)) {
                action_state = FIGURE_ACTION_73_PREFECT_RETURNING;
                destination_x = x_road;
                destination_y = y_road;
                route_remove();
            } else
                state = FIGURE_STATE_DEAD;
        }
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

void figure::prefect_action() {
    building *b = building_get(building_id);

    terrain_usage = TERRAIN_USAGE_ROADS;
    use_cross_country = 0;
    max_roam_length = 640;
    if (b->state != BUILDING_STATE_IN_USE || b->figure_id != id)
        state = FIGURE_STATE_DEAD;
    figure_image_increase_offset(12);

    // special actions
    if (!fight_enemy())
        fight_fire();

    switch (action_state) {
        case FIGURE_ACTION_150_ATTACK:
            figure_combat_handle_attack();
            break;
        case FIGURE_ACTION_149_CORPSE:
            figure_combat_handle_corpse();
            break;
        case FIGURE_ACTION_70_PREFECT_CREATED:
            is_ghost = 1;
            image_offset = 0;
            wait_ticks--;
            if (wait_ticks <= 0) {
                int x_road, y_road;
                if (map_closest_road_within_radius(b->x, b->y, b->size, 2, &x_road, &y_road)) {
                    action_state = FIGURE_ACTION_71_PREFECT_ENTERING_EXITING;
                    set_cross_country_destination(x_road, y_road);
                    roam_length = 0;
                } else
                    state = FIGURE_STATE_DEAD;
            }
            break;
        case FIGURE_ACTION_71_PREFECT_ENTERING_EXITING:
            use_cross_country = 1;
            is_ghost = 1;
            if (move_ticks_cross_country(1) == 1) {
                if (map_building_at(grid_offset) == building_id) {
                    // returned to own building
                    state = FIGURE_STATE_DEAD;
                } else {
                    action_state = FIGURE_ACTION_72_PREFECT_ROAMING;
                    init_roaming();
                    roam_length = 0;
                }
            }
            break;
        case FIGURE_ACTION_72_PREFECT_ROAMING:
            is_ghost = 0;
            roam_length++;
            if (roam_length >= max_roam_length) {
                int x_road, y_road;
                if (map_closest_road_within_radius(b->x, b->y, b->size, 2, &x_road, &y_road)) {
                    action_state = FIGURE_ACTION_73_PREFECT_RETURNING;
                    destination_x = x_road;
                    destination_y = y_road;
                    route_remove();
                } else
                    state = FIGURE_STATE_DEAD;
            }
            roam_ticks(1);
            break;
        case FIGURE_ACTION_73_PREFECT_RETURNING:
            move_ticks(1);
            if (direction == DIR_FIGURE_AT_DESTINATION) {
                action_state = FIGURE_ACTION_71_PREFECT_ENTERING_EXITING;
                set_cross_country_destination(b->x, b->y);
                roam_length = 0;
            } else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_LOST)
                state = FIGURE_STATE_DEAD;
            break;
        case FIGURE_ACTION_74_PREFECT_GOING_TO_FIRE:
            terrain_usage = TERRAIN_USAGE_ANY;
            move_ticks(1);
            if (direction == DIR_FIGURE_AT_DESTINATION) {
                action_state = FIGURE_ACTION_75_PREFECT_AT_FIRE;
                route_remove();
                roam_length = 0;
                wait_ticks = 50;
            } else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_LOST)
                state = FIGURE_STATE_DEAD;
            break;
        case FIGURE_ACTION_75_PREFECT_AT_FIRE:
            extinguish_fire();
            break;
        case FIGURE_ACTION_76_PREFECT_GOING_TO_ENEMY:
            terrain_usage = TERRAIN_USAGE_ANY;
            if (!target_is_alive()) {
                int x_road, y_road;
                if (map_closest_road_within_radius(b->x, b->y, b->size, 2, &x_road, &y_road)) {
                    action_state = FIGURE_ACTION_73_PREFECT_RETURNING;
                    destination_x = x_road;
                    destination_y = y_road;
                    route_remove();
                    roam_length = 0;
                } else
                    state = FIGURE_STATE_DEAD;
            }
            move_ticks(1);
            if (direction == DIR_FIGURE_AT_DESTINATION) {
                figure *target = figure_get(target_figure_id);
                destination_x = target->x;
                destination_y = target->y;
                route_remove();
            } else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_LOST)
                state = FIGURE_STATE_DEAD;
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
        case FIGURE_ACTION_74_PREFECT_GOING_TO_FIRE:
            image_id = image_id_from_group(GROUP_FIGURE_PREFECT_WITH_BUCKET) + dir + 8 * image_offset;
            break;
        case FIGURE_ACTION_75_PREFECT_AT_FIRE:
            image_id = image_id_from_group(GROUP_FIGURE_PREFECT_WITH_BUCKET) + dir + 96 + 8 * (image_offset / 2);
            break;
        case FIGURE_ACTION_150_ATTACK:
            if (attack_image_offset >= 12) {
                image_id = image_id_from_group(GROUP_FIGURE_PREFECT) + 104 + dir + 8 * ((attack_image_offset - 12) / 2);
            } else
                image_id = image_id_from_group(GROUP_FIGURE_PREFECT) + 104 + dir;
            break;
        case FIGURE_ACTION_149_CORPSE:
            image_id = image_id_from_group(GROUP_FIGURE_PREFECT) + 96 + figure_image_corpse_offset();
            break;
        default:
            image_id = image_id_from_group(GROUP_FIGURE_PREFECT) + dir + 8 * image_offset;
            break;
    }
}
void figure::worker_action() {
    terrain_usage = TERRAIN_USAGE_ROADS;
    use_cross_country = 0;
    max_roam_length = 384;
    building *b = building_get(building_id);
    if (b->state != BUILDING_STATE_IN_USE || b->figure_id != id)
        state = FIGURE_STATE_DEAD;

}
