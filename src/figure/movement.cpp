#include "movement.h"

#include "grid/road_network.h"
#include "building/building.h"
#include "building/destruction.h"
#include "building/building_roadblock.h"
#include "building/monuments.h"
#include "core/calc.h"
#include "figure/combat.h"
#include "figure/route.h"
#include "graphics/image_groups.h"
#include "grid/bridge.h"
#include "grid/building.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/property.h"
#include "grid/random.h"
#include "grid/road_access.h"
#include "grid/routing/routing_terrain.h"
#include "grid/terrain.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "game/game_config.h"
#include "game/game.h"

#include <algorithm>

void figure::advance_figure_tick() {
    switch (direction) {
    case DIR_0_TOP_RIGHT:
        cc_coords.y--;
        break;
    case DIR_1_RIGHT:
        cc_coords.x++;
        cc_coords.y--;
        break;
    case DIR_2_BOTTOM_RIGHT:
        cc_coords.x++;
        break;
    case DIR_3_BOTTOM:
        cc_coords.x++;
        cc_coords.y++;
        break;
    case DIR_4_BOTTOM_LEFT:
        cc_coords.y++;
        break;
    case DIR_5_LEFT:
        cc_coords.x--;
        cc_coords.y++;
        break;
    case DIR_6_TOP_LEFT:
        cc_coords.x--;
        break;
    case DIR_7_TOP:
        cc_coords.x--;
        cc_coords.y--;
        break;
    default:
        break;
    }
    if (height_adjusted_ticks) {
        height_adjusted_ticks--;
        if (height_adjusted_ticks > 0) {
            if (current_height < target_height)
                current_height++;

            if (current_height > target_height)
                current_height--;
        }
    } else {
        if (current_height)
            current_height--;
    }
}

void figure::set_target_height_bridge() {
    height_adjusted_ticks = 18;
    target_height = map_bridge_height(tile.grid_offset());
}

void figure::set_target_height_building() {
    height_adjusted_ticks = 18;
    target_height = map_building_height_at(tile.grid_offset());
}

e_permission figure::get_permission_for_figure() {
    return dcast()->get_permission();
}

void figure::move_to_next_tile() {
    const tile2i old = tile;

    map_figure_remove(); // is this necessary??? maybe could be refactored in the future...
    switch (direction) {
    default:
        return;

    case DIR_0_TOP_RIGHT:    tile.shift(0, -1); break;
    case DIR_1_RIGHT:        tile.shift(1, -1); break;
    case DIR_2_BOTTOM_RIGHT: tile.shift(1,  0); break;
    case DIR_3_BOTTOM:       tile.shift(1,  1); break;
    case DIR_4_BOTTOM_LEFT:  tile.shift(0,  1); break;
    case DIR_5_LEFT:         tile.shift(-1, 1); break;
    case DIR_6_TOP_LEFT:     tile.shift(-1, 0); break;
    case DIR_7_TOP:          tile.shift(-1,-1); break;
    }

    map_figure_add();
    figure_combat_attack_figure_at(tile.grid_offset());

    const int old_terrain = map_terrain_get(old);
    const int current_terrain = map_terrain_get(tile);
    if (old_terrain != current_terrain) {
        dcast()->on_change_terrain(old_terrain, current_terrain);
    }

    terrain_type = map_terrain_get(tile);

    previous_tile = old;
}

void figure::set_next_tile_and_direction() {
    if (routing_path_id > 0) {                               // has a path generated for its destination
        if (routing_path_current_tile < routing_path_length) {// advance to next tile in path
            direction = figure_route_get_direction(routing_path_id, routing_path_current_tile);
        } else { // at destination!!
            route_remove();
            direction = DIR_FIGURE_NONE;
        }
    } else { // no path possible - should be at destination
        direction = calc_general_direction(tile, destination_tile);
        if (direction != DIR_FIGURE_NONE) {
            if (!roam_wander_freely) { // this is because the road network was cutoff from the "randomized direction"
                                     // target
                roam_wander_freely = true;
            } else { // all other cases
                direction = DIR_FIGURE_CAN_NOT_REACH;
            }
        }
    }
}

