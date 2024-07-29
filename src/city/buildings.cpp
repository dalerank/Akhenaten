#include "buildings.h"

#include "building/building.h"
#include "building/count.h"
#include "building/building_menu.h"
#include "core/profiler.h"
#include "grid/water.h"
#include "grid/routing/routing.h"

#include "city/city.h"

static auto &city_data = g_city;
int city_buildings_t::get_palace_id() {
    if (!palace_placed) {
        return 0;
    }

    return palace_building_id;
}

void city_buildings_add_palace(building* palace) {
    city_data.buildings.palace_placed = true;
    city_data.buildings.palace_building_id = palace->id;
    city_data.buildings.palace_point = palace->tile;
}

void city_buildings_remove_palace(building* palace) {
    building* next_palace = building_first([](auto& b) { return b.is_administration(); });
    city_data.buildings.palace_point.set(next_palace ? next_palace->tile.grid_offset() : 0);
    city_data.buildings.palace_building_id = next_palace ? next_palace->id : 0;
    city_data.buildings.palace_placed = !!next_palace;
}

bool city_buildings_has_mansion() {
    return city_data.buildings.mansion_placed;
}

int city_buildings_get_mansion_id() {
    if (!city_buildings_has_mansion()) {
        return 0;
    }

    return city_data.buildings.mansion_building_id;
}

void city_buildings_add_mansion(building* mansion) {
    city_data.buildings.mansion_placed = 1;
    if (!city_data.buildings.mansion.grid_offset()) {
        city_data.buildings.mansion_building_id = mansion->id;
        city_data.buildings.mansion.set(mansion->tile.grid_offset());
    }
}

void city_buildings_remove_mansion(building* mansion) {
    if (mansion->tile == city_data.buildings.mansion) {
        city_data.buildings.mansion.set(0);
        city_data.buildings.mansion_placed = 0;
    }
}

bool city_buildings_has_recruiter() {
    return city_data.buildings.recruiter.placed;
}

void city_buildings_add_recruiter(building* recruiter) {
    city_data.buildings.recruiter.placed = true;
    if (!city_data.buildings.recruiter.tile.grid_offset()) {
        city_data.buildings.recruiter.building_id = recruiter->id;
        city_data.buildings.recruiter.tile = recruiter->tile;
    }
}

void city_buildings_remove_recruiter(building* recruiter) {
    city_data.buildings.recruiter.placed = false;
    if (recruiter->tile == city_data.buildings.recruiter.tile) {
        city_data.buildings.recruiter.tile.set(0);
        city_data.buildings.recruiter.placed = 0;
    }
}

int city_buildings_get_recruiter() {
    return city_data.buildings.recruiter.building_id;
}

void city_buildings_set_recruiter(int building_id) {
    city_data.buildings.recruiter.building_id = building_id;
}

bool city_buildings_has_distribution_center() {
    return city_data.buildings.distribution_center_placed;
}

void city_buildings_add_distribution_center(building* center) {
    city_data.buildings.distribution_center_placed = 1;
    if (!city_data.buildings.distribution_center.grid_offset()) {
        city_data.buildings.distribution_center_building_id = center->id;
        city_data.buildings.distribution_center.set(center->tile.grid_offset());
    }
}

void city_buildings_remove_distribution_center(building* center) {
    if (center->tile.grid_offset() == city_data.buildings.distribution_center.grid_offset()) {
        city_data.buildings.distribution_center.set(0);
        //        city_data.buildings.distribution_center.grid_offset() = 0;
        //        city_data.buildings.distribution_center.x = 0;
        //        city_data.buildings.distribution_center.y = 0;
        city_data.buildings.distribution_center_placed = 0;
    }
}

int city_buildings_get_trade_center(void) {
    return city_data.buildings.trade_center_building_id;
}

void city_buildings_set_trade_center(int building_id) {
    city_data.buildings.trade_center_building_id = building_id;
}

bool city_buildings_has_senet_house() {
    return city_data.buildings.senet_house_placed;
}

void city_buildings_add_senet_house() {
    city_data.buildings.senet_house_placed = 1;
}

void city_buildings_remove_senet_house() {
    city_data.buildings.senet_house_placed = 0;
}

int city_buildings_triumphal_arch_available(void) {
    return city_data.buildings.triumphal_arches_available > city_data.buildings.triumphal_arches_placed;
}

void city_buildings_build_triumphal_arch(void) {
    city_data.buildings.triumphal_arches_placed++;
}

void city_buildings_remove_triumphal_arch(void) {
    if (city_data.buildings.triumphal_arches_placed > 0)
        city_data.buildings.triumphal_arches_placed--;
}

void city_buildings_earn_triumphal_arch(void) {
    city_data.buildings.triumphal_arches_available++;
}

