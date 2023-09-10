#include "maintenance.h"

#include "building/building.h"
#include "building/house.h"
#include "building/destruction.h"
#include "building/list.h"
#include "city/buildings.h"
#include "city/map.h"
#include "city/message.h"
#include "city/population.h"
#include "city/sentiment.h"
#include "city/warning.h"
#include "core/calc.h"
#include "core/random.h"
#include "core/profiler.h"
#include "figuretype/migrant.h"
#include "figure/route.h"
#include "game/tutorial.h"
#include "game/undo.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/grid.h"
#include "grid/random.h"
#include "grid/road_access.h"
#include "grid/road_network.h"
#include "grid/routing/routing.h"
#include "grid/routing/routing_terrain.h"
#include "grid/tiles.h"
#include "model.h"
#include "scenario/property.h"
#include "sound/effect.h"

int g_fire_spread_direction = 0;

void building_maintenance_update_fire_direction(void) {
    g_fire_spread_direction = random_byte() & 7;
}

void building_maintenance_update_burning_ruins(void) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Burning Ruins Update");
    int climate = scenario_property_climate();
    int recalculate_terrain = 0;
    building_list_burning_clear();
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if ((b->state != BUILDING_STATE_VALID && b->state != BUILDING_STATE_MOTHBALLED)
            || b->type != BUILDING_BURNING_RUIN)
            continue;

        if (b->fire_duration < 0)
            b->fire_duration = 0;

        b->fire_duration++;
        if (b->fire_duration > 32) {
            game_undo_disable();
            b->state = BUILDING_STATE_RUBBLE;
            map_building_tiles_set_rubble(i, b->tile.x(), b->tile.y(), b->size);
            recalculate_terrain = 1;
            continue;
        }
        if (b->ruin_has_plague)
            continue;

        building_list_burning_add(i);
        if (climate == CLIMATE_DESERT) {
            if (b->fire_duration & 3) // check spread every 4 ticks
                continue;
        } else {
            if (b->fire_duration & 7) // check spread every 8 ticks
                continue;
        }
        if ((b->map_random_7bit & 3) != (random_byte() & 3))
            continue;

        int dir1 = g_fire_spread_direction - 1;
        if (dir1 < 0)
            dir1 = 7;
        int dir2 = g_fire_spread_direction + 1;
        if (dir2 > 7)
            dir2 = 0;

        int grid_offset = b->tile.grid_offset();
        int next_building_id = map_building_at(grid_offset + map_grid_direction_delta(g_fire_spread_direction));
        if (next_building_id && !building_get(next_building_id)->fire_proof) {
            building_destroy_by_fire(building_get(next_building_id));
            recalculate_terrain = 1;
        } else {
            next_building_id = map_building_at(grid_offset + map_grid_direction_delta(dir1));
            if (next_building_id && !building_get(next_building_id)->fire_proof) {
                building_destroy_by_fire(building_get(next_building_id));
                recalculate_terrain = 1;
            } else {
                next_building_id = map_building_at(grid_offset + map_grid_direction_delta(dir2));
                if (next_building_id && !building_get(next_building_id)->fire_proof) {
                    building_destroy_by_fire(building_get(next_building_id));
                    recalculate_terrain = 1;
                }
            }
        }
    }
    if (recalculate_terrain)
        map_routing_update_land();
}

int building_maintenance_get_closest_burning_ruin(map_point tile, int* distance) {
    int min_free_building_id = 0;
    int min_occupied_building_id = 0;
    int min_occupied_dist = *distance = 10000;

    std::span<int> burning_ruins = building_list_burning_items();
    for (const auto &building_id: burning_ruins) {
        building* b = building_get(building_id);
        if ((b->state == BUILDING_STATE_VALID || b->state == BUILDING_STATE_MOTHBALLED)
            && b->type == BUILDING_BURNING_RUIN && !b->ruin_has_plague && b->distance_from_entry) {

            int dist = calc_maximum_distance(tile, b->tile);
            if (b->has_figure(3)) {
                if (dist < min_occupied_dist) {
                    min_occupied_dist = dist;
                    min_occupied_building_id = building_id;
                }
            } else if (dist < *distance) {
                *distance = dist;
                min_free_building_id = building_id;
            }
        }
    }

    if (!min_free_building_id && min_occupied_dist <= 2) {
        min_free_building_id = min_occupied_building_id;
        *distance = 2;
    }
    return min_free_building_id;
}

