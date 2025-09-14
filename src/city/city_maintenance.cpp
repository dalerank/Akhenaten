#include "city_maintenance.h"

#include "building/building_house.h"
#include "building/building_temple_complex.h"
#include "grid/random.h"
#include "grid/road_access.h"
#include "grid/road_network.h"
#include "grid/routing/routing_terrain.h"
#include "city/city_buildings.h"
#include "core/profiler.h"
#include "core/random.h"
#include "scenario/scenario.h"
#include "figuretype/figure_homeless.h"
#include "city/city.h"
#include "game/game_events.h"
#include "city/city_warnings.h"
#include "city/city_message.h"
#include "grid/routing/routing.h"
#include "grid/routing/routing_terrain.h"
#include "game/game_config.h"
#include "game/undo.h"

void fire_building(building *b) {
    city_message_apply_sound_interval(MESSAGE_CAT_FIRE);
    city_message_post_with_popup_delay(MESSAGE_CAT_FIRE, false, MESSAGE_FIRE, b->type, b->tile.grid_offset());

    game_undo_disable();
    b->destroy_by_fire();
}

void city_maintenance_t::collapse_building(building *b) {
    city_message_apply_sound_interval(MESSAGE_CAT_COLLAPSE);
    city_message_post_with_popup_delay(MESSAGE_CAT_COLLAPSE, false, MESSAGE_COLLAPSED_BUILDING, b->type, b->tile.grid_offset());

    game_undo_disable();
    b->destroy_by_collapse();
}


void city_maintenance_t::flood_building(building *b) {
    city_message_apply_sound_interval(MESSAGE_CAT_COLLAPSE);
    city_message_post_with_popup_delay(MESSAGE_CAT_COLLAPSE, false, MESSAGE_COLLAPSED_BUILDING, b->type, b->tile.grid_offset());

    game_undo_disable();
    b->destroy_by_flooded();
}

void city_maintenance_t::init() {
    events::subscribe([this] (event_advance_month) {
        update_fire_direction();
    });
}

void city_maintenance_t::update_fire_direction() {
    fire_spread_direction = random_byte() & 7;
}

void city_maintenance_t::check_fire_collapse() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Fire Collapse Update");

    int climate = scenario_property_climate();
    int recalculate_terrain = 0;
    random_generate_next();
    int random_global = random_byte() & 7;

    buildings_valid_do([&] (building &b) {
        const model_building *model = model_get_building(b.type);

        /////// COLLAPSE
        int damage_risk_increase = model->damage_risk;
        damage_risk_increase += scenario_additional_damage(b.type, e_damage_collapse);

        if (!b.damage_proof) {
            b.damage_risk += damage_risk_increase;
        }

        if (b.damage_risk > 1000) {
            collapse_building(&b);
            recalculate_terrain = 1;
            return;
        }

        /////// FIRE
        int random_building = (b.id + map_random_get(b.tile)) & 7;
        if (!b.fire_proof && random_building == random_global) {
            int expected_fire_risk = building_impl::params(b.type).fire_risk_update;
            expected_fire_risk += model->fire_risk;

            expected_fire_risk += scenario_additional_damage(b.type, e_damage_fire);
            expected_fire_risk = b.dcast()->get_fire_risk(expected_fire_risk);
            b.fire_risk += expected_fire_risk;
            //            if (climate == CLIMATE_NORTHERN)
            //                b->fire_risk = 0;
            //            else if (climate == CLIMATE_DESERT)
            //                b->fire_risk += 30;
        }

        if (b.fire_risk > 1000) {
            b.destroy_by_fire();
            recalculate_terrain = 1;
        }
    });

    if (recalculate_terrain) {
        map_routing_update_land();
    }
}

