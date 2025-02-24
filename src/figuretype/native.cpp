#include "native.h"

#include "building/building.h"
#include "city/city.h"
#include "city/military.h"
#include "figure/combat.h"
#include "figure/formation.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "grid/terrain.h"

void figure::indigenous_native_action() {
    building* b = home();
    //    terrain_usage = TERRAIN_USAGE_ANY;
    //    use_cross_country = false;
    //    max_roam_length = 800;
    //    if (b->state != BUILDING_STATE_VALID || b->figure_id != id)
    //        poof();

    //    figure_image_increase_offset(12);
    switch (action_state) {
    case FIGURE_ACTION_156_NATIVE_GOING_TO_MEETING_CENTER:
        move_ticks(1);
        if (direction == DIR_FIGURE_NONE) {
            action_state = FIGURE_ACTION_157_NATIVE_RETURNING_FROM_MEETING;
            destination_tile = source_tile;
            //                destination_tile.x() = source_tile.x();
            //                destination_tile.y() = source_tile.y();
        } else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_CAN_NOT_REACH)
            poof();

        break;
    case FIGURE_ACTION_157_NATIVE_RETURNING_FROM_MEETING:
        move_ticks(1);
        if (direction == DIR_FIGURE_NONE || direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }
        break;
    case FIGURE_ACTION_158_NATIVE_CREATED:
        anim.frame = 0;
        wait_ticks++;
        if (wait_ticks > 10 + (id & 3)) {
            wait_ticks = 0;
            if (!g_city.military.is_native_attack_active()) {
                int x_tile, y_tile;
                building* meeting = building_get(b->native_meeting_center_id);
                if (map_terrain_get_adjacent_road_or_clear_land(
                      meeting->tile.x(), meeting->tile.y(), meeting->size, &x_tile, &y_tile)) {
                    action_state = FIGURE_ACTION_156_NATIVE_GOING_TO_MEETING_CENTER;
                    destination_tile.set(x_tile, y_tile);
                    //                        destination_tile.x() = x_tile;
                    //                        destination_tile.y() = y_tile;
                }
            } else {
                const formation* m = formation_get(0);
                action_state = FIGURE_ACTION_159_NATIVE_ATTACKING;
                destination_tile.set(m->destination_x, m->destination_y);
                //                    destination_tile.x() = m->destination_x;
                //                    destination_tile.y() = m->destination_y;
                set_destination(m->destination_building_id);
            }
            route_remove();
        }
        break;
    case FIGURE_ACTION_159_NATIVE_ATTACKING:
        g_city.figures_add_attacking_native();
        terrain_usage = TERRAIN_USAGE_ENEMY;
        move_ticks(1);
        if (direction == DIR_FIGURE_NONE || direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_CAN_NOT_REACH) {
            action_state = FIGURE_ACTION_158_NATIVE_CREATED;
        }
        break;
    }
    int dir;
    if (action_state == FIGURE_ACTION_150_ATTACK || direction == DIR_FIGURE_ATTACK)
        dir = attack_direction;
    else if (direction < 8)
        dir = direction;
    else {
        dir = previous_tile_direction;
    }
    dir = figure_image_normalize_direction(dir);

    is_enemy_image = 1;
    if (action_state == FIGURE_ACTION_150_ATTACK) {
        if (attack_image_offset >= 12)
            sprite_image_id = 393 + dir + 8 * ((attack_image_offset - 12) / 2);
        else {
            sprite_image_id = 393 + dir;
        }
    } else if (action_state == FIGURE_ACTION_149_CORPSE)
        sprite_image_id = 441 + figure_image_corpse_offset();
    else if (direction == DIR_FIGURE_ATTACK)
        sprite_image_id = 393 + dir + 8 * (anim.frame / 2);
    else if (action_state == FIGURE_ACTION_159_NATIVE_ATTACKING)
        sprite_image_id = 297 + dir + 8 * anim.frame;
    else {
        sprite_image_id = 201 + dir + 8 * anim.frame;
    }
}