void figure::advance_route_tile(int roaming_enabled) {
    if (direction >= 8) {
        return;
    }

    int target_grid_offset = tile.grid_offset() + map_grid_direction_delta(direction);

    const bool is_water_move = (allow_move_type == EMOVE_WATER);
    const bool is_amphibia_move = (allow_move_type == EMOVE_AMPHIBIAN);
    const bool is_deepwater_move = (allow_move_type == EMOVE_DEEPWATER);
    const bool is_ferry_route = map_terrain_is(target_grid_offset, TERRAIN_FERRY_ROUTE);
    const bool is_water_tile = map_terrain_is(target_grid_offset, TERRAIN_WATER);
    if (!is_deepwater_move && !is_water_move && !is_amphibia_move && !is_ferry_route && is_water_tile) {
        direction = DIR_FIGURE_REROUTE;
    } else if (is_water_move && !is_water_tile) { // boats can not travel on land
        direction = DIR_FIGURE_REROUTE;
    } else if (!map_routing_passable_by_usage(terrain_usage, target_grid_offset)) {
        direction = DIR_FIGURE_REROUTE;
    } else if (terrain_usage == TERRAIN_USAGE_ENEMY) {
        if (map_routing_is_destroyable(target_grid_offset)) {
            int cause_damage = 1;
            int max_damage = 0;
            switch (map_routing_get_destroyable(target_grid_offset)) {
            case DESTROYABLE_BUILDING:
                max_damage = 10;
                break;

            case DESTROYABLE_CANALS_GARDEN:
                if (map_terrain_is(target_grid_offset, TERRAIN_GARDEN | TERRAIN_ACCESS_RAMP | TERRAIN_RUBBLE))
                    cause_damage = 0;
                else
                    max_damage = 10;
                break;
            case DESTROYABLE_WALL:
                max_damage = 200;
                break;
            case DESTROYABLE_GATEHOUSE:
                max_damage = 150;
                break;
            }

            if (cause_damage) {
                attack_direction = direction;
                direction = DIR_FIGURE_ATTACK;
                if (!(game.simtime.tick & 3)) {
                    building_destroy_increase_enemy_damage(target_grid_offset, max_damage);
                }
            }
        }
    } else if (map_terrain_is(target_grid_offset, TERRAIN_ROAD | TERRAIN_ACCESS_RAMP)) {
        if (map_terrain_is(target_grid_offset, TERRAIN_WATER) && map_terrain_is(target_grid_offset, TERRAIN_FLOODPLAIN)) {
            direction = DIR_FIGURE_REROUTE;
        } else if (roaming_enabled && map_terrain_is(target_grid_offset, TERRAIN_BUILDING)) {
            building* b = building_at(target_grid_offset);
            if (b->type == BUILDING_MUD_GATEHOUSE || b->type == BUILDING_ROADBLOCK) {
                // do not allow roaming through gatehouses or roadblocks
                if (roaming_enabled)
                    direction = DIR_FIGURE_REROUTE;
            }
        }
    } else if (map_terrain_is(target_grid_offset, TERRAIN_BUILDING)) {
        building *b = building_at(target_grid_offset);
        switch (b->type) {
            //            case BUILDING_WAREHOUSE_SPACE:
            //            case BUILDING_GRANARY:
        case BUILDING_RESERVED_TRIUMPHAL_ARCH_56:
        case BUILDING_HOUSE_VACANT_LOT:
        case BUILDING_FORT_GROUND:
        case BUILDING_FESTIVAL_SQUARE:
        case BUILDING_PLAZA:
        case BUILDING_FERRY:
        case BUILDING_BOOTH:
        case BUILDING_BANDSTAND:
        case BUILDING_FIGS_FARM:
        case BUILDING_GRAIN_FARM:
        case BUILDING_CHICKPEAS_FARM:
        case BUILDING_BARLEY_FARM:
        case BUILDING_FLAX_FARM:
        case BUILDING_PAVILLION:
            //
            break; // OK to walk

        case BUILDING_ROADBLOCK:
            break;

        case BUILDING_BURNING_RUIN:
            if (b->state != BUILDING_STATE_RUBBLE) {
                direction = DIR_FIGURE_REROUTE;
            }
            break;

        case BUILDING_SMALL_MASTABA:
        case BUILDING_SMALL_MASTABA_SIDE:
        case BUILDING_SMALL_MASTABA_WALL:
        case BUILDING_SMALL_MASTABA_ENTRANCE:
        case BUILDING_MEDIUM_MASTABA:
        case BUILDING_MEDIUM_MASTABA_SIDE:
        case BUILDING_MEDIUM_MASTABA_WALL:
        case BUILDING_MEDIUM_MASTABA_ENTRANCE:
            {
                auto &d = b->dcast_monument()->runtime_data();
                if (d.phase > 2) {
                    //direction = DIR_FIGURE_REROUTE;
                }
            }
            break;
            
        default:
            direction = DIR_FIGURE_REROUTE;
        }
    }
    //    else if (map_terrain_is(target_grid_offset, TERRAIN_IMPASSABLE))
    //        direction = DIR_FIGURE_REROUTE;
}

