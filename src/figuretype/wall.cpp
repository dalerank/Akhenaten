#include "wall.h"

#include "building/building.h"
#include "core/calc.h"
#include "figure/combat.h"
#include "figure/enemy_army.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/properties.h"
#include "figure/route.h"
#include "figuretype/figure_missile.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/view/view.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/routing/routing_terrain.h"
#include "grid/terrain.h"
#include "config/config.h"
#include "sound/sound.h"
#include "city/city_figures.h"

static const int BALLISTA_FIRING_OFFSETS[]
  = {0, 1, 2, 3, 4, 5, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static const int TOWER_SENTRY_FIRING_OFFSETS[]
  = {0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void figure::ballista_action() {
    building* b = home();
    terrain_usage = TERRAIN_USAGE_WALLS;
    use_cross_country = false;
    height_adjusted_ticks = 10;
    current_height = 45;

    if (b->state != BUILDING_STATE_VALID || !b->has_figure(3, id))
        poof();

    if (b->num_workers <= 0 || !b->has_figure(3))
        poof();

    map_figure_remove();
    switch (city_view_orientation()) {
    case DIR_0_TOP_RIGHT:
        tile = b->tile;
        break;
    case DIR_2_BOTTOM_RIGHT:
        tile = b->tile.shifted(1, 0);
        break;
    case DIR_4_BOTTOM_LEFT:
        tile = b->tile.shifted(1, 1);
        break;
    case DIR_6_TOP_LEFT:
        tile = b->tile.shifted(0, 1);
        break;
    }
    //    tile.grid_offset() = MAP_OFFSET(tile.x(), tile.y());
    map_figure_add();

    switch (action_state) {
    case FIGURE_ACTION_149_CORPSE:
        poof();
        break;
    case FIGURE_ACTION_180_BALLISTA_CREATED:
        wait_ticks++;
        if (wait_ticks > 20) {
            wait_ticks = 0;
            tile2i tile;
            if (figure_combat_get_missile_target_for_soldier(this, 15, &tile)) {
                action_state = FIGURE_ACTION_181_BALLISTA_FIRING;
                wait_ticks_missile = figure_properties_for_type(type)->missile_delay;
            }
        }
        break;
    case FIGURE_ACTION_181_BALLISTA_FIRING:
        wait_ticks_missile++;
        if (wait_ticks_missile > figure_properties_for_type(type)->missile_delay) {
            tile2i tile;
            if (figure_combat_get_missile_target_for_soldier(this, 15, &tile)) {
                direction = calc_missile_shooter_direction(tile, tile);
                wait_ticks_missile = 0;
                figure* f = figure_get(target_figure_id);
                figure_missile::create(home_building_id, tile, f->tile, FIGURE_BOLT);
                g_sound.play_effect(SOUND_EFFECT_BALLISTA_SHOOT);
            } else {
                action_state = FIGURE_ACTION_180_BALLISTA_CREATED;
            }
        }
        break;
    }
    int dir = figure_image_direction();
    if (action_state == FIGURE_ACTION_181_BALLISTA_FIRING) {
        sprite_image_id
          = image_id_from_group(GROUP_FIGURE_BALLISTA) + dir + 8 * BALLISTA_FIRING_OFFSETS[wait_ticks_missile / 4];
    } else {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_BALLISTA) + dir;
    }
}

void figure::tower_sentry_pick_target() {
    if (enemy_army_total_enemy_formations() <= 0)
        return;
    if (action_state == FIGURE_ACTION_150_ATTACK || action_state == FIGURE_ACTION_149_CORPSE)
        return;
    if (in_building_wait_ticks)
        return;
    wait_ticks_next_target++;
    if (wait_ticks_next_target >= 40) {
        wait_ticks_next_target = 0;
        tile2i tile;
        if (figure_combat_get_missile_target_for_soldier(this, 10, &tile)) {
            action_state = FIGURE_ACTION_172_TOWER_SENTRY_FIRING;
            destination_tile = tile;
            //            destination_tile.x() = tile.x();
            //            destination_tile.y() = tile.y();
        }
    }
}

static int tower_sentry_init_patrol(building* b, int* x_tile, int* y_tile) {
    int dir = b->figure_roam_direction;
    int x = b->tile.x();
    int y = b->tile.y();
    switch (dir) {
    case DIR_0_TOP_RIGHT:
        y -= 8;
        break;
    case DIR_2_BOTTOM_RIGHT:
        x += 8;
        break;
    case DIR_4_BOTTOM_LEFT:
        y += 8;
        break;
    case DIR_6_TOP_LEFT:
        x -= 8;
        break;
    }
    map_grid_bound(&x, &y);

    if (map_routing_wall_tile_in_radius(x, y, 6, x_tile, y_tile)) {
        b->figure_roam_direction += 2;
        if (b->figure_roam_direction > 6)
            b->figure_roam_direction = 0;
        return 1;
    }
    for (int i = 0; i < 4; i++) {
        dir = b->figure_roam_direction;
        b->figure_roam_direction += 2;
        if (b->figure_roam_direction > 6)
            b->figure_roam_direction = 0;
        x = b->tile.x();
        y = b->tile.y();
        switch (dir) {
        case DIR_0_TOP_RIGHT:
            y -= 3;
            break;
        case DIR_2_BOTTOM_RIGHT:
            x += 3;
            break;
        case DIR_4_BOTTOM_LEFT:
            y += 3;
            break;
        case DIR_6_TOP_LEFT:
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
    building* b = home();
    //    terrain_usage = TERRAIN_USAGE_WALLS;
    //    use_cross_country = false;
    //    is_ghost = true;
    height_adjusted_ticks = 10;
    //    max_roam_length = 800;
    //    if (b->state != BUILDING_STATE_VALID || b->figure_id != id)
    //        poof();

    //    figure_image_increase_offset(12);

    tower_sentry_pick_target();
    switch (action_state) {
    case FIGURE_ACTION_170_TOWER_SENTRY_AT_REST:
        anim.frame = 0;
        wait_ticks++;
        if (wait_ticks > 40) {
            wait_ticks = 0;
            int x_tile, y_tile;
            if (tower_sentry_init_patrol(b, &x_tile, &y_tile)) {
                action_state = FIGURE_ACTION_171_TOWER_SENTRY_PATROLLING;
                destination_tile.set(x_tile, y_tile);
                route_remove();
            }
        }
        break;

    case FIGURE_ACTION_171_TOWER_SENTRY_PATROLLING:
        move_ticks(1);
        if (direction == DIR_FIGURE_NONE) {
            action_state = FIGURE_ACTION_173_TOWER_SENTRY_RETURNING;
            destination_tile = source_tile;
            //                destination_tile.x() = source_tile.x();
            //                destination_tile.y() = source_tile.y();
            route_remove();
        } else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_CAN_NOT_REACH)
            action_state = FIGURE_ACTION_170_TOWER_SENTRY_AT_REST;

        break;

    case FIGURE_ACTION_172_TOWER_SENTRY_FIRING:
        move_ticks_tower_sentry(1);
        wait_ticks_missile++;
        if (wait_ticks_missile > figure_properties_for_type(type)->missile_delay) {
            tile2i tile;
            if (figure_combat_get_missile_target_for_soldier(this, 10, &tile)) {
                direction = calc_missile_shooter_direction(tile, tile);
                wait_ticks_missile = 0;
                figure* f = figure_get(target_figure_id);
                figure_missile::create(home_building_id, tile, f->tile, FIGURE_JAVELIN);
            } else {
                action_state = FIGURE_ACTION_173_TOWER_SENTRY_RETURNING;
                destination_tile = source_tile;
                route_remove();
            }
        }
        break;

    case ACTION_11_RETURNING_EMPTY:
    case FIGURE_ACTION_173_TOWER_SENTRY_RETURNING:
        move_ticks(1);
        if (direction == DIR_FIGURE_NONE)
            action_state = FIGURE_ACTION_170_TOWER_SENTRY_AT_REST;
        else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_CAN_NOT_REACH)
            poof();

        break;

    case FIGURE_ACTION_174_TOWER_SENTRY_GOING_TO_TOWER:
        terrain_usage = TERRAIN_USAGE_ROADS;
        if (config_get(CONFIG_GP_CH_TOWER_SENTRIES_GO_OFFROAD))
            terrain_usage = TERRAIN_USAGE_PREFER_ROADS;

        //            is_ghost = false;
        height_adjusted_ticks = 0;
        move_ticks(1);
        if (direction == DIR_FIGURE_NONE) {
            map_figure_remove();
            source_tile = tile = b->tile;
            map_figure_add();
            action_state = FIGURE_ACTION_170_TOWER_SENTRY_AT_REST;
            route_remove();
        } else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }

        break;
    }

    if (map_terrain_is(tile.grid_offset(), TERRAIN_WALL)) {
        current_height = 18;
    } else if (map_terrain_is(tile.grid_offset(), TERRAIN_GATEHOUSE)) {
        in_building_wait_ticks = 24;
    }

    if (in_building_wait_ticks) {
        in_building_wait_ticks--;
        height_adjusted_ticks = 0;
    }
    int dir = figure_image_direction();
    if (action_state == FIGURE_ACTION_149_CORPSE) {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_TOWER_SENTRY) + 136 + figure_image_corpse_offset();
    } else if (action_state == FIGURE_ACTION_172_TOWER_SENTRY_FIRING) {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_TOWER_SENTRY) + dir + 96
                          + 8 * TOWER_SENTRY_FIRING_OFFSETS[wait_ticks_missile / 2];
    } else if (action_state == FIGURE_ACTION_150_ATTACK) {
        int image_id = image_id_from_group(GROUP_FIGURE_TOWER_SENTRY);
        if (attack_image_offset < 16)
            image_id = image_id + 96 + dir;
        else {
            image_id = image_id + 96 + dir + 8 * ((attack_image_offset - 16) / 2);
        }
    } else {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_TOWER_SENTRY) + dir + 8 * anim.frame;
    }
}

