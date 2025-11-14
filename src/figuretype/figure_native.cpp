#include "figure_native.h"

#include "building/building.h"
#include "city/city.h"
#include "city/military.h"
#include "figure/combat.h"
#include "figure/formation.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "grid/terrain.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_native);

void figure_native::figure_action() {
    building* b = home();
    //    terrain_usage = TERRAIN_USAGE_ANY;
    //    use_cross_country = false;
    //    max_roam_length = 800;
    //    if (b->state != BUILDING_STATE_VALID || b->figure_id != id)
    //        poof();

    //    figure_image_increase_offset(12);
    switch (base.action_state) {
    case ACTION_160_NATIVE_GOING_TO_WAREHOUSE:
        base.move_ticks(1);
        if (base.direction == DIR_FIGURE_NONE) {
            base.action_state = ACTION_161_NATIVE_RETURNING;
            base.destination_tile = base.source_tile;
        } else if (base.direction == DIR_FIGURE_REROUTE || base.direction == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }
        break;

    case ACTION_161_NATIVE_RETURNING:
        base.move_ticks(1);
        if (base.direction == DIR_FIGURE_NONE || base.direction == DIR_FIGURE_REROUTE || base.direction == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }
        break;

    case ACTION_162_NATIVE_CREATED:
        base.animctx.frame = 0;
        base.wait_ticks++;
        if (base.wait_ticks > 10 + (base.id & 3)) {
            base.wait_ticks = 0;
            if (!g_city.military.is_native_attack_active()) {
                int x_tile, y_tile;
                building* meeting = building_get(b->native_meeting_center_id);
                if (map_terrain_get_adjacent_road_or_clear_land(
                      meeting->tile.x(), meeting->tile.y(), meeting->size, &x_tile, &y_tile)) {
                    base.action_state = ACTION_160_NATIVE_GOING_TO_WAREHOUSE;
                    base.destination_tile.set(x_tile, y_tile);
                }
            } else {
                const formation* m = formation_get(0);
                base.action_state = ACTION_159_NATIVE_ATTACKING;
                base.destination_tile = m->destination;
                set_destination(m->destination_building_id);
            }
            route_remove();
        }
        break;
    case ACTION_159_NATIVE_ATTACKING:
        g_city.figures_add_attacking_native();
        base.terrain_usage = TERRAIN_USAGE_ENEMY;
        base.move_ticks(1);
        if (base.direction == DIR_FIGURE_NONE || base.direction == DIR_FIGURE_REROUTE || base.direction == DIR_FIGURE_CAN_NOT_REACH) {
            base.action_state = ACTION_162_NATIVE_CREATED;
        }
        break;
    }
}

void figure_native::update_animation() {
    int dir;
    if (base.action_state == FIGURE_ACTION_150_ATTACK || base.direction == DIR_FIGURE_ATTACK)
        dir = base.attack_direction;
    else if (base.direction < 8)
        dir = base.direction;
    else {
        dir = base.previous_tile_direction;
    }
    dir = base.figure_image_normalize_direction(dir);

    if (base.action_state == FIGURE_ACTION_150_ATTACK) {
        if (base.attack_image_offset >= 12)
            base.main_image_id = 393 + dir + 8 * ((base.attack_image_offset - 12) / 2);
        else {
            base.main_image_id = 393 + dir;
        }
    } else if (base.action_state == FIGURE_ACTION_149_CORPSE)
        base.main_image_id = 441 + base.figure_image_corpse_offset();
    else if (base.direction == DIR_FIGURE_ATTACK)
        base.main_image_id = 393 + dir + 8 * (base.animctx.frame / 2);
    else if (base.action_state == ACTION_159_NATIVE_ATTACKING)
        base.main_image_id = 297 + dir + 8 * base.animctx.frame;
    else {
        base.main_image_id = 201 + dir + 8 * base.animctx.frame;
    }
}

void figure_native::before_poof() {
}
