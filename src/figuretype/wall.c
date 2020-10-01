#include "wall.h"

#include "building/building.h"
#include "city/view.h"
#include "core/calc.h"
#include "core/config.h"
#include "core/image.h"
#include "figure/combat.h"
#include "figure/enemy_army.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/properties.h"
#include "figure/route.h"
#include "figuretype/missile.h"
#include "map/figure.h"
#include "map/grid.h"
#include "map/routing_terrain.h"
#include "map/terrain.h"
#include "sound/effect.h"

static const int BALLISTA_FIRING_OFFSETS[] = {
        0, 1, 2, 3, 4, 5, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static const int TOWER_SENTRY_FIRING_OFFSETS[] = {
        0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void figure::ballista_action() {
    building *b = building_get(building_id);
    terrain_usage = TERRAIN_USAGE_WALLS;
    use_cross_country = 0;
    is_ghost = 1;
    height_adjusted_ticks = 10;
    current_height = 45;

    if (b->state != BUILDING_STATE_IN_USE || b->figure_id4 != id)
        state = FIGURE_STATE_DEAD;

    if (b->num_workers <= 0 || b->figure_id <= 0)
        state = FIGURE_STATE_DEAD;

    map_figure_remove();
    switch (city_view_orientation()) {
        case DIR_0_TOP:
            tile_x = b->x;
            tile_y = b->y;
            break;
        case DIR_2_RIGHT:
            tile_x = b->x + 1;
            tile_y = b->y;
            break;
        case DIR_4_BOTTOM:
            tile_x = b->x + 1;
            tile_y = b->y + 1;
            break;
        case DIR_6_LEFT:
            tile_x = b->x;
            tile_y = b->y + 1;
            break;
    }
    grid_offset = map_grid_offset(tile_x, tile_y);
    map_figure_add();

    switch (action_state) {
        case FIGURE_ACTION_149_CORPSE:
            state = FIGURE_STATE_DEAD;
            break;
        case FIGURE_ACTION_180_BALLISTA_CREATED:
            wait_ticks++;
            if (wait_ticks > 20) {
                wait_ticks = 0;
                map_point tile;
                if (figure_combat_get_missile_target_for_soldier(this, 15, &tile)) {
                    action_state = FIGURE_ACTION_181_BALLISTA_FIRING;
                    wait_ticks_missile = figure_properties_for_type(type)->missile_delay;
                }
            }
            break;
        case FIGURE_ACTION_181_BALLISTA_FIRING:
            wait_ticks_missile++;
            if (wait_ticks_missile > figure_properties_for_type(type)->missile_delay) {
                map_point tile;
                if (figure_combat_get_missile_target_for_soldier(this, 15, &tile)) {
                    direction = calc_missile_shooter_direction(tile_x, tile_y, tile.x, tile.y);
                    wait_ticks_missile = 0;
                    figure_create_missile(id, tile_x, tile_y, tile.x, tile.y, FIGURE_BOLT);
                    sound_effect_play(SOUND_EFFECT_BALLISTA_SHOOT);
                } else {
                    action_state = FIGURE_ACTION_180_BALLISTA_CREATED;
                }
            }
            break;
    }
    int dir = figure_image_direction();
    if (action_state == FIGURE_ACTION_181_BALLISTA_FIRING) {
        image_id = image_id_from_group(GROUP_FIGURE_BALLISTA) + dir +
                      8 * BALLISTA_FIRING_OFFSETS[wait_ticks_missile / 4];
    } else {
        image_id = image_id_from_group(GROUP_FIGURE_BALLISTA) + dir;
    }
}

void figure::tower_sentry_pick_target() {
    if (enemy_army_total_enemy_formations() <= 0)
        return;
    if (action_state == FIGURE_ACTION_150_ATTACK ||
        action_state == FIGURE_ACTION_149_CORPSE)
        return;
    if (in_building_wait_ticks)
        return;
    wait_ticks_next_target++;
    if (wait_ticks_next_target >= 40) {
        wait_ticks_next_target = 0;
        map_point tile;
        if (figure_combat_get_missile_target_for_soldier(this, 10, &tile)) {
            action_state = FIGURE_ACTION_172_TOWER_SENTRY_FIRING;
            destination_x = tile_x;
            destination_y = tile_y;
        }
    }
}

static int tower_sentry_init_patrol(building *b, int *x_tile, int *y_tile) {
    int dir = b->figure_roam_direction;
    int x = b->x;
    int y = b->y;
    switch (dir) {
        case DIR_0_TOP:
            y -= 8;
            break;
        case DIR_2_RIGHT:
            x += 8;
            break;
        case DIR_4_BOTTOM:
            y += 8;
            break;
        case DIR_6_LEFT:
            x -= 8;
            break;
    }
    map_grid_bound(&x, &y);

    if (map_routing_wall_tile_in_radius(x, y, 6, x_tile, y_tile)) {
        b->figure_roam_direction += 2;
        if (b->figure_roam_direction > 6) b->figure_roam_direction = 0;
        return 1;
    }
    for (int i = 0; i < 4; i++) {
        dir = b->figure_roam_direction;
        b->figure_roam_direction += 2;
        if (b->figure_roam_direction > 6) b->figure_roam_direction = 0;
        x = b->x;
        y = b->y;
        switch (dir) {
            case DIR_0_TOP:
                y -= 3;
                break;
            case DIR_2_RIGHT:
                x += 3;
                break;
            case DIR_4_BOTTOM:
                y += 3;
                break;
            case DIR_6_LEFT:
                x -= 3;
                break;
        }
        map_grid_bound(&x, &y);
        if (map_routing_wall_tile_in_radius(x, y, 6, x_tile, y_tile))
            return 1;

    }
    return 0;
}

void figure::tower_sentry_action() {
    building *b = building_get(building_id);
    terrain_usage = TERRAIN_USAGE_WALLS;
    use_cross_country = 0;
    is_ghost = 1;
    height_adjusted_ticks = 10;
    max_roam_length = 800;
    if (b->state != BUILDING_STATE_IN_USE || b->figure_id != id)
        state = FIGURE_STATE_DEAD;

    figure_image_increase_offset(12);

    tower_sentry_pick_target();
    switch (action_state) {
        case FIGURE_ACTION_150_ATTACK:
            figure_combat_handle_attack();
            break;
        case FIGURE_ACTION_149_CORPSE:
            figure_combat_handle_corpse();
            break;
        case FIGURE_ACTION_170_TOWER_SENTRY_AT_REST:
            image_offset = 0;
            wait_ticks++;
            if (wait_ticks > 40) {
                wait_ticks = 0;
                int x_tile, y_tile;
                if (tower_sentry_init_patrol(b, &x_tile, &y_tile)) {
                    action_state = FIGURE_ACTION_171_TOWER_SENTRY_PATROLLING;
                    destination_x = x_tile;
                    destination_y = y_tile;
                    route_remove();
                }
            }
            break;
        case FIGURE_ACTION_171_TOWER_SENTRY_PATROLLING:
            move_ticks(1);
            if (direction == DIR_FIGURE_AT_DESTINATION) {
                action_state = FIGURE_ACTION_173_TOWER_SENTRY_RETURNING;
                destination_x = source_x;
                destination_y = source_y;
                route_remove();
            } else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_LOST)
                action_state = FIGURE_ACTION_170_TOWER_SENTRY_AT_REST;

            break;
        case FIGURE_ACTION_172_TOWER_SENTRY_FIRING:
            move_ticks_tower_sentry(1);
            wait_ticks_missile++;
            if (wait_ticks_missile > figure_properties_for_type(type)->missile_delay) {
                map_point tile;
                if (figure_combat_get_missile_target_for_soldier(this, 10, &tile)) {
                    direction = calc_missile_shooter_direction(tile_x, tile_y, tile.x, tile.y);
                    wait_ticks_missile = 0;
                    figure_create_missile(id, tile_x, tile_y, tile.x, tile.y, FIGURE_JAVELIN);
                } else {
                    action_state = FIGURE_ACTION_173_TOWER_SENTRY_RETURNING;
                    destination_x = source_x;
                    destination_y = source_y;
                    route_remove();
                }
            }
            break;
        case FIGURE_ACTION_COMMON_RETURN:
        case FIGURE_ACTION_173_TOWER_SENTRY_RETURNING:
            move_ticks(1);
            if (direction == DIR_FIGURE_AT_DESTINATION)
                action_state = FIGURE_ACTION_170_TOWER_SENTRY_AT_REST;
            else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_LOST)
                state = FIGURE_STATE_DEAD;

            break;
        case FIGURE_ACTION_174_TOWER_SENTRY_GOING_TO_TOWER:
            terrain_usage = TERRAIN_USAGE_ROADS;
            if (config_get(CONFIG_GP_CH_TOWER_SENTRIES_GO_OFFROAD))
                terrain_usage = TERRAIN_USAGE_PREFER_ROADS;


            is_ghost = 0;
            height_adjusted_ticks = 0;
            move_ticks(1);
            if (direction == DIR_FIGURE_AT_DESTINATION) {
                map_figure_remove();
                source_x = tile_x = b->x;
                source_y = tile_y = b->y;
                grid_offset = map_grid_offset(tile_x, tile_y);
                map_figure_add();
                action_state = FIGURE_ACTION_170_TOWER_SENTRY_AT_REST;
                route_remove();
            } else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_LOST)
                state = FIGURE_STATE_DEAD;

            break;
    }
    if (map_terrain_is(grid_offset, TERRAIN_WALL))
        current_height = 18;
    else if (map_terrain_is(grid_offset, TERRAIN_GATEHOUSE))
        in_building_wait_ticks = 24;

    if (in_building_wait_ticks) {
        in_building_wait_ticks--;
        height_adjusted_ticks = 0;
    }
    int dir = figure_image_direction();
    if (action_state == FIGURE_ACTION_149_CORPSE) {
        image_id = image_id_from_group(GROUP_FIGURE_TOWER_SENTRY) +
                      136 + figure_image_corpse_offset();
    } else if (action_state == FIGURE_ACTION_172_TOWER_SENTRY_FIRING) {
        image_id = image_id_from_group(GROUP_FIGURE_TOWER_SENTRY) +
                      dir + 96 + 8 * TOWER_SENTRY_FIRING_OFFSETS[wait_ticks_missile / 2];
    } else if (action_state == FIGURE_ACTION_150_ATTACK) {
        int image_id = image_id_from_group(GROUP_FIGURE_TOWER_SENTRY);
        if (attack_image_offset < 16)
            image_id = image_id + 96 + dir;
        else {
            image_id = image_id + 96 + dir + 8 * ((attack_image_offset - 16) / 2);
        }
    } else {
        image_id = image_id_from_group(GROUP_FIGURE_TOWER_SENTRY) +
                      dir + 8 * image_offset;
    }
}

