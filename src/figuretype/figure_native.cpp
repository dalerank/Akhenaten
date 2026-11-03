#include "figure_native.h"

#include "building/building.h"
#include "city/city.h"
#include "city/military.h"
#include "figure/combat.h"
#include "figure/formation.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "graphics/animkeys.h"
#include "grid/terrain.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_native);

namespace {
constexpr int NATIVE_MAX_ROAM_LENGTH = 800;
constexpr int NATIVE_WAIT_TICKS = 10;
constexpr int NATIVE_WAIT_SPREAD = 3;
}

void figure_native::figure_action() {
    // OG: drown on flooded floodplain water.
    if (map_terrain_is(tile(), TERRAIN_WATER) && map_terrain_is(tile(), TERRAIN_FLOODPLAIN)) {
        poof();
        return;
    }

    base.terrain_usage = TERRAIN_USAGE_ANY;
    base.use_cross_country = false;
    base.max_roam_length = NATIVE_MAX_ROAM_LENGTH;

    building *b = home();
    if (!b || b->state != BUILDING_STATE_VALID || !b->has_figure(0, id())) {
        poof();
        return;
    }

    if (base.in_attack()) {
        base.figure_combat_handle_attack();
        return;
    }

    switch (base.action_state) {
    case FIGURE_ACTION_149_CORPSE:
        base.figure_combat_handle_corpse();
        break;

    case ACTION_11_NATIVE_ATTACKING:
        base.terrain_usage = TERRAIN_USAGE_ENEMY;
        base.flags |= e_figure_flag_enemy;
        base.flags &= ~e_figure_flag_friendly;
        g_city.figures.add_attacking_native();
        base.move_ticks(1);
        if (base.direction == DIR_FIGURE_NONE || base.direction == DIR_FIGURE_REROUTE
            || base.direction == DIR_FIGURE_CAN_NOT_REACH) {
            base.action_state = ACTION_10_NATIVE_CREATED;
            base.flags &= ~e_figure_flag_enemy;
            base.flags |= e_figure_flag_friendly;
        }
        break;

    case ACTION_10_NATIVE_CREATED:
        base.animctx.frame = 0;
        base.wait_ticks++;
        if (base.wait_ticks > NATIVE_WAIT_TICKS + (id() & NATIVE_WAIT_SPREAD)) {
            base.wait_ticks = 0;
            if (!g_city.military.is_native_attack_active()) {
                building *meeting = building_get(b->native_meeting_center_id);
                int x_tile = 0;
                int y_tile = 0;
                if (meeting && meeting->state == BUILDING_STATE_VALID
                    && map_terrain_get_adjacent_road_or_clear_land(
                         meeting->tile.x(), meeting->tile.y(), meeting->size, &x_tile, &y_tile)) {
                    base.action_state = ACTION_8_NATIVE_GOING_TO_MEETING;
                    base.destination_tile.set(x_tile, y_tile);
                }
            } else {
                const formation *m = formation_get(0);
                base.action_state = ACTION_11_NATIVE_ATTACKING;
                base.destination_tile = m->destination;
                set_destination(m->destination_building_id);
            }
            route_remove();
        }
        break;

    case ACTION_8_NATIVE_GOING_TO_MEETING:
        base.move_ticks(1);
        if (base.direction == DIR_FIGURE_REROUTE || base.direction == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        } else if (base.direction == DIR_FIGURE_NONE) {
            base.action_state = ACTION_9_NATIVE_RETURNING;
            base.destination_tile = base.source_tile;
        }
        break;

    case ACTION_9_NATIVE_RETURNING:
        base.move_ticks(1);
        if (base.direction == DIR_FIGURE_NONE || base.direction == DIR_FIGURE_REROUTE
            || base.direction == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }
        break;

    default:
        base.action_state = ACTION_10_NATIVE_CREATED;
        break;
    }
}

void figure_native::update_animation() {
    xstring animkey = animkeys().walk;
    if (action_state() == FIGURE_ACTION_149_CORPSE) {
        animkey = animkeys().death;
    } else if (base.in_attack() || base.direction == DIR_FIGURE_ATTACK) {
        animkey = animkeys().attack;
    }
    image_set_animation(animkey);
}

void figure_native::before_poof() {
}
