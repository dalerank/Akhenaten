#include "figure_tower_sentry.h"

#include "building/building_ferry.h"
#include "figure/enemy_army.h"
#include "figure/combat.h"
#include "figuretype/figure_cartpusher.h"
#include "city/city_figures.h"
#include "grid/routing/routing_terrain.h"
#include "figure_missile.h"
#include "grid/terrain.h"
#include "game/game_config.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_tower_sentry);

namespace {
constexpr int SENTRY_TARGET_SEARCH_TICKS = 40;
constexpr int SENTRY_REST_TICKS = 40;
constexpr int SENTRY_MISSILE_RANGE = 10;
constexpr int SENTRY_WALL_HEIGHT = 18;
constexpr int SENTRY_GATEHOUSE_WAIT = 24;
constexpr int SENTRY_MAX_ROAM = 800;
}

void figure_tower_sentry::tower_sentry_pick_target() {
    if (enemy_army_total_enemy_formations() <= 0) {
        return;
    }

    if (base.in_attack() || action_state() == FIGURE_ACTION_149_CORPSE) {
        return;
    }

    if (base.in_building_wait_ticks) {
        return;
    }

    // OG skips search while marching to the tower or on a ferry.
    if (action_state() == ACTION_174_TOWER_SENTRY_GOING_TO_TOWER
        || action_state() == ACTION_6_CARTPUSHER_ON_FERRY
        || action_state() == ACTION_7_CARTPUSHER_WAIT_FOR_FERRY) {
        return;
    }

    auto &d = runtime_data();
    d.wait_ticks_next_target++;
    if (d.wait_ticks_next_target >= SENTRY_TARGET_SEARCH_TICKS) {
        d.wait_ticks_next_target = 0;
        tile2i tile;
        if (figure_combat_get_missile_target_for_soldier(&base, SENTRY_MISSILE_RANGE, &tile)) {
            base.action_state = ACTION_172_TOWER_SENTRY_FIRING;
            // OG stays put while firing — destination is the sentry's own tile.
            base.destination_tile = base.tile;
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
            base.progress_on_tile = 15;
        }
    }
}

void figure_tower_sentry::figure_before_action() {
    building *b = home();
    if (!b || b->state != BUILDING_STATE_VALID || !b->has_figure(0, id())) {
        poof();
    }
}

