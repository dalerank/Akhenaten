#include "soldier.h"

#include "city/figures.h"
#include "city/map.h"
#include "core/calc.h"
#include "figure/combat.h"
#include "figure/formation.h"
#include "figure/formation_layout.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/properties.h"
#include "figure/route.h"
#include "figuretype/missile.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/point.h"

static const coords_t ALTERNATIVE_POINTS[] = {
  {-1, -6},
  {0, -1},
  {1, -1},
  {1, 0},
  {1, 1},
  {0, 1},
  {-1, 1},
  {-1, 0},
  {-1, -1},
  {0, -2},
  {1, -2},
  {2, -2},
  {2, -1},
  {2, 0},
  {2, 1},
  {2, 2},
  {1, 2},
  {0, 2},
  {-1, 2},
  {-2, 2},
  {-2, 1},
  {-2, 0},
  {-2, -1},
  {-2, -2},
  {-1, -2},
  {0, -3},
  {1, -3},
  {2, -3},
  {3, -3},
  {3, -2},
  {3, -1},
  {3, 0},
  {3, 1},
  {3, 2},
  {3, 3},
  {2, 3},
  {1, 3},
  {0, 3},
  {-1, 3},
  {-2, 3},
  {-3, 3},
  {-3, 2},
  {-3, 1},
  {-3, 0},
  {-3, -1},
  {-3, -2},
  {-3, -3},
  {-2, -3},
  {-1, -3},
  {0, -4},
  {1, -4},
  {2, -4},
  {3, -4},
  {4, -4},
  {4, -3},
  {4, -2},
  {4, -1},
  {4, 0},
  {4, 1},
  {4, 2},
  {4, 3},
  {4, 4},
  {3, 4},
  {2, 4},
  {1, 4},
  {0, 4},
  {-1, 4},
  {-2, 4},
  {-3, 4},
  {-4, 4},
  {-4, 3},
  {-4, 2},
  {-4, 1},
  {-4, 0},
  {-4, -1},
  {-4, -2},
  {-4, -3},
  {-4, -4},
  {-3, -4},
  {-2, -4},
  {-1, -4},
  {0, -5},
  {1, -5},
  {2, -5},
  {3, -5},
  {4, -5},
  {5, -5},
  {5, -4},
  {5, -3},
  {5, -2},
  {5, -1},
  {5, 0},
  {5, 1},
  {5, 2},
  {5, 3},
  {5, 4},
  {5, 5},
  {4, 5},
  {3, 5},
  {2, 5},
  {1, 5},
  {0, 5},
  {-1, 5},
  {-2, 5},
  {-3, 5},
  {-4, 5},
  {-5, 5},
  {-5, 4},
  {-5, 3},
  {-5, 2},
  {-5, 1},
  {-5, 0},
  {-5, -1},
  {-5, -2},
  {-5, -3},
  {-5, -4},
  {-5, -5},
  {-4, -5},
  {-3, -5},
  {-2, -5},
  {-1, -5},
  {0, -6},
  {1, -6},
  {2, -6},
  {3, -6},
  {4, -6},
  {5, -6},
  {6, -6},
  {6, -5},
  {6, -4},
  {6, -3},
  {6, -2},
  {6, -1},
  {6, 0},
  {6, 1},
  {6, 2},
  {6, 3},
  {6, 4},
  {6, 5},
  {6, 6},
  {5, 6},
  {4, 6},
  {3, 6},
  {2, 6},
  {1, 6},
  {0, 6},
  {-1, 6},
  {-2, 6},
  {-3, 6},
  {-4, 6},
  {-5, 6},
  {-6, 6},
  {-6, 5},
  {-6, 4},
  {-6, 3},
  {-6, 2},
  {-6, 1},
  {-6, 0},
  {-6, -1},
  {-6, -2},
  {-6, -3},
  {-6, -4},
  {-6, -5},
  {-6, -6},
  {-5, -6},
  {-4, -6},
  {-3, -6},
  {-2, -6},
  {-1, -6},
};