static void collapse_building(building* b) {
    //    return; // TODO: get fire values and logic working before enabling
    city_message_apply_sound_interval(MESSAGE_CAT_COLLAPSE);
    if (!tutorial_handle_collapse()) {
        city_message_post_with_popup_delay(MESSAGE_CAT_COLLAPSE,
                                           MESSAGE_COLLAPSED_BUILDING,
                                           b->type,
                                           b->tile.grid_offset());
    }

    game_undo_disable();
    building_destroy_by_collapse(b);
}

static void fire_building(building* b) {
    //    return; // TODO: get fire values and logic working before enabling
    city_message_apply_sound_interval(MESSAGE_CAT_FIRE);
    if (!tutorial_handle_fire()) {
        city_message_post_with_popup_delay(MESSAGE_CAT_FIRE, MESSAGE_FIRE, b->type, b->tile.grid_offset());
    }

    building_destroy_by_fire(b);
}

void building_maintenance_check_fire_collapse(void) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Fire Collapse Update");
    city_sentiment_reset_protesters_criminals();

    int climate = scenario_property_climate();
    int recalculate_terrain = 0;
    random_generate_next();
    int random_global = random_byte() & 7;
    int max_id = building_get_highest_id();
    for (int i = 1; i <= max_id; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || b->fire_proof) {
            continue;
        }

        if (b->type == BUILDING_SENET_HOUSE && b->prev_part_building_id) {
            continue;
        }

        const model_building* model = model_get_building(b->type);

        /////// COLLAPSE
        int damage_risk_increase = model->damage_risk;
        if (tutorial_extra_damage_risk()) {
            damage_risk_increase += 5;
        }

        b->damage_risk += damage_risk_increase;
        if (b->damage_risk > 1000) {
            collapse_building(b);
            recalculate_terrain = 1;
            continue;
        }

        /////// FIRE
        int random_building = (i + map_random_get(b->tile.grid_offset())) & 7;
        if (random_building == random_global) {
            b->fire_risk += model->fire_risk;
            int expected_fire_risk = 0;
            if (!b->house_size) {
                expected_fire_risk += 50;
            } else if (b->house_population <= 0) {
                expected_fire_risk = 0;
            } else if (b->subtype.house_level <= HOUSE_LARGE_SHACK) {
                expected_fire_risk += 100;
            } else if (b->subtype.house_level <= HOUSE_GRAND_INSULA) {
                expected_fire_risk += 50;
            } else {
                expected_fire_risk += 20;
            }

            if (tutorial_extra_fire_risk()) {
                expected_fire_risk += 50;
            }

            expected_fire_risk = b->get_fire_risk(expected_fire_risk);
            b->fire_risk += expected_fire_risk;
            //            if (climate == CLIMATE_NORTHERN)
            //                b->fire_risk = 0;
            //            else if (climate == CLIMATE_DESERT)
            //                b->fire_risk += 30;
        }
        if (b->fire_risk > 1000) {
            fire_building(b);
            recalculate_terrain = 1;
        }
    }

    if (recalculate_terrain) {
        map_routing_update_land();
    }
}