void city_maintenance_t::check_kingdome_access() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Check Road Access");
    tile2i entry_point = g_city.map.entry_point;
    map_routing_calculate_distances(entry_point);
    int problem_grid_offset = 0;
    buildings_valid_do([&problem_grid_offset] (building &b) {
        auto house = b.dcast_house();
        if (house && house->hsize() > 0) {
            OZZY_PROFILER_SECTION("Game/Run/Tick/Check Road Access/House");
            tile2i road_tile = map_closest_road_within_radius(b, 2);
            auto &housed = b.dcast_house()->runtime_data();
            if (!road_tile.valid()) {
                // no road: eject people
                b.distance_from_entry = 0;
                housed.unreachable_ticks++;
                if (housed.unreachable_ticks > 4) {
                    if (housed.population > 0) {
                        events::emit(event_create_homeless{ b.tile, housed.population, SOURCE_LOCATION });
                        housed.population = 0;
                        housed.unreachable_ticks = 0;
                    }
                    b.state = BUILDING_STATE_UNDO;
                }
            } else if (map_routing_distance(road_tile)) {
                // reachable from rome
                OZZY_PROFILER_SECTION("Game/Run/Tick/Check Road Access/House/map_routing_distance");
                b.distance_from_entry = map_routing_distance(road_tile);
                b.road_network_id = map_road_network_get(road_tile);
                housed.unreachable_ticks = 0;
            } else if (map_closest_reachable_road_within_radius(b.tile, b.size, 2, road_tile)) {
                b.distance_from_entry = map_routing_distance(road_tile);
                b.road_network_id = map_road_network_get(road_tile);
                housed.unreachable_ticks = 0;
            } else {
                // no reachable road in radius
                if (!housed.unreachable_ticks) {
                    problem_grid_offset = b.tile.grid_offset();
                }

                housed.unreachable_ticks++;
                if (housed.unreachable_ticks > 8) {
                    b.distance_from_entry = 0;
                    housed.unreachable_ticks = 0;
                    b.state = BUILDING_STATE_UNDO;
                }
            }
        } else if (b.type == BUILDING_STORAGE_YARD) {
            OZZY_PROFILER_SECTION("Game/Run/Tick/Check Road Access/Storageyard");
            if (!city_buildings_get_trade_center()) {
                city_buildings_set_trade_center(b.id);
            }

            b.distance_from_entry = 0;
            const bool closest_road = !!game_features::gameplay_building_road_closest;
            tile2i road = map_road_to_largest_network_rotation(b.orientation, b.tile, 3, closest_road);
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
            building *main_building = b.main();
            b.road_network_id = main_building->road_network_id;
            b.distance_from_entry = main_building->distance_from_entry;
            b.road_access = main_building->road_access;

        } else if (b.type == BUILDING_SENET_HOUSE) {
            OZZY_PROFILER_SECTION("Game/Run/Tick/Check Road Access/Senet");
            b.distance_from_entry = 0;
            const bool closest_road = !!game_features::gameplay_building_road_closest;
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
        } else if (building_type_any_of(b, { BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_PTAH, BUILDING_TEMPLE_COMPLEX_SETH, BUILDING_TEMPLE_COMPLEX_BAST })) {
            if (b.is_main()) {
                auto complex = b.dcast_temple_complex();
                int orientation = (5 - (complex->runtime_data().variant / 2)) % 4;
                b.has_road_access = map_has_road_access_temple_complex(b.tile, orientation, false, &b.road_access);
                b.road_network_id = map_road_network_get(b.road_access);
                b.distance_from_entry = map_routing_distance(b.road_access);
            }
        } else { // other building
            OZZY_PROFILER_SECTION("Game/Run/Tick/Check Road Access/Other");
            b.distance_from_entry = 0;
            bool closest_road = !!game_features::gameplay_building_road_closest;
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
        events::emit(event_city_warning{ "#restore_access_or_sector_will_stagnate"});
        events::emit(event_city_warning{"#city_isolated_from_kingdom_road"});
        // TODO: TEMP
        //        city_view_go_to_grid_offset(problem_grid_offset);
    }
}