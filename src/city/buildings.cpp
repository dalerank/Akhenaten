#include "buildings.h"

#include "building/building.h"
#include "building/count.h"
#include "building/building_menu.h"
#include "core/profiler.h"
#include "grid/water.h"
#include "grid/building.h"
#include "grid/routing/routing.h"

#include "city/city.h"
#include <set>

static auto &city_data = g_city;
const auto palace_types = { BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_VILLAGE_PALACE_UP, BUILDING_TOWN_PALACE_UP, BUILDING_CITY_PALACE };
int city_buildings_t::get_palace_id() {
    for (auto btype : palace_types) {
        const auto &palace = tracked_buildings->at(btype);
        if (!palace.empty()) {
            return palace.front();
        }
    }

    return 0;
}

void city_buildings_t::remove_palace(building &palace) {
    assert(!!palace.dcast_palace());
    for (auto btype : palace_types) {
        auto &palace = tracked_buildings->at(btype);
        palace.clear();
    }
}

void city_buildings_t::track_building(building &b, bool active) {
    tracked_buildings->at(b.type).push_back(b.id);
    building_increase_type_count(b.type, active);
}

void city_buildings_t::check_buildings_twins() {
    std::set<int> occuped;
    for (auto &b : city_buildings()) {
        if (b.is_valid()) {
            auto result = occuped.insert(b.tile.grid_offset());
            if (!result.second) {
                assert(false && "twin building, second will be removed");
                b.state = BUILDING_STATE_UNUSED;
            }
        }
    }
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

int city_buildings_get_trade_center() {
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

void city_buildings_remove_festival_square() {
    city_data.buildings.festival_square = tile2i::invalid;
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
}

void city_buildings_t::update_counters() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Buildin Count Update");

    building_clear_counters();
    g_city.buildings.reset_tracked_buildings_counters();
    g_city.health.reset_mortuary_workers();

    buildings_valid_do ( [] (building &b) {
        b.dcast()->update_count();
    });
}

void city_buildings_t::on_post_load () {
    buildings_valid_do ( [] (building &b) {
        b.dcast()->on_post_load();
    });

    check_buildings_twins();
}

void city_buildings_t::init() {
    tracked_buildings = new tracked_buildings_t();
}

void city_buildings_t::shutdown() {
    delete tracked_buildings;
    tracked_buildings = nullptr;
}

void city_buildings_t::update_tick(bool refresh_only) {
    for (auto it = building_begin(), end = building_end(); it != end; ++it) {
        if (it->is_valid()) {
            it->dcast()->on_tick(refresh_only);
        }
    }
}

void city_buildings_t::reset_tracked_buildings_counters() {
    for (auto &bids: *tracked_buildings) {
        bids.clear();
    }
}

void city_buildings_t::update_day() {
    buildings_valid_do([] (building &b) {
        b.dcast()->update_day();
    });
}

void city_buildings_t::update_month() {
    buildings_valid_do([] (building &b) {
        b.dcast()->update_month();
    });
}

void city_buildings_t::update_religion_supply_houses() {
    OZZY_PROFILER_SECTION("Game/Update/Religion Supply Update");
    svector<building*, 512> shrines;

    auto mark_shrine_access = [] (building *shrine, int radius) {
        grid_area area = map_grid_get_area(shrine->tile, 1, radius);

        for (int yy = area.tmin.y(), endy = area.tmax.y(); yy <= endy; yy++) {
            for (int xx = area.tmin.x(), endx = area.tmax.x(); xx <= endx; xx++) {
                int building_id = map_building_at(MAP_OFFSET(xx, yy));

                building *b = building_get(building_id);
                if (b->house_size) {
                    b->data.house.shrine_access = true;
                }
            }
        }
    };

    for (auto& b : city_buildings()) {
        if (b.state != BUILDING_STATE_VALID)
            continue;

        if (b.is_shrine()) {
            shrines.push_back(&b);
        } else if (b.house_size) {
            b.data.house.shrine_access = false;
        }
    }

    for (auto& s : shrines) {
        mark_shrine_access(s, 3);
    }
}