void building_maintenance_check_rome_access(void) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Check Rome Access");
    map_point& entry_point = city_map_entry_point();
    map_routing_calculate_distances(entry_point);
    int problem_grid_offset = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID)
            continue;

        if (b->house_size) {
            OZZY_PROFILER_SECTION("Game/Run/Tick/Check Rome Access/House");
            map_point road_tile;
            if (!map_closest_road_within_radius(b->tile.x(), b->tile.y(), b->size, 2, road_tile)) {
                // no road: eject people
                b->distance_from_entry = 0;
                b->house_unreachable_ticks++;
                if (b->house_unreachable_ticks > 4) {
                    if (b->house_population) {
                        figure_create_homeless(b->tile.x(), b->tile.y(), b->house_population);
                        b->house_population = 0;
                        b->house_unreachable_ticks = 0;
                    }
                    b->state = BUILDING_STATE_UNDO;
                }
            } else if (map_routing_distance(road_tile.grid_offset())) {
                // reachable from rome
                OZZY_PROFILER_SECTION("Game/Run/Tick/Check Rome Access/House/map_routing_distance");
                b->distance_from_entry = map_routing_distance(road_tile.grid_offset());
                b->house_unreachable_ticks = 0;
            } else if (map_closest_reachable_road_within_radius(b->tile.x(), b->tile.y(), b->size, 2, road_tile)) {
                b->distance_from_entry = map_routing_distance(road_tile.grid_offset());
                b->house_unreachable_ticks = 0;
            } else {
                // no reachable road in radius
                if (!b->house_unreachable_ticks)
                    problem_grid_offset = b->tile.grid_offset();

                b->house_unreachable_ticks++;
                if (b->house_unreachable_ticks > 8) {
                    b->distance_from_entry = 0;
                    b->house_unreachable_ticks = 0;
                    b->state = BUILDING_STATE_UNDO;
                }
            }
        } else if (b->type == BUILDING_STORAGE_YARD) {
            OZZY_PROFILER_SECTION("Game/Run/Tick/Check Rome Access/Storageyard");
            if (!city_buildings_get_trade_center()) {
                city_buildings_set_trade_center(i);
            }

            b->distance_from_entry = 0;
            int x_road, y_road;
            int road_grid_offset = map_road_to_largest_network_rotation(b->subtype.orientation, b->tile.x(), b->tile.y(), 3, &x_road, &y_road);
            if (road_grid_offset >= 0) {
                b->road_network_id = map_road_network_get(road_grid_offset);
                b->distance_from_entry = map_routing_distance(road_grid_offset);
                b->road_access.x(x_road);
                b->road_access.y(y_road);
            }
        } else if (b->type == BUILDING_STORAGE_YARD_SPACE) {
            OZZY_PROFILER_SECTION("Game/Run/Tick/Check Rome Access/Storageyard Space");
            b->distance_from_entry = 0;
            building* main_building = b->main();
            b->road_network_id = main_building->road_network_id;
            b->distance_from_entry = main_building->distance_from_entry;
            b->road_access = main_building->road_access;

        } else if (b->type == BUILDING_SENET_HOUSE) {
            OZZY_PROFILER_SECTION("Game/Run/Tick/Check Rome Access/Senet");
            b->distance_from_entry = 0;
            int x_road, y_road;
            int road_grid_offset = map_road_to_largest_network_hippodrome(b->tile.x(), b->tile.y(), &x_road, &y_road);
            if (road_grid_offset >= 0) {
                b->road_network_id = map_road_network_get(road_grid_offset);
                b->distance_from_entry = map_routing_distance(road_grid_offset);
                b->road_access.x(x_road);
                b->road_access.y(y_road);
            }
        } else { // other building
            OZZY_PROFILER_SECTION("Game/Run/Tick/Check Rome Access/Other");
            b->distance_from_entry = 0;
            int x_road, y_road;
            int road_grid_offset = map_road_to_largest_network(b->tile.x(), b->tile.y(), b->size, &x_road, &y_road);
            if (road_grid_offset >= 0) {
                b->road_network_id = map_road_network_get(road_grid_offset);
                b->distance_from_entry = map_routing_distance(road_grid_offset);
                b->road_access.x(x_road);
                b->road_access.y(y_road);
            }
        }
    }
    
    {
        OZZY_PROFILER_SECTION("Game/Run/Tick/Check Rome Access/Exit Check");
        map_point& exit_point = city_map_exit_point();
        //if (!map_routing_distance(exit_point.grid_offset())) {
        //    // no route through city
        //    if (city_population() <= 0) {
        //        return;
        //    }
        //    map_routing_delete_first_wall_or_aqueduct(entry_point.x(), entry_point.y());
        //    map_routing_delete_first_wall_or_aqueduct(exit_point.x(), exit_point.y());
        //    map_routing_calculate_distances(entry_point.x(), entry_point.y());
        //    
        //    map_tiles_update_all_walls();
        //    map_tiles_update_all_aqueducts(0);
        //    map_tiles_update_all_empty_land();
        //    map_tiles_update_all_meadow();
        //    
        //    map_routing_update_land();
        //    map_routing_update_walls();
        //    
        //    if (map_routing_distance(exit_point.grid_offset())) {
        //        city_message_post(true, MESSAGE_ROAD_TO_ROME_OBSTRUCTED, 0, 0);
        //        game_undo_disable();
        //        return;
        //    }
        //    // building_destroy_last_placed();
        //}
    } // else

    if (problem_grid_offset) {
        // parts of city disconnected
        city_warning_show(WARNING_CITY_BOXED_IN);
        city_warning_show(WARNING_CITY_BOXED_IN_PEOPLE_WILL_PERISH);
        // TODO: TEMP
        //        city_view_go_to_grid_offset(problem_grid_offset);
    }
}
