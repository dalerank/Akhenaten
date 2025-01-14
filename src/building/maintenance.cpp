#include "maintenance.h"

#include "building/building.h"
#include "building/building_house.h"
#include "building/building_burning_ruin.h"
#include "building/destruction.h"
#include "building/list.h"
#include "city/buildings.h"
#include "city/city.h"
#include "city/message.h"
#include "city/population.h"
#include "city/sentiment.h"
#include "city/warning.h"
#include "core/calc.h"
#include "core/custom_span.hpp"
#include "core/random.h"
#include "core/profiler.h"
#include "figuretype/figure_homeless.h"
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
#include "sound/effect.h"
#include "config/config.h"

int g_fire_spread_direction = 0;

void building_maintenance_update_fire_direction() {
    g_fire_spread_direction = random_byte() & 7;
}

int building_maintenance_fire_direction() {
    return g_fire_spread_direction;
}

void building_maintenance_update_burning_ruins() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Burning Ruins Update");
    int climate = scenario_property_climate();
    bool recalculate_terrain = 0;

    building_list_burning_clear();
    buildings_valid_do([&recalculate_terrain] (building &b) {
        auto ruin = b.dcast_burning_ruin();
        building_list_burning_add(b.id);
        recalculate_terrain |= ruin->update();
    }, BUILDING_BURNING_RUIN);

    if (recalculate_terrain) {
        map_routing_update_land();
    }
}

std::pair<int, tile2i> building_maintenance_get_closest_burning_ruin(tile2i tile) {
    building *near_ruin = nullptr;
    int distance = 10000;

    //custom_span<int>  = building_list_burning_items();
    std::vector<building *> burning_ruins;
    buildings_valid_do([&burning_ruins] (building &b) {
        if (!(b.state == BUILDING_STATE_VALID || b.state == BUILDING_STATE_MOTHBALLED || b.has_plague)) {
            return;
        }

        if (b.has_figure(3)) {
            return;
        }

        burning_ruins.push_back(&b);
    }, BUILDING_BURNING_RUIN);

    std::sort(burning_ruins.begin(), burning_ruins.end(), [&tile] (auto &lhs, auto &rhs) {
        int lhs_dist = calc_maximum_distance(tile, lhs->tile);
        int rhs_dist = calc_maximum_distance(tile, rhs->tile);
        return (lhs_dist < rhs_dist);
    });

    for (const auto &b: burning_ruins) {
        grid_tiles adjacent = map_grid_get_tiles(b, 1);
        for (const auto &t : adjacent) {
            if (map_routing_citizen_can_travel_over_land(tile, t)) {
                return {b->id, t};
            }
        }
    }

    return {0, tile2i(-1, -1)};
}

static void collapse_building(building* b) {
    city_message_apply_sound_interval(MESSAGE_CAT_COLLAPSE);
    if (!tutorial_handle_collapse()) {
        city_message_post_with_popup_delay(MESSAGE_CAT_COLLAPSE, false, MESSAGE_COLLAPSED_BUILDING, b->type, b->tile.grid_offset());
    }

    game_undo_disable();
    building_destroy_by_collapse(b);
}

static void fire_building(building* b) {
    city_message_apply_sound_interval(MESSAGE_CAT_FIRE);
    if (!tutorial_handle_fire()) {
        city_message_post_with_popup_delay(MESSAGE_CAT_FIRE, false, MESSAGE_FIRE, b->type, b->tile.grid_offset());
    }

    game_undo_disable();
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

    buildings_valid_do([&] (building &b) {
        if (b.fire_proof) {
            return;
        }

        const model_building *model = model_get_building(b.type);

        /////// COLLAPSE
        int damage_risk_increase = model->damage_risk;
        if (tutorial_extra_damage_risk()) {
            damage_risk_increase += 5;
        }

        if (!b.damage_proof) {
            b.damage_risk += damage_risk_increase;
        }

        if (b.damage_risk > 1000) {
            collapse_building(&b);
            recalculate_terrain = 1;
            return;
        }

        /////// FIRE
        int random_building = (b.id + map_random_get(b.tile.grid_offset())) & 7;
        if (random_building == random_global) {
            b.fire_risk += model->fire_risk;
            int expected_fire_risk = 0;
            if (!b.house_size) {
                expected_fire_risk += 50;
            } else if (b.house_population <= 0) {
                expected_fire_risk = 0;
            } else if (b.subtype.house_level <= HOUSE_COMMON_SHANTY) {
                expected_fire_risk += 100;
            } else if (b.subtype.house_level <= HOUSE_COMMON_MANOR) {
                expected_fire_risk += 50;
            } else {
                expected_fire_risk += 20;
            }

            if (tutorial_extra_fire_risk()) {
                expected_fire_risk += 50;
            }

            expected_fire_risk = b.dcast()->get_fire_risk(expected_fire_risk);
            b.fire_risk += expected_fire_risk;
            //            if (climate == CLIMATE_NORTHERN)
            //                b->fire_risk = 0;
            //            else if (climate == CLIMATE_DESERT)
            //                b->fire_risk += 30;
        }
        if (b.fire_risk > 1000) {
            fire_building(&b);
            recalculate_terrain = 1;
        }
    });

    if (recalculate_terrain) {
        map_routing_update_land();
    }
}