void city_buildings_add_dock() {
    city_data.buildings.working_docks++;
}

void city_buildings_remove_dock() {
    city_data.buildings.working_docks--;
}

void city_buildings_add_working_wharf(int needs_fishing_boat) {
    ++city_data.buildings.working_wharfs;
    if (needs_fishing_boat)
        ++city_data.buildings.shipyard_boats_requested;
}

void city_buildings_add_working_dock(int building_id) {
    if (city_data.buildings.working_docks < 10)
        city_data.buildings.working_dock_ids[city_data.buildings.working_docks] = building_id;

    ++city_data.buildings.working_docks;
}

void city_buildings_add_working_shipyard(int building_id) {
    ++city_data.buildings.working_shipyards;
}

bool city_buildings_has_working_dock() {
    return city_data.buildings.working_docks > 0;
}

int city_buildings_get_working_dock(int index) {
    return city_data.buildings.working_dock_ids[index];
}

tile2i city_buildings_main_native_meeting_center() {
    return city_data.buildings.main_native_meeting;
}
void city_buildings_set_main_native_meeting_center(int x, int y) {
    city_data.buildings.main_native_meeting.set(x, y);
}

int city_buildings_is_mission_post_operational(void) {
    return city_data.buildings.mission_post_operational > 0;
}

void city_buildings_set_mission_post_operational(void) {
    city_data.buildings.mission_post_operational = 1;
}

tile2i city_building_get_festival_square_position() {
    return city_data.buildings.festival_square;
}

void city_buildings_add_festival_square(building* square) {
    city_data.buildings.festival_square = square->tile;
}

void city_buildings_remove_festival_square(void) {
    city_data.buildings.festival_square.set(0);
}

bool city_buildings_has_temple_complex(void) {
    return city_data.buildings.temple_complex_placed;
}

int city_buildings_get_temple_complex(void) {
    return city_data.buildings.temple_complex_id;
}

void city_buildings_add_temple_complex(building* complex) {
    city_data.buildings.temple_complex_placed = true;
    city_data.buildings.temple_complex_id = complex->id;
    building_menu_update_temple_complexes();
}

void city_buildings_remove_temple_complex() {
    city_data.buildings.temple_complex_id = 0;
    city_data.buildings.temple_complex_placed = false;
    building_menu_update_temple_complexes();
}

int city_buildings_unknown_value() {
    return city_data.buildings.unknown_value;
}

void city_t::buildings_update_open_water_access() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Open Water Access Update");
    tile2i river_entry = scenario_map_river_entry();
    if (!river_entry.valid()) {
        return;
    }

    map_routing_calculate_distances_water_boat(river_entry);

    buildings_valid_do([] (building &b) {
        bool found = map_terrain_is_adjacent_to_open_water(b.tile, b.size);
        if (found) {
            b.has_water_access = true;
            b.has_open_water_access = true;
            ferry_tiles ppoints = map_water_docking_points(b);
            b.data.dock.dock_tiles[0] = ppoints.point_a.grid_offset();
            b.data.dock.dock_tiles[1] = ppoints.point_b.grid_offset();
        } else {
            b.has_water_access = false;
            b.has_open_water_access = false;
            b.data.dock.dock_tiles[0] = -1;
            b.data.dock.dock_tiles[1] = -1;
        }
    }, BUILDING_DOCK, BUILDING_FISHING_WHARF, BUILDING_SHIPWRIGHT);
}

void city_buildings_t::update_counters() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Buildin Count Update");
    building_clear_counters();
    g_city.buildings.reset_dock_wharf_counters();
    g_city.health.reset_mortuary_workers();

    buildings_valid_do ( [] (building &b) {
        b.dcast()->update_count();
    });
}

void city_buildings_t::update_unique_building_positions() {
    buildings_valid_do ( [] (building &b) {
        b.dcast()->on_post_load();
    });
}

void city_buildings_t::update_tick(bool refresh_only) {
    for (auto it = building_begin(), end = building_end(); it != end; ++it) {
        if (it->is_valid()) {
            it->dcast()->on_tick(refresh_only);
        }
    }
}

void city_buildings_t::reset_dock_wharf_counters() {
    working_wharfs = 0;
    shipyard_boats_requested = 0;
    for (int i = 0; i < 8; i++) {
        working_dock_ids[i] = 0;
    }
    working_docks = 0;
}

void city_buildings_t::update_day() {
    buildings_valid_do([] (building &b) {
        b.dcast()->update_day();
    });
}

bool city_buildings_t::has_working_shipyard() {
    return working_shipyards > 0;
}

void city_buildings_t::update_month() {
    buildings_valid_do([] (building &b) {
        b.dcast()->update_month();
    });
}