void figure::military_standard_action() {
    const formation* m = formation_get(formation_id);

    //    terrain_usage = TERRAIN_USAGE_ANY;
    //    figure_image_increase_offset(16);
    map_figure_remove();
    if (m->is_at_fort) {
        tile.set(m->x, m->y);
        //        tile.x() = m->x;
        //        tile.y() = m->y;
    } else {
        tile.set(m->standard_x, m->standard_y);
        //        tile.x() = m->standard_x;
        //        tile.y() = m->standard_y;
    }
    //    tile.grid_offset() = MAP_OFFSET(tile.x(), tile.y());
    cc_coords.x = 15 * tile.x() + 7;
    cc_coords.y = 15 * tile.y() + 7;
    map_figure_add();

    sprite_image_id = image_id_from_group(GROUP_FIGURE_FORT_STANDARD_POLE) + 20 - m->morale / 5;
    if (m->figure_type == FIGURE_FORT_LEGIONARY) {
        if (m->is_halted)
            cart_image_id = image_id_from_group(GROUP_FIGURE_FORT_FLAGS) + 8;
        else {
            cart_image_id = image_id_from_group(GROUP_FIGURE_FORT_FLAGS) + anim_frame / 2;
        }
    } else if (m->figure_type == FIGURE_FORT_MOUNTED) {
        if (m->is_halted)
            cart_image_id = image_id_from_group(GROUP_FIGURE_FORT_FLAGS) + 26;
        else {
            cart_image_id = image_id_from_group(GROUP_FIGURE_FORT_FLAGS) + 18 + anim_frame / 2;
        }
    } else {
        if (m->is_halted)
            cart_image_id = image_id_from_group(GROUP_FIGURE_FORT_FLAGS) + 17;
        else {
            cart_image_id = image_id_from_group(GROUP_FIGURE_FORT_FLAGS) + 9 + anim_frame / 2;
        }
    }
}

void figure::javelin_launch_missile() {
    map_point tile = {-1, -1};
    wait_ticks_missile++;
    if (wait_ticks_missile > figure_properties_for_type(type)->missile_delay) {
        wait_ticks_missile = 0;
        if (figure_combat_get_missile_target_for_soldier(this, 10, &tile)) {
            attack_image_offset = 1;
            direction = calc_missile_shooter_direction(tile.x(), tile.y(), tile.x(), tile.y());
        } else
            attack_image_offset = 0;
    }
    if (attack_image_offset) {
        if (attack_image_offset == 1) {
            if (tile.x() == -1 || tile.y() == -1)
                map_point_get_last_result(&tile);

            //            figure_create_missile(id, tile_x, tile_y, tile.x, tile.y, FIGURE_JAVELIN);
            missile_fire_at(target_figure_id, FIGURE_JAVELIN);
            formation_record_missile_fired(formation_get(formation_id));
        }
        attack_image_offset++;
        if (attack_image_offset > 100)
            attack_image_offset = 0;
    }
}
void figure::legionary_attack_adjacent_enemy() {
    for (int i = 0; i < 8 && action_state != FIGURE_ACTION_150_ATTACK; i++)
        figure_combat_attack_figure_at(tile.grid_offset() + map_grid_direction_delta(i));
}
int figure::find_mop_up_target() {
    int target_id = target_figure_id;
    if (figure_get(target_id)->is_dead()) {
        target_figure_id = 0;
        target_id = 0;
    }
    if (target_id <= 0) {
        target_id = figure_combat_get_target_for_soldier(tile.x(), tile.y(), 20);
        if (target_id) {
            figure* target = figure_get(target_id);
            destination_tile = target->tile;
            //            destination_tile.x() = target->tile.x();
            //            destination_tile.y() = target->tile.y();
            target_figure_id = target_id;
            target->targeted_by_figure_id = id;
            target_figure_created_sequence = target->created_sequence;
        } else {
            action_state = FIGURE_ACTION_84_SOLDIER_AT_STANDARD;
            anim_frame = 0;
        }
        route_remove();
    }
    return target_id;
}