void building_maintenance_check_kingdome_access() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Check Road Access");
    tile2i entry_point = g_city.map.entry_point;
    map_routing_calculate_distances(entry_point);
    int problem_grid_offset = 0;
    buildings_valid_do( [&problem_grid_offset] (building &b) {
        if (b.house_size) {
            OZZY_PROFILER_SECTION("Game/Run/Tick/Check Road Access/House");
            tile2i road_tile = map_closest_road_within_radius(b, 2);
            if (!road_tile.valid()) {
                // no road: eject people
                b.distance_from_entry = 0;
                b.house_unreachable_ticks++;
                if (b.house_unreachable_ticks > 4) {
                    if (b.house_population > 0) {
                        figure_create_homeless(b.tile, b.house_population);
                        b.house_population = 0;
                        b.house_unreachable_ticks = 0;
                    }
                    b.state = BUILDING_STATE_UNDO;
                }
            } else if (map_routing_distance(road_tile)) {
                // reachable from rome
                OZZY_PROFILER_SECTION("Game/Run/Tick/Check Road Access/House/map_routing_distance");
                b.distance_from_entry = map_routing_distance(road_tile);
                b.road_network_id = map_road_network_get(road_tile);
                b.house_unreachable_ticks = 0;
            } else if (map_closest_reachable_road_within_radius(b.tile, b.size, 2, road_tile)) {
                b.distance_from_entry = map_routing_distance(road_tile);
                b.road_network_id = map_road_network_get(road_tile);
                b.house_unreachable_ticks = 0;
            } else {
                // no reachable road in radius
                if (!b.house_unreachable_ticks) {
                    problem_grid_offset = b.tile.grid_offset();
                }

                b.house_unreachable_ticks++;
                if (b.house_unreachable_ticks > 8) {
                    b.distance_from_entry = 0;
                    b.house_unreachable_ticks = 0;
                    b.state = BUILDING_STATE_UNDO;
                }
            }
        } else if (b.type == BUILDING_STORAGE_YARD) {
            OZZY_PROFILER_SECTION("Game/Run/Tick/Check Road Access/Storageyard");
            if (!city_buildings_get_trade_center()) {
                city_buildings_set_trade_center(b.id);
            }

            b.distance_from_entry = 0;
            bool closest_road = config_get(CONFIG_GP_CH_BUILDING_CLOSEST_ROAD) > 0;
            tile2i road = map_road_to_largest_network_rotation(b.subtype.orientation, b.tile, 3, closest_road);
            if (road.x() >= 0) {
                b.road_network_id = map_road_network_get(road);
                b.distance_from_entry = map_routing_distance(road);
                b.road_access = road;
                b.has_road_access = true;
            } else {
                b.road_access = map_get_road_access_tile(b.tile, 3);
                b.has_road_access = b.road_access.valid();
            }
        } else if (b.type == BUILDING_STORAGE_ROOM) {
            OZZY_PROFILER_SECTION("Game/Run/Tick/Check Road Access/Storageyard Space");
            b.distance_from_entry = 0;
            building* main_building = b.main();
            b.road_network_id = main_building->road_network_id;
            b.distance_from_entry = main_building->distance_from_entry;
            b.road_access = main_building->road_access;

        } else if (b.type == BUILDING_SENET_HOUSE) {
            OZZY_PROFILER_SECTION("Game/Run/Tick/Check Road Access/Senet");
            b.distance_from_entry = 0;
            int x_road, y_road;
            int road_grid_offset = map_road_to_largest_network_hippodrome(b.tile.x(), b.tile.y(), &x_road, &y_road);
            if (road_grid_offset >= 0) {
                b.road_network_id = map_road_network_get(road_grid_offset);
                b.distance_from_entry = map_routing_distance(road_grid_offset);
                b.road_access.x(x_road);
                b.road_access.y(y_road);
            }
        } else if (building_type_any_of(b, BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_PTAH, BUILDING_TEMPLE_COMPLEX_SETH,BUILDING_TEMPLE_COMPLEX_BAST)) {
            if (b.is_main()) {
                int orientation = (5 - (b.data.monuments.variant / 2)) % 4;
                b.has_road_access = map_has_road_access_temple_complex(b.tile, orientation, false, &b.road_access);
                b.road_network_id = map_road_network_get(b.road_access);
                b.distance_from_entry = map_routing_distance(b.road_access);
            }
        } else { // other building
            OZZY_PROFILER_SECTION("Game/Run/Tick/Check Road Access/Other");
            b.distance_from_entry = 0;
            bool closest_road = config_get(CONFIG_GP_CH_BUILDING_CLOSEST_ROAD) > 0;
            tile2i road = map_road_to_largest_network(b.tile, b.size, closest_road);
            if (road.valid()) {
                b.road_network_id = map_road_network_get(road);
                b.distance_from_entry = map_routing_distance(road);
                b.road_access = road;
                b.has_road_access = true;
            } else {
                b.road_access = map_get_road_access_tile(b.tile, b.size);
                b.has_road_access = b.road_access.valid();
            }
        }
    });
    
    {
        //OZZY_PROFILER_SECTION("Game/Run/Tick/Check Rome Access/Exit Check");
        //map_point& exit_point = city_map_exit_point();
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
