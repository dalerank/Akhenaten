#include "dock.h"

#include "building/building_bazaar.h"
#include "building/building.h"
#include "building/building_type.h"
#include "grid/water.h"
#include "city/buildings.h"
#include "city/resource.h"
#include "core/profiler.h"
#include "empire/empire_city.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/routing/routing.h"
#include "grid/terrain.h"
#include "scenario/map.h"

int building_dock_count_idle_dockers(building* dock) {
    int num_idle = 0;
    for (int i = 0; i < 3; i++) {
        if (dock->data.dock.docker_ids[i]) {
            figure* f = figure_get(dock->data.dock.docker_ids[i]);
            if (f->action_state == FIGURE_ACTION_132_DOCKER_IDLING
                || f->action_state == FIGURE_ACTION_133_DOCKER_IMPORT_QUEUE) {
                num_idle++;
            }
        }
    }
    return num_idle;
}

void building_river_update_open_water_access() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Oper Water Access Update");
    tile2i river_entry = scenario_map_river_entry();
    map_routing_calculate_distances_water_boat(river_entry);

    buildings_valid_do([] (building &b) {
        if (!building_type_any_of(b, BUILDING_DOCK, BUILDING_FISHING_WHARF, BUILDING_SHIPYARD)) {
            return;
        }

        bool found = map_terrain_is_adjacent_to_open_water(b.tile, 3);
        if (found) {
            b.has_water_access = true;
            b.has_open_water_access = true;
            auto ppoints = map_water_docking_points(&b);
            b.data.dock.dock_tiles[0] = ppoints.point_a.grid_offset();
            b.data.dock.dock_tiles[1] = ppoints.point_b.grid_offset();
        } else {
            b.has_water_access = false;
            b.has_open_water_access = false;
            b.data.dock.dock_tiles[0] = -1;
            b.data.dock.dock_tiles[1] = -1;
        }
    });
}

bool building_dock_is_connected_to_open_water(tile2i tile) {
    tile2i river_entry = scenario_map_river_entry();
    map_routing_calculate_distances_water_boat(river_entry);
    return map_terrain_is_adjacent_to_open_water(tile, 3);
}

int building_dock_accepts_ship(int ship_id, int dock_id) {
    building* dock = building_get(dock_id);
    figure* f = figure_get(ship_id);

    empire_city* city = empire_city_get(f->empire_city_id);
    for (int resource = RESOURCE_GRAIN; resource < RESOURCES_MAX; resource++) {
        if (city->sells_resource[resource] || city->buys_resource[resource]) {
            if (!is_good_accepted(resource - 1, dock)) {
                dock_id = 0;
                return 0;
            }
        }
    }
    return 1;
}

int building_dock_get_free_destination(int ship_id, tile2i* tile) {
    if (!city_buildings_has_working_dock())
        return 0;

    int dock_id = 0;
    for (int i = 0; i < 10; i++) {
        dock_id = city_buildings_get_working_dock(i);
        if (!dock_id)
            continue;
        if (!building_dock_accepts_ship(ship_id, dock_id)) {
            dock_id = 0;
            continue;
        }

        building* dock = building_get(dock_id);

        if (!dock->data.dock.trade_ship_id || dock->data.dock.trade_ship_id == ship_id)
            break;
    }
    // BUG: when 10 docks in city, always takes last one... regardless of whether it is free
    if (dock_id <= 0)
        return 0;

    building* dock = building_get(dock_id);
    int dx, dy;
    switch (dock->data.dock.orientation) {
    case 0:
        dx = 1;
        dy = -1;
        break;
    case 1:
        dx = 3;
        dy = 1;
        break;
    case 2:
        dx = 1;
        dy = 3;
        break;
    default:
        dx = -1;
        dy = 1;
        break;
    }
    tile2i dock_tile = dock->tile.shifted(dx, dy);
    map_point_store_result(dock_tile, *tile);
    dock->data.dock.trade_ship_id = ship_id;
    return dock_id;
}

int building_dock_get_queue_destination(int ship_id, tile2i* tile) {
    if (!city_buildings_has_working_dock())
        return 0;

    // first queue position
    for (int i = 0; i < 10; i++) {
        int dock_id = city_buildings_get_working_dock(i);
        if (!dock_id)
            continue;
        if (!building_dock_accepts_ship(ship_id, dock_id)) {
            dock_id = 0;
            continue;
        }
        building* dock = building_get(dock_id);
        int dx, dy;
        switch (dock->data.dock.orientation) {
        case 0:
            dx = 2;
            dy = -2;
            break;
        case 1:
            dx = 4;
            dy = 2;
            break;
        case 2:
            dx = 2;
            dy = 4;
            break;
        default:
            dx = -2;
            dy = 2;
            break;
        }
        tile2i dock_tile = dock->tile.shifted(dx, dy);
        map_point_store_result(dock_tile, *tile);

        if (!map_has_figure_at(tile->grid_offset())) {
            return dock_id;
        }
    }
    // second queue position
    for (int i = 0; i < 10; i++) {
        int dock_id = city_buildings_get_working_dock(i);
        if (!dock_id)
            continue;
        if (!building_dock_accepts_ship(ship_id, dock_id)) {
            dock_id = 0;
            continue;
        }
        building* dock = building_get(dock_id);
        int dx, dy;
        switch (dock->data.dock.orientation) {
        case 0:
            dx = 2;
            dy = -3;
            break;
        case 1:
            dx = 5;
            dy = 2;
            break;
        case 2:
            dx = 2;
            dy = 5;
            break;
        default:
            dx = -3;
            dy = 2;
            break;
        }
        tile2i dock_tile = dock->tile.shifted(dx, dy);
        map_point_store_result(dock_tile, *tile);
        if (!map_has_figure_at(tile->grid_offset())) {
            return dock_id;
        }
    }
    return 0;
}