void figure::update_image_javelin(int dir) {
    int image_id = image_id_from_group(GROUP_BUILDING_FORT_JAVELIN);
    if (action_state == FIGURE_ACTION_150_ATTACK) {
        if (attack_image_offset < 12)
            image_id = image_id + 96 + dir;
        else {
            image_id = image_id + 96 + dir + 8 * ((attack_image_offset - 12) / 2);
        }
    } else if (action_state == FIGURE_ACTION_149_CORPSE)
        image_id = image_id + 144 + figure_image_corpse_offset();
    else if (action_state == FIGURE_ACTION_84_SOLDIER_AT_STANDARD) {
        image_id = image_id + 96 + dir + 8 * figure_image_missile_launcher_offset();
    } else {
        image_id = image_id + dir + 8 * anim_frame;
    }
}
void figure::update_image_mounted(int dir) {
    int image_id = image_id_from_group(GROUP_FIGURE_FORT_MOUNTED);
    if (action_state == FIGURE_ACTION_150_ATTACK) {
        if (attack_image_offset < 12)
            image_id = image_id + 96 + dir;
        else {
            image_id = image_id + 96 + dir + 8 * ((attack_image_offset - 12) / 2);
        }
    } else if (action_state == FIGURE_ACTION_149_CORPSE)
        image_id = image_id + 144 + figure_image_corpse_offset();
    else {
        image_id = image_id + dir + 8 * anim_frame;
    }
}
void figure::update_image_legionary(const formation* m, int dir) {
    int image_id = image_id_from_group(GROUP_BUILDING_FORT_LEGIONARY);
    if (action_state == FIGURE_ACTION_150_ATTACK) {
        if (attack_image_offset < 12)
            image_id = image_id + 96 + dir;
        else {
            image_id = image_id + 96 + dir + 8 * ((attack_image_offset - 12) / 2);
        }
    } else if (action_state == FIGURE_ACTION_149_CORPSE)
        image_id = image_id + 152 + figure_image_corpse_offset();
    else if (action_state == FIGURE_ACTION_84_SOLDIER_AT_STANDARD) {
        if (m->is_halted && m->layout == FORMATION_COLUMN && m->missile_attack_timeout)
            image_id = image_id + dir + 144;
        else {
            image_id = image_id + dir;
        }
    } else {
        image_id = image_id + dir + 8 * anim_frame;
    }
}
void figure::soldier_update_image(const formation* m) {
    int dir;
    if (action_state == FIGURE_ACTION_150_ATTACK)
        dir = attack_direction;
    else if (m->missile_fired)
        dir = direction;
    else if (action_state == FIGURE_ACTION_84_SOLDIER_AT_STANDARD)
        dir = m->direction;
    else if (direction < 8)
        dir = direction;
    else
        dir = previous_tile_direction;
    dir = figure_image_normalize_direction(dir);
    if (type == FIGURE_FORT_JAVELIN)
        update_image_javelin(dir);
    else if (type == FIGURE_FORT_MOUNTED)
        update_image_mounted(dir);
    else if (type == FIGURE_FORT_LEGIONARY)
        update_image_legionary(m, dir);
}