void figure::move_ticks(int num_ticks, bool roaming_enabled) {
    while (num_ticks > 0) {
        num_ticks--;

        if (progress_inside_speed > 0) {
            progress_inside--;
            if (progress_inside >= 0) {
                continue;
            }
            if (progress_inside < 0) {
                progress_inside = progress_inside_speed;
            }
        }

        progress_on_tile++;
        if (progress_on_tile == 8) { // tile edge reached
            move_to_next_tile();
        }

        if (progress_on_tile >= 15) { // tile center
            progress_on_tile = std::clamp<unsigned char>(progress_on_tile, 0, 15);
            figure_service_provide_coverage();

            // update route
            if (routing_path_id <= 0) {
                figure_route_add();
            }

            set_next_tile_and_direction();
            advance_route_tile(roaming_enabled);
            if (direction >= 8) {
                break;
            }
            routing_path_current_tile++;
            previous_tile_direction = direction;
        }

        if (progress_on_tile > 14) {
            progress_on_tile = 0;
        }
        advance_figure_tick();
    }
}

void figure::init_roaming_from_building(int roam_dir) {
    progress_on_tile = 14;
    roam_wander_freely = false;
    roam_ticks_until_next_turn = -1;
    roam_turn_direction = 2;

    // randomize a search area in a general direction to send off roamers to
    building* b = home();
    int offset_search_x = b->tile.x();
    int offset_search_y = b->tile.y();
    switch (roam_dir) {
    case DIR_0_TOP_RIGHT: offset_search_y -= 8; break;
    case DIR_2_BOTTOM_RIGHT: offset_search_x += 8; break;
    case DIR_4_BOTTOM_LEFT: offset_search_y += 8; break;
    case DIR_6_TOP_LEFT: offset_search_x -= 8; break;
    }

    // look for a road within the search area
    map_grid_bound(&offset_search_x, &offset_search_y);
    tile2i road_tile = map_closest_road_within_radius(tile2i(offset_search_x, offset_search_y), 1, 6);
    int found_road = road_tile.valid();
    int road_network_original = map_road_network_get(tile);
    int road_network_found = map_road_network_get(road_tile);

    if (found_road && road_network_original == road_network_found) { // must be in the same network!!
        destination_tile = road_tile;
    } else {
        roam_wander_freely = true; // no road found within bounds, roam freely
    }
}

