#include "figure_tower_sentry.h"

#include "figure/enemy_army.h"
#include "figure/combat.h"
#include "city/city_figures.h"
#include "grid/routing/routing_terrain.h"
#include "figure_missile.h"
#include "grid/terrain.h"
#include "game/game_config.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_tower_sentry);

static const int TOWER_SENTRY_FIRING_OFFSETS[] = 
{ 0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
};

void figure_tower_sentry::tower_sentry_pick_target() {
    if (enemy_army_total_enemy_formations() <= 0)
        return;

    if (action_state() == FIGURE_ACTION_150_ATTACK || action_state() == FIGURE_ACTION_149_CORPSE)
        return;

    if (base.in_building_wait_ticks) {
        return;
    }

    auto &d = runtime_data();
    d.wait_ticks_next_target++;
    if (d.wait_ticks_next_target >= 40) {
        d.wait_ticks_next_target = 0;
        tile2i tile;
        if (figure_combat_get_missile_target_for_soldier(&base, 10, &tile)) {
            base.action_state = FIGURE_ACTION_172_TOWER_SENTRY_FIRING;
            base.destination_tile = tile;
            //            destination_tile.x() = tile.x();
            //            destination_tile.y() = tile.y();
        }
    }
}

int figure_tower_sentry::tower_sentry_init_patrol(building *b, int *x_tile, int *y_tile) {
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

void figure_tower_sentry::move_ticks_tower_sentry(int num_ticks) {
    while (num_ticks > 0) {
        num_ticks--;
        base.progress_on_tile++;
        if (base.progress_on_tile < 15) {
            base.advance_figure_tick();
        } else {
            base.progress_on_tile = 14;
        }
    }
}

void figure_tower_sentry::figure_before_action() {
    if (home()->state != BUILDING_STATE_VALID || !home()->has_figure(0, id())) {
        //poof();
    }
}

void figure_tower_sentry::figure_action() {
    building *b = home();
    //    terrain_usage = TERRAIN_USAGE_WALLS;
    //    use_cross_country = false;
    //    is_ghost = true;
    base.height_adjusted_ticks = 10;
    //    max_roam_length = 800;
    //    if (b->state != BUILDING_STATE_VALID || b->figure_id != id)
    //        poof();

    //    figure_image_increase_offset(12);
    short &wait_ticks = base.wait_ticks;

    tower_sentry_pick_target();
    switch (action_state()) {
    case FIGURE_ACTION_170_TOWER_SENTRY_AT_REST:
        base.animctx.frame = 0;
        wait_ticks++;
        if (wait_ticks > 40) {
            wait_ticks = 0;
            int x_tile, y_tile;
            if (tower_sentry_init_patrol(b, &x_tile, &y_tile)) {
                advance_action(FIGURE_ACTION_171_TOWER_SENTRY_PATROLLING);
                base.destination_tile.set(x_tile, y_tile);
                route_remove();
            }
        }
        break;

    case FIGURE_ACTION_171_TOWER_SENTRY_PATROLLING:
        base.move_ticks(1);
        if (direction() == DIR_FIGURE_NONE) {
            advance_action(FIGURE_ACTION_173_TOWER_SENTRY_RETURNING);
            base.destination_tile = base.source_tile;
            //                destination_tile.x() = source_tile.x();
            //                destination_tile.y() = source_tile.y();
            route_remove();
        } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH)
            advance_action(FIGURE_ACTION_170_TOWER_SENTRY_AT_REST);

        break;

    case FIGURE_ACTION_172_TOWER_SENTRY_FIRING:
        move_ticks_tower_sentry(1);
        base.wait_ticks_missile++;
        if (base.wait_ticks_missile > current_params().missile_delay) {
            tile2i tile;
            if (figure_combat_get_missile_target_for_soldier(&base, 10, &tile)) {
                base.direction = calc_missile_shooter_direction(tile, tile);
                base.wait_ticks_missile = 0;
                figure *f = figure_get(base.target_figure_id);
                figure_missile::create(base.home_building_id, tile, f->tile, FIGURE_JAVELIN);
            } else {
                advance_action(FIGURE_ACTION_173_TOWER_SENTRY_RETURNING);
                base.destination_tile = base.source_tile;
                route_remove();
            }
        }
        break;

    case ACTION_11_RETURNING_EMPTY:
    case FIGURE_ACTION_173_TOWER_SENTRY_RETURNING:
        base.move_ticks(1);
        if (direction() == DIR_FIGURE_NONE)
            advance_action(FIGURE_ACTION_170_TOWER_SENTRY_AT_REST);
        else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH)
            poof();

        break;

    case FIGURE_ACTION_174_TOWER_SENTRY_GOING_TO_TOWER:
        base.terrain_usage = TERRAIN_USAGE_ROADS;
        if (!!game_features::gameplay_change_tower_sentries_go_offroad) {
            base.terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
        }

        //            is_ghost = false;
        base.height_adjusted_ticks = 0;
        base.move_ticks(1);
        if (direction() == DIR_FIGURE_NONE) {
            base.map_figure_remove();
            base.source_tile = b->tile;
            base.tile = b->tile;
            base.map_figure_add();
            advance_action(FIGURE_ACTION_170_TOWER_SENTRY_AT_REST);
            route_remove();
        } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }

        break;
    }

    if (map_terrain_is(tile(), TERRAIN_WALL)) {
        base.current_height = 18;
    } else if (map_terrain_is(tile(), TERRAIN_GATEHOUSE)) {
        base.in_building_wait_ticks = 24;
    }

    if (base.in_building_wait_ticks) {
        base.in_building_wait_ticks--;
        base.height_adjusted_ticks = 0;
    }
}

void figure_tower_sentry::update_animation() {
    xstring animkey = animkeys().walk;
    //int dir = base.figure_image_direction();
    if (action_state(FIGURE_ACTION_149_CORPSE)) {
        animkey = animkeys().death;
    } else if (action_state(FIGURE_ACTION_172_TOWER_SENTRY_FIRING)) {
        animkey = animkeys().fire;  // image_id_from_group(GROUP_FIGURE_TOWER_SENTRY) + dir + 96 + 8 * TOWER_SENTRY_FIRING_OFFSETS[base.wait_ticks_missile / 2];
    } else if (action_state(FIGURE_ACTION_150_ATTACK)) {
        animkey = animkeys().attack;
        // if (base.attack_image_offset < 16)
        //     image_id = image_id + 96 + dir;
        // else {
        //     image_id = image_id + 96 + dir + 8 * ((base.attack_image_offset - 16) / 2);
        // }
    }

    image_set_animation(animkey);
}

void figure_tower_sentry::poof() {
    // 
}
