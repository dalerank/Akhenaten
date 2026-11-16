#include "building_police_station.h"

#include "building/building_storage_yard.h"
#include "city/buildings.h"
#include "city/city_buildings.h"
#include "core/calc.h"
#include "figuretype/figure_constable.h"
#include "game/game_config.h"
#include "grid/road_access.h"
#include "grid/road_network.h"
#include "js/js_game.h"

BUILDING_RUNTIME_DATA_IMPL(building_police_station)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_police_station);

bool building_police_station::request_weapons_if_need() {
    auto& d = runtime_data();
    if (d.weapon_requested_this_month) {
        return false;
    }

    if (stored_amount(RESOURCE_WEAPONS) > 50) {
        return false;
    }

    int min_dist = 10000;
    building_id closest_warehouse_id = 0;
    const int road_network_id = road_network();
    d.weapon_requested_this_month = true;

    buildings_valid_do(
      [&](building& b) {
          building_storage_yard* warehouse = b.dcast_storage_yard();

          if (!warehouse->has_road_access() || warehouse->base.distance_from_entry <= 0) {
              return;
          }

          if (warehouse->road_network() != road_network_id) {
              return;
          }

          int weapons_amount = warehouse->amount(RESOURCE_WEAPONS);
          if (weapons_amount > 50) {
              int dist = calc_distance_with_penalty(warehouse->tile(), base.tile, warehouse->base.distance_from_entry,
                base.distance_from_entry);
              if (dist < min_dist) {
                  min_dist = dist;
                  closest_warehouse_id = warehouse->id();
              }
          }
      },
      BUILDING_STORAGE_YARD);

    if (closest_warehouse_id > 0) {
        figure* f = create_roaming_figure(FIGURE_CONSTABLE, (e_figure_action)ACTION_74_CONSTABLE_REQUESTING_WEAPONS,
          BUILDING_SLOT_SERVICE);
        if (f) {
            building* warehouse = building_get(closest_warehouse_id);
            tile2i warehouse_tile;
            if (warehouse->has_road_access) {
                map_point_store_result(warehouse->road_access, warehouse_tile);
            } else {
                warehouse_tile = map_has_road_access_rotation(warehouse->orientation, warehouse->tile, 3);
            }
            if (warehouse_tile.valid()) {
                f->destination_tile = warehouse_tile;
                f->set_destination(closest_warehouse_id);
            }
        }
        return true;
    }

    return false;
}

void building_police_station::spawn_figure() {
    check_labor_problem();
    if (has_figure(BUILDING_SLOT_SERVICE) || !has_road_access()) {
        return;
    }

    common_spawn_labor_seeker(current_params().min_houses_coverage);

    const int spawn_delay = figure_spawn_timer();
    if (spawn_delay == -1) {
        return;
    }

    base.figure_spawn_delay++;
    if (base.figure_spawn_delay > spawn_delay) {
        base.figure_spawn_delay = 0;
        if (game_features::gameplay_change_police_weapons.to_bool()) {
            if (request_weapons_if_need()) {
                return;
            }
            if (stored_amount(RESOURCE_WEAPONS) > 0) {
                consume_resource(RESOURCE_WEAPONS, 1);
            }
        }
        create_roaming_figure(FIGURE_CONSTABLE, (e_figure_action)ACTION_70_LAW_WALKER_CREATED, BUILDING_SLOT_SERVICE);
    }
}

void building_police_station::update_month() {
    building_impl::update_month();
    runtime_data().weapon_requested_this_month = false;
}

bool building_police_station::add_resource(e_resource resource, int amount, figure_id fid) {
    if (resource != RESOURCE_WEAPONS || !game_features::gameplay_change_police_weapons.to_bool()) {
        return false;
    }
    store_resource(RESOURCE_WEAPONS, amount);
    return true;
}