void figure::roam_set_direction() {
    int grid_offset = MAP_OFFSET(tile.x(), tile.y());
    int direction = calc_general_direction(tile, destination_tile);
    if (direction >= 8)
        direction = 0;

    int road_offset_dir1 = 0;
    int road_dir1 = 0;
    for (int i = 0, dir = direction; i < 8; i++) {
        if (dir % 2 == 0 && map_terrain_is(grid_offset + map_grid_direction_delta(dir), TERRAIN_ROAD)) {
            if (!map_terrain_is(grid_offset + map_grid_direction_delta(dir), TERRAIN_WATER)
                || !map_terrain_is(grid_offset + map_grid_direction_delta(dir), TERRAIN_FLOODPLAIN)) {
                road_dir1 = dir;
                break;
            }
        }

        dir++;
        if (dir > 7) {
            dir = 0;
        }
        road_offset_dir1++;
    }
    int road_offset_dir2 = 0;
    int road_dir2 = 0;
    for (int i = 0, dir = direction; i < 8; i++) {
        if (dir % 2 == 0 && map_terrain_is(grid_offset + map_grid_direction_delta(dir), TERRAIN_ROAD)) {
            if (!map_terrain_is(grid_offset + map_grid_direction_delta(dir), TERRAIN_WATER)
                || !map_terrain_is(grid_offset + map_grid_direction_delta(dir), TERRAIN_FLOODPLAIN)) {
                road_dir2 = dir;
                break;
            }
        }

        dir--;
        if (dir < 0) {
            dir = 7;
        }
        road_offset_dir2++;
    }

    if (road_offset_dir1 <= road_offset_dir2) {
        direction = road_dir1;
        roam_turn_direction = 2;
    } else {
        direction = road_dir2;
        roam_turn_direction = -2;
    }
    roam_ticks_until_next_turn = 5;
}

void figure::follow_ticks(int num_ticks) {
    figure *leader = figure_get(leading_figure_id);

    while (num_ticks > 0) {
        num_ticks--;
        progress_on_tile++;
        if (progress_on_tile == 8) { // tile edge reached
            move_to_next_tile();
        }

        if (progress_on_tile >= 15) { // tile center
            figure_service_provide_coverage();
            int found_dir = calc_general_direction(tile, leader->previous_tile);
            if (found_dir >= 8) {
                animctx.frame = 0;
                progress_on_tile--;
                continue;
            }
            previous_tile_direction = direction;
            direction = found_dir;
        }

        if (progress_on_tile > 14) { // wrap around
            progress_on_tile = 0;
        }

        advance_figure_tick();
    }
}