void figure::soldier_action() {
    formation* m = formation_get(formation_id);
    city_figures_add_soldier();
    //    terrain_usage = TERRAIN_USAGE_ANY;
    //    figure_image_increase_offset(12);
    //    cart_image_id = 0;
    if (m->in_use != 1)
        kill();

    int speed_factor;
    if (type == FIGURE_FORT_MOUNTED)
        speed_factor = 3;
    else if (type == FIGURE_FORT_JAVELIN)
        speed_factor = 2;
    else {
        speed_factor = 1;
    }
    int layout = m->layout;
    if (formation_at_rest || action_state == FIGURE_ACTION_81_SOLDIER_GOING_TO_FORT)
        layout = FORMATION_AT_REST;

    formation_position_x.soldier = m->x + formation_layout_position_x(layout, index_in_formation);
    formation_position_y.soldier = m->y + formation_layout_position_y(layout, index_in_formation);

    switch (action_state) {
    case FIGURE_ACTION_80_SOLDIER_AT_REST:
        map_figure_update();
        wait_ticks = 0;
        formation_at_rest = 1;
        anim_frame = 0;
        if (tile.x() != formation_position_x.soldier || tile.y() != formation_position_y.soldier)
            action_state = FIGURE_ACTION_81_SOLDIER_GOING_TO_FORT;

        break;
    case FIGURE_ACTION_81_SOLDIER_GOING_TO_FORT:
    case FIGURE_ACTION_148_FLEEING:
        wait_ticks = 0;
        formation_at_rest = 1;
        destination_tile.set(formation_position_x.soldier, formation_position_y.soldier);
        //            destination_tile.x() = formation_position_x.soldier;
        //            destination_tile.y() = formation_position_y.soldier;
        //            destination_tile.grid_offset() = MAP_OFFSET(destination_tile.x(), destination_tile.y());
        move_ticks(speed_factor);
        if (direction == DIR_FIGURE_NONE)
            action_state = FIGURE_ACTION_80_SOLDIER_AT_REST;
        else if (direction == DIR_FIGURE_REROUTE)
            route_remove();
        else if (direction == DIR_FIGURE_CAN_NOT_REACH)
            poof();

        break;
    case FIGURE_ACTION_82_SOLDIER_RETURNING_TO_BARRACKS:
        formation_at_rest = 1;
        destination_tile = source_tile;
        //            destination_tile.x() = source_tile.x();
        //            destination_tile.y() = source_tile.y();
        move_ticks(speed_factor);
        if (direction == DIR_FIGURE_NONE || direction == DIR_FIGURE_CAN_NOT_REACH)
            poof();
        else if (direction == DIR_FIGURE_REROUTE)
            route_remove();

        break;
    case FIGURE_ACTION_83_SOLDIER_GOING_TO_STANDARD:
        formation_at_rest = 0;
        destination_tile.set(m->standard_x + formation_layout_position_x(m->layout, index_in_formation),
                             m->standard_y + formation_layout_position_y(m->layout, index_in_formation));
        //            destination_tile.x() = m->standard_x + formation_layout_position_x(m->layout, index_in_formation);
        //            destination_tile.y() = m->standard_y + formation_layout_position_y(m->layout, index_in_formation);
        if (alternative_location_index) {
            destination_tile.set(ALTERNATIVE_POINTS[alternative_location_index].x,
                                 ALTERNATIVE_POINTS[alternative_location_index].y);
            //                destination_tile.x() += ALTERNATIVE_POINTS[alternative_location_index].x;
            //                destination_tile.y() += ALTERNATIVE_POINTS[alternative_location_index].y;
        }
        //            destination_tile.grid_offset() = MAP_OFFSET(destination_tile.x(), destination_tile.y());
        move_ticks(speed_factor);
        if (direction == DIR_FIGURE_NONE) {
            action_state = FIGURE_ACTION_84_SOLDIER_AT_STANDARD;
            anim_frame = 0;
        } else if (direction == DIR_FIGURE_REROUTE)
            route_remove();
        else if (direction == DIR_FIGURE_CAN_NOT_REACH) {
            alternative_location_index++;
            if (alternative_location_index > 168)
                poof();

            anim_frame = 0;
        }
        break;
    case FIGURE_ACTION_84_SOLDIER_AT_STANDARD:
        formation_at_rest = 0;
        anim_frame = 0;
        map_figure_update();
        destination_tile.set(m->standard_x + formation_layout_position_x(m->layout, index_in_formation),
                             m->standard_y + formation_layout_position_y(m->layout, index_in_formation));
        //            destination_tile.x() = m->standard_x + formation_layout_position_x(m->layout, index_in_formation);
        //            destination_tile.y() = m->standard_y + formation_layout_position_y(m->layout, index_in_formation);
        if (alternative_location_index) {
            destination_tile.set(ALTERNATIVE_POINTS[alternative_location_index].x,
                                 ALTERNATIVE_POINTS[alternative_location_index].y);
            //                destination_tile.x() += ALTERNATIVE_POINTS[alternative_location_index].x;
            //                destination_tile.y() += ALTERNATIVE_POINTS[alternative_location_index].y;
        }
        if (tile.x() != destination_tile.x() || tile.y() != destination_tile.y()) {
            if (m->missile_fired <= 0 && m->recent_fight <= 0 && m->missile_attack_timeout <= 0) {
                action_state = FIGURE_ACTION_83_SOLDIER_GOING_TO_STANDARD;
                alternative_location_index = 0;
            }
        }
        if (action_state != FIGURE_ACTION_83_SOLDIER_GOING_TO_STANDARD) {
            if (type == FIGURE_FORT_JAVELIN)
                javelin_launch_missile();
            else if (type == FIGURE_FORT_LEGIONARY)
                legionary_attack_adjacent_enemy();
        }
        break;
    case FIGURE_ACTION_85_SOLDIER_GOING_TO_MILITARY_ACADEMY:
        m->has_military_training = 1;
        formation_at_rest = 1;
        move_ticks(speed_factor);
        if (direction == DIR_FIGURE_NONE)
            action_state = FIGURE_ACTION_81_SOLDIER_GOING_TO_FORT;
        else if (direction == DIR_FIGURE_REROUTE)
            route_remove();
        else if (direction == DIR_FIGURE_CAN_NOT_REACH)
            poof();

        break;
    case FIGURE_ACTION_86_SOLDIER_MOPPING_UP:
        formation_at_rest = 0;
        if (find_mop_up_target()) {
            move_ticks(speed_factor);
            if (direction == DIR_FIGURE_NONE) {
                figure* target = figure_get(target_figure_id);
                destination_tile = target->tile;
                //                    destination_tile.x() = target->tile.x();
                //                    destination_tile.y() = target->tile.y();
                route_remove();
            } else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_CAN_NOT_REACH) {
                action_state = FIGURE_ACTION_84_SOLDIER_AT_STANDARD;
                target_figure_id = 0;
                anim_frame = 0;
            }
        }
        break;
    case FIGURE_ACTION_87_SOLDIER_GOING_TO_DISTANT_BATTLE: {
        map_point& exit = city_map_exit_point();
        formation_at_rest = 0;
        destination_tile = exit;
        //            destination_tile.x() = exit->x();
        //            destination_tile.y() = exit->y();
        move_ticks(speed_factor);
        if (direction == DIR_FIGURE_NONE) {
            action_state = FIGURE_ACTION_89_SOLDIER_AT_DISTANT_BATTLE;
            route_remove();
        } else if (direction == DIR_FIGURE_REROUTE)
            route_remove();
        else if (direction == DIR_FIGURE_CAN_NOT_REACH)
            poof();

        break;
    }
    case FIGURE_ACTION_88_SOLDIER_RETURNING_FROM_DISTANT_BATTLE:
        //            is_ghost = false;
        wait_ticks = 0;
        formation_at_rest = 1;
        destination_tile.set(formation_position_x.soldier, formation_position_y.soldier);
        //            destination_tile.x() = formation_position_x.soldier;
        //            destination_tile.y() = formation_position_y.soldier;
        //            destination_tile.grid_offset() = MAP_OFFSET(destination_tile.x(), destination_tile.y());
        move_ticks(speed_factor);
        if (direction == DIR_FIGURE_NONE)
            action_state = FIGURE_ACTION_80_SOLDIER_AT_REST;
        else if (direction == DIR_FIGURE_REROUTE)
            route_remove();
        else if (direction == DIR_FIGURE_CAN_NOT_REACH)
            poof();

        break;
    case FIGURE_ACTION_89_SOLDIER_AT_DISTANT_BATTLE:
        //            is_ghost = true;
        formation_at_rest = 1;
        break;
    }

    soldier_update_image(m);
}
