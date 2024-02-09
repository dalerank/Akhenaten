#include "figure/figure.h"

#include "graphics/image_groups.h"
#include "grid/road_access.h"
#include "core/calc.h"

void figure::fireman_action() { // doubles as fireman! not as policeman!!!
    fireman_fight_fire();

    building* b = home();
    switch (action_state) {
    case FIGURE_ACTION_70_FIREMAN_CREATED:
        advance_action(ACTION_10_GOING);
        break;

    case ACTION_11_RETURNING_FROM_PATROL:
    case FIGURE_ACTION_73_FIREMAN_RETURNING:
        do_returnhome(TERRAIN_USAGE_PREFER_ROADS);
        break;

    case 9:
    case FIGURE_ACTION_71_FIREMAN_ENTERING_EXITING:
        do_enterbuilding(true, home());
        break;

    case ACTION_10_GOING:
    case FIGURE_ACTION_72_FIREMAN_ROAMING:
        do_roam(TERRAIN_USAGE_ROADS, ACTION_11_RETURNING_FROM_PATROL);
        break;

    case FIGURE_ACTION_74_FIREMAN_GOING_TO_FIRE:
    case 12:
        if (do_goto(destination_tile, TERRAIN_USAGE_PREFER_ROADS, FIGURE_ACTION_75_FIREMAN_AT_FIRE)) {
            wait_ticks = 50;
        }

        if (direction == DIR_FIGURE_REROUTE) {
            movement_ticks_watchdog++;
            int next_direction = calc_general_direction(tile, destination_tile);
            int dir_grid_offset = tile.grid_offset() + map_grid_direction_delta(next_direction);
            building *next_tile_b = building_at(dir_grid_offset);
            building *next_b = destination();
            auto clear_ruin_destination = [&] { if (next_b && next_b->type == BUILDING_BURNING_RUIN) { next_b->set_figure(3, 0); }};
            if (next_tile_b && next_tile_b->type == BUILDING_BURNING_RUIN) {
                clear_ruin_destination();
                set_destination(next_tile_b);
                advance_action(FIGURE_ACTION_75_FIREMAN_AT_FIRE);
            }
            
            if (!next_b || next_b->state == BUILDING_STATE_UNUSED || next_b->type != BUILDING_BURNING_RUIN) {
                clear_ruin_destination();
                bool has_fire_around = fireman_fight_fire();
                if (!has_fire_around) {
                    advance_action(ACTION_11_RETURNING_FROM_PATROL);
                }
            }

            if (movement_ticks_watchdog > 10) {
                movement_ticks_watchdog = 0;
                clear_ruin_destination();
                route_remove();
                advance_action(ACTION_11_RETURNING_FROM_PATROL);
            }
        }
        break;

    case FIGURE_ACTION_75_FIREMAN_AT_FIRE:
    case 13:
        fireman_extinguish_fire();
        break;

    case FIGURE_ACTION_76_FIREMAN_GOING_TO_ENEMY:
        //terrain_usage = TERRAIN_USAGE_ANY;
        //if (!target_is_alive()) {
        //    map_point road_tile;
        //    if (map_closest_road_within_radius(b->tile.x(), b->tile.y(), b->size, 2, road_tile)) {
        //        action_state = FIGURE_ACTION_73_FIREMAN_RETURNING;
        //        destination_tile = road_tile;
        //        route_remove();
        //        roam_length = 0;
        //    } else {
        //        poof();
        //    }
        //}
        //move_ticks(1);
        //if (direction == DIR_FIGURE_NONE) {
        //    figure* target = figure_get(target_figure_id);
        //    destination_tile = target->tile;
        //    route_remove();
        //} else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_CAN_NOT_REACH) {
        //    poof();
        //}
        advance_action(ACTION_11_RETURNING_FROM_PATROL);
        break;
    }

    constexpr int DEATH_FRAMES = 8;
    switch (action_state) {
        default:
        break;
    
    case FIGURE_ACTION_75_FIREMAN_AT_FIRE:
    case 13:
        direction = attack_direction;
        image_set_animation(GROUP_FIGURE_FIREMAN_ATFIRE, 0, 36);
        break;
    }
}