int figure::roam_ticks(int num_ticks) {
    route_remove(); // refresh path to check if road network is disconnected
    // no destination: walk to end of tile and pick a direction
    auto clamp_direction = [] (int direction) {
        if (direction > 6) direction = 0;
        else if (direction < 0) direction = 6;
        return direction;
    };

    while (num_ticks > 0) {
        num_ticks--;
        progress_on_tile++;
        if (progress_on_tile == 8) {// tile edge reached
            move_to_next_tile();
        }

        if (progress_on_tile >= 15) { // tile center
            if (figure_service_provide_coverage()) {
                return direction;
            }

            add_roam_history(tile.grid_offset());

            int came_from_direction = (previous_tile_direction + 4) % 8;
            int road_tiles[8];
            e_permission permission = get_permission_for_figure();
            int adjacent_road_tiles = map_get_adjacent_road_tiles_for_roaming(tile.grid_offset(), road_tiles, permission);
            if (adjacent_road_tiles == 3 && map_get_diagonal_road_tiles_for_roaming(tile.grid_offset(), road_tiles) >= 5) {
                // go in the straight direction of a double-wide road
                adjacent_road_tiles = 2;
                if (came_from_direction == DIR_0_TOP_RIGHT || came_from_direction == DIR_4_BOTTOM_LEFT) {
                    if (road_tiles[0] && road_tiles[4]) {
                        road_tiles[2] = road_tiles[6] = 0;
                    } else {
                        road_tiles[0] = road_tiles[4] = 0;
                    }

                } else {
                    if (road_tiles[2] && road_tiles[6]) {
                        road_tiles[0] = road_tiles[4] = 0;
                    } else {
                        road_tiles[2] = road_tiles[6] = 0;
                    }
                }
            }

            if (adjacent_road_tiles == 4 && map_get_diagonal_road_tiles_for_roaming(tile, road_tiles) >= 8) {
                // go straight on when all surrounding tiles are road
                adjacent_road_tiles = 2;
                if (came_from_direction == DIR_0_TOP_RIGHT || came_from_direction == DIR_4_BOTTOM_LEFT) {
                    road_tiles[2] = road_tiles[6] = 0;
                } else {
                    road_tiles[0] = road_tiles[4] = 0;
                }
            }

            if (adjacent_road_tiles <= 0) {
                roam_length = max_roam_length; // end roaming walk
                return direction;
            }
            
            if (adjacent_road_tiles == 1) {
                int dir = 0;
                do {
                    direction = 2 * dir;
                } while (!road_tiles[direction] && dir++ < 4);
            } else if (adjacent_road_tiles == 2) {
                if (roam_ticks_until_next_turn == -1) {
                    roam_set_direction();
                    //                    came_from_direction = -1; // TODO?
                }
                // 1. continue in the same direction
                // 2. turn in the direction given by roam_turn_direction
                int dir = 0;
                do {
                    if (road_tiles[direction] && direction != came_from_direction) {
                        break;
                    }

                    direction = clamp_direction(direction + roam_turn_direction);
                } while (dir++ < 4);
            } else { // > 2 road tiles
                direction = (roam_random_counter + map_random_get(tile)) & 6;
                if (!road_tiles[direction] || direction == came_from_direction) {
                    roam_ticks_until_next_turn--;
                    if (roam_ticks_until_next_turn <= 0) {
                        roam_set_direction();
                        came_from_direction = -1;
                    }
                    for (int dir = 0; dir < 4; ++dir) {
                        if (road_tiles[direction]) {
                            if (direction != came_from_direction) {
                                break;
                            }

                            const int dirtile = tile.grid_offset() + map_grid_direction_delta(direction);
                            if (!in_roam_history(dirtile)) {
                                break;
                            }
                        }

                        direction = clamp_direction(direction + roam_turn_direction);
                    }
                } else {
                    if (in_roam_history(tile.grid_offset())) {
                        for (int dir = 0; dir < 4; ++dir) {
                            const int dirtile = tile.grid_offset() + map_grid_direction_delta(direction);
                            if (!in_roam_history(dirtile)) {
                                break;
                            }

                            direction = clamp_direction(direction + roam_turn_direction);
                        };
                    }
                }
            }
            routing_path_current_tile++;
            previous_tile_direction = direction;
        }

        if (progress_on_tile > 14) { // wrap around
            progress_on_tile = 0;
        }

        advance_figure_tick();
    }

    return direction;
}

void figure::advance_attack() {
    if (progress_on_tile <= 5) {
        progress_on_tile++;
        advance_figure_tick();
    }
}

void figure::set_cross_country_direction(int x_src, int y_src, int x_dst, int y_dst, int is_missile) {
    // all x/y are in 1/15th of a tile
    cc_destination.x = x_dst;
    cc_destination.y = y_dst;
    cc_delta.x = (x_src > x_dst) ? (x_src - x_dst) : (x_dst - x_src);
    cc_delta.y = (y_src > y_dst) ? (y_src - y_dst) : (y_dst - y_src);
    if (cc_delta.x < cc_delta.y)
        cc_delta_xy = 2 * cc_delta.x - cc_delta.y;
    else if (cc_delta.y < cc_delta.x)
        cc_delta_xy = 2 * cc_delta.y - cc_delta.x;
    else // equal
        cc_delta_xy = 0;
    if (is_missile)
        direction = calc_missile_direction(x_src, y_src, x_dst, y_dst);
    else {
        direction = calc_general_direction(tile2i(x_src, y_src), tile2i(x_dst, y_dst));
        if (cc_delta.y > 2 * cc_delta.x) {
            switch (direction) {
            case DIR_1_RIGHT:
            case DIR_7_TOP:
                direction = DIR_0_TOP_RIGHT;
                break;
            case DIR_3_BOTTOM:
            case DIR_5_LEFT:
                direction = DIR_4_BOTTOM_LEFT;
                break;
            }
        }
        if (cc_delta.x > 2 * cc_delta.y) {
            switch (direction) {
            case DIR_1_RIGHT:
            case DIR_3_BOTTOM:
                direction = DIR_2_BOTTOM_RIGHT;
                break;
            case DIR_5_LEFT:
            case DIR_7_TOP:
                direction = DIR_6_TOP_LEFT;
                break;
            }
        }
    }
    if (cc_delta.x >= cc_delta.y)
        cc_direction = 1;
    else
        cc_direction = 2;
}