void figure_tower_sentry_reroute(void) {
    for (int i = 1; i < MAX_FIGURES[GAME_ENV]; i++) {
        figure *f = figure_get(i);
        if (f->type != FIGURE_TOWER_SENTRY || map_routing_is_wall_passable(f->grid_offset))
            continue;

        // tower sentry got off wall due to rotation
        int x_tile, y_tile;
        if (map_routing_wall_tile_in_radius(f->tile_x, f->tile_y, 2, &x_tile, &y_tile)) {
            f->route_remove();
            f->progress_on_tile = 0;
            f->map_figure_remove();
            f->previous_tile_x = f->tile_x = x_tile;
            f->previous_tile_y = f->tile_y = y_tile;
            f->cross_country_x = 15 * x_tile;
            f->cross_country_y = 15 * y_tile;
            f->grid_offset = map_grid_offset(x_tile, y_tile);
            f->map_figure_add();
            f->action_state = FIGURE_ACTION_173_TOWER_SENTRY_RETURNING;
            f->destination_x = f->source_x;
            f->destination_y = f->source_y;
        } else {
            // Teleport back to tower
            f->map_figure_remove();
            building *b = building_get(f->building_id);
            f->source_x = f->tile_x = b->x;
            f->source_y = f->tile_y = b->y;
            f->grid_offset = map_grid_offset(f->tile_x, f->tile_y);
            f->map_figure_add();
            f->action_state = FIGURE_ACTION_170_TOWER_SENTRY_AT_REST;
            f->route_remove();
        }
    }
}

void figure_kill_tower_sentries_at(int x, int y) {
    for (int i = 0; i < MAX_FIGURES[GAME_ENV]; i++) {
        figure *f = figure_get(i);
        if (!f->is_dead() && f->type == FIGURE_TOWER_SENTRY) {
            if (calc_maximum_distance(f->tile_x, f->tile_y, x, y) <= 1)
                f->state = FIGURE_STATE_DEAD;

        }
    }
}