void figure_tower_sentry_reroute(void) {
    for (int i = 1; i < MAX_FIGURES; i++) {
        figure* f = figure_get(i);
        if (f->type != FIGURE_TOWER_SENTRY || map_routing_is_wall_passable(f->tile.grid_offset()))
            continue;

        // tower sentry got off wall due to rotation
        int x_tile, y_tile;
        if (map_routing_wall_tile_in_radius(f->tile.x(), f->tile.y(), 2, &x_tile, &y_tile)) {
            f->route_remove();
            f->progress_on_tile = 1;
            f->map_figure_remove();
            f->previous_tile = f->tile = tile2i(x_tile, y_tile);
            //            f->previous_tile.x() = f->tile.x() = x_tile;
            //            f->previous_tile.y() = f->tile.y() = y_tile;
            f->cc_coords.x = 15 * x_tile;
            f->cc_coords.y = 15 * y_tile;
            //            f->tile.grid_offset() = MAP_OFFSET(x_tile, y_tile);
            f->map_figure_add();
            f->action_state = FIGURE_ACTION_173_TOWER_SENTRY_RETURNING;
            f->destination_tile = f->source_tile;
            //            f->destination_tile.x() = f->source_tile.x();
            //            f->destination_tile.y() = f->source_tile.y();
        } else {
            // Teleport back to tower
            f->map_figure_remove();
            building* b = f->home();
            f->source_tile = f->tile = tile2i(b->tile.x(), b->tile.y());
            //            f->source_tile.x() = f->tile.x() = b->tile.x();
            //            f->source_tile.y() = f->tile.y() = b->tile.y();
            //            f->tile.grid_offset() = MAP_OFFSET(f->tile.x(), f->tile.y());
            f->map_figure_add();
            f->action_state = FIGURE_ACTION_170_TOWER_SENTRY_AT_REST;
            f->route_remove();
        }
    }
}

void figure_kill_tower_sentries_at(tile2i tile) {
    for (int i = 0; i < MAX_FIGURES; i++) {
        figure* f = figure_get(i);
        if (!f->is_dead() && f->type == FIGURE_TOWER_SENTRY) {
            if (calc_maximum_distance(f->tile, tile) <= 1)
                f->poof();
        }
    }
}