void figure::set_cross_country_destination(tile2i dst) {
    destination_tile = dst;
    set_cross_country_direction(cc_coords.x, cc_coords.y, 15 * dst.x(), 15 * dst.y(), 0);
}

bool figure::move_ticks_cross_country(int num_ticks) {
    map_figure_remove();
    bool is_at_destination = false;
    while (num_ticks > 0) {
        num_ticks--;
        if (cc_delta.x + cc_delta.y <= 0) {
            is_at_destination = true;
            break;
        }
        cross_country_advance();
    }
    tile2i old = tile;
    tile.set(cc_coords.x / 15, cc_coords.y / 15);

    if (map_terrain_is(tile, TERRAIN_BUILDING)) {
        in_building_wait_ticks = 8;
    } else if (in_building_wait_ticks) {
        in_building_wait_ticks--;
    }

    map_figure_add();
    if (tile != old) {
        previous_tile = old;
    }

    return is_at_destination;
}

void figure::cross_country_update_delta() {
    if (cc_direction == 1) { // x
        if (cc_delta_xy >= 0)
            cc_delta_xy += 2 * (cc_delta.y - cc_delta.x);
        else
            cc_delta_xy += 2 * cc_delta.y;
        cc_delta.x--;
    } else { // y
        if (cc_delta_xy >= 0)
            cc_delta_xy += 2 * (cc_delta.x - cc_delta.y);
        else
            cc_delta_xy += 2 * cc_delta.x;
        cc_delta.y--;
    }
}
void figure::cross_country_advance_x() {
    if (cc_coords.x < cc_destination.x)
        cc_coords.x++;
    else if (cc_coords.x > cc_destination.x)
        cc_coords.x--;
}
void figure::cross_country_advance_y() {
    if (cc_coords.y < cc_destination.y)
        cc_coords.y++;
    else if (cc_coords.y > cc_destination.y)
        cc_coords.y--;
}
void figure::cross_country_advance() {
    cross_country_update_delta();
    if (cc_direction == 2) { // y
        cross_country_advance_y();
        if (cc_delta_xy >= 0) {
            cc_delta.x--;
            cross_country_advance_x();
        }
    } else {
        cross_country_advance_x();
        if (cc_delta_xy >= 0) {
            cc_delta.y--;
            cross_country_advance_y();
        }
    }
}

int figure_movement_can_launch_cross_country_missile(tile2i src, tile2i dst) {
    int height = 0;
    figure* f = figure_get(0); // abuse unused figure 0 as scratch
    f->cc_coords.x = 15 * src.x();
    f->cc_coords.y = 15 * src.y();
    if (map_terrain_is(MAP_OFFSET(src.x(), src.y()), TERRAIN_WALL_OR_GATEHOUSE))
        height = 6;

    f->set_cross_country_direction(15 * src.x(), 15 * src.y(), 15 * dst.x(), 15 * dst.y(), 0);

    for (int guard = 0; guard < 1000; guard++) {
        for (int i = 0; i < 8; i++) {
            if (f->cc_delta.x + f->cc_delta.y <= 0)
                return 1;

            f->cross_country_advance();
        }
        f->tile.set(f->cc_coords.x / 15, f->cc_coords.y / 15);

        if (height) {
            height--;
        } else {
            int grid_offset = MAP_OFFSET(f->tile.x(), f->tile.y());
            if (map_terrain_is(grid_offset, TERRAIN_WALL | TERRAIN_GATEHOUSE | TERRAIN_TREE))
                break;

            if (map_terrain_is(grid_offset, TERRAIN_BUILDING) && map_property_multi_tile_size(grid_offset) > 1)
                break;
        }
    }
    return 0;
}