void figure_tower_sentry::figure_action() {
    building *b = home();
    base.terrain_usage = TERRAIN_USAGE_WALLS;
    base.use_cross_country = false;
    base.set_flag(e_figure_flag_invisible, true);
    base.height_adjusted_ticks = 10;
    base.max_roam_length = SENTRY_MAX_ROAM;

    if (!b || b->state != BUILDING_STATE_VALID || !b->has_figure(0, id())) {
        poof();
        return;
    }

    short &wait_ticks = base.wait_ticks;

    tower_sentry_pick_target();
    switch (action_state()) {
    case ACTION_150_TOWER_SENTRY_ATTACK:
        base.figure_combat_handle_attack();
        break;

    case FIGURE_ACTION_149_CORPSE:
        base.figure_combat_handle_corpse();
        break;

    case ACTION_170_TOWER_SENTRY_AT_REST:
        base.animctx.frame = 0;
        wait_ticks++;
        if (wait_ticks > SENTRY_REST_TICKS) {
            wait_ticks = 0;
            int x_tile, y_tile;
            if (tower_sentry_init_patrol(b, &x_tile, &y_tile)) {
                advance_action(ACTION_171_TOWER_SENTRY_PATROLLING);
                base.destination_tile.set(x_tile, y_tile);
                route_remove();
            }
        }
        break;

    case ACTION_171_TOWER_SENTRY_PATROLLING:
        base.move_ticks(1);
        if (direction() == DIR_FIGURE_NONE) {
            advance_action(ACTION_173_TOWER_SENTRY_RETURNING);
            base.destination_tile = base.source_tile;
            route_remove();
        } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action(ACTION_170_TOWER_SENTRY_AT_REST);
        }
        break;

    case ACTION_172_TOWER_SENTRY_FIRING:
        move_ticks_tower_sentry(1);
        base.wait_ticks_missile++;
        if (base.wait_ticks_missile > current_params().missile_delay) {
            tile2i tile;
            if (figure_combat_get_missile_target_for_soldier(&base, SENTRY_MISSILE_RANGE, &tile)) {
                base.direction = calc_missile_shooter_direction(base.tile, tile);
                base.wait_ticks_missile = 0;
                figure_missile::create(id(), base.tile, tile, FIGURE_JAVELIN);
            } else {
                advance_action(ACTION_173_TOWER_SENTRY_RETURNING);
                base.destination_tile = base.source_tile;
                route_remove();
            }
        }
        break;

    case ACTION_173_TOWER_SENTRY_RETURNING:
        base.move_ticks(1);
        if (direction() == DIR_FIGURE_NONE) {
            advance_action(ACTION_170_TOWER_SENTRY_AT_REST);
        } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }
        break;

    case ACTION_174_TOWER_SENTRY_GOING_TO_TOWER:
        // OG TERRAIN_USAGE_ANY_OR_FORT — closest remake equivalent is ANY.
        base.terrain_usage = TERRAIN_USAGE_ANY;
        if (!!game_features::gameplay_change_tower_sentries_go_offroad) {
            base.terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
        }
        base.set_flag(e_figure_flag_invisible, false);
        base.height_adjusted_ticks = 0;
        base.move_ticks(1);
        if (direction() == DIR_FIGURE_NONE) {
            base.map_figure_remove();
            base.source_tile = b->tile;
            base.tile = b->tile;
            base.map_figure_add();
            advance_action(ACTION_170_TOWER_SENTRY_AT_REST);
            route_remove();
        } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }
        break;

    case ACTION_6_CARTPUSHER_ON_FERRY:
        base.terrain_usage = TERRAIN_USAGE_ANY;
        base.set_flag(e_figure_flag_invisible, true);
        break;

    case ACTION_7_CARTPUSHER_WAIT_FOR_FERRY:
        base.terrain_usage = TERRAIN_USAGE_ANY;
        base.animctx.frame = 0;
        wait_ticks++;
        if (wait_ticks > 100) {
            wait_ticks = 0;
            if (!figure_is_queued_for_ferry(id())) {
                poof();
            }
        }
        break;

    default:
        advance_action(ACTION_170_TOWER_SENTRY_AT_REST);
        break;
    }

    if (map_terrain_is(tile(), TERRAIN_WALL)) {
        base.current_height = SENTRY_WALL_HEIGHT;
    } else if (map_terrain_is(tile(), TERRAIN_GATEHOUSE)) {
        base.in_building_wait_ticks = SENTRY_GATEHOUSE_WAIT;
    } else if (action_state() != ACTION_174_TOWER_SENTRY_GOING_TO_TOWER
               && action_state() != ACTION_6_CARTPUSHER_ON_FERRY
               && action_state() != ACTION_7_CARTPUSHER_WAIT_FOR_FERRY) {
        // Off the wall (and not marching to the tower / ferrying) — die.
        poof();
    }

    if (base.in_building_wait_ticks) {
        base.in_building_wait_ticks--;
        base.height_adjusted_ticks = 0;
    }
}

void figure_tower_sentry::update_animation() {
    xstring animkey = animkeys().walk;
    if (action_state(FIGURE_ACTION_149_CORPSE)) {
        animkey = animkeys().death;
    } else if (action_state(ACTION_172_TOWER_SENTRY_FIRING)) {
        animkey = animkeys().fire;
    } else if (action_state(ACTION_150_TOWER_SENTRY_ATTACK) || base.in_attack()) {
        animkey = animkeys().attack;
    } else if (action_state(ACTION_6_CARTPUSHER_ON_FERRY)) {
        return;
    }

    image_set_animation(animkey);
}
