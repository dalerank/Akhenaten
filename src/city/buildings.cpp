#include "buildings.h"

#include "building/building_house.h"
#include "core/profiler.h"
#include "grid/water.h"
#include "grid/building.h"
#include "grid/routing/routing.h"
#include "city/city.h"

#include <set>

city_buildings_t::tracked_buildings_t g_tracked_buildings;

const auto palace_types = { BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_VILLAGE_PALACE_UP, BUILDING_TOWN_PALACE_UP, BUILDING_CITY_PALACE };
int city_buildings_t::get_palace_id() {
    for (auto btype : palace_types) {
        const auto &palace = tracked_buildings().at(btype);
        if (!palace.empty()) {
            return palace.front();
        }
    }

    return 0;
}

void city_buildings_t::remove_palace(building &palace) {
}

void city_buildings_t::track_building(building &b, bool active) {
    g_tracked_buildings[b.type].push_back(b.id);
    increase_count(b.type, active);
}

void city_buildings_t::check_buildings_twins() {
    std::set<int> occuped;
    for (auto &b : city_buildings()) {
        if (b.is_valid()) {
            auto result = occuped.insert(b.tile.grid_offset());
            if (!result.second) {
                verify_no_crash(false && "twin building, second will be removed");
                b.state = BUILDING_STATE_UNUSED;
            }
        }
    }
}

bool city_buildings_has_distribution_center() {
    return g_city.buildings.distribution_center_placed;
}

void city_buildings_add_distribution_center(building* center) {
    g_city.buildings.distribution_center_placed = 1;
    if (!g_city.buildings.distribution_center.grid_offset()) {
        g_city.buildings.distribution_center_building_id = center->id;
        g_city.buildings.distribution_center.set(center->tile.grid_offset());
    }
}

void city_buildings_remove_distribution_center(building* center) {
    if (center->tile.grid_offset() == g_city.buildings.distribution_center.grid_offset()) {
        g_city.buildings.distribution_center.set(0);
        //        g_city.buildings.distribution_center.grid_offset() = 0;
        //        g_city.buildings.distribution_center.x = 0;
        //        g_city.buildings.distribution_center.y = 0;
        g_city.buildings.distribution_center_placed = 0;
    }
}

int city_buildings_get_trade_center() {
    return g_city.buildings.trade_center_building_id;
}

void city_buildings_set_trade_center(int building_id) {
    g_city.buildings.trade_center_building_id = building_id;
}

bool city_buildings_has_senet_house() {
    return g_city.buildings.senet_house_placed;
}

void city_buildings_add_senet_house() {
    g_city.buildings.senet_house_placed = 1;
}

void city_buildings_remove_senet_house() {
    g_city.buildings.senet_house_placed = 0;
}

int city_buildings_triumphal_obelisk_available() {
    return g_city.buildings.triumphal_obelisk_available > g_city.buildings.triumphal_obelisk_placed;
}

void city_buildings_build_triumphal_obelisk() {
    g_city.buildings.triumphal_obelisk_placed++;
}

void city_buildings_remove_triumphal_obelisk(void) {
    if (g_city.buildings.triumphal_obelisk_placed > 0)
        g_city.buildings.triumphal_obelisk_placed--;
}

void city_buildings_earn_triumphal_obelisk(void) {
    g_city.buildings.triumphal_obelisk_available++;
}

tile2i city_buildings_main_native_meeting_center() {
    return g_city.buildings.main_native_meeting;
}
void city_buildings_set_main_native_meeting_center(int x, int y) {
    g_city.buildings.main_native_meeting.set(x, y);
}

int city_buildings_is_mission_post_operational(void) {
    return g_city.buildings.mission_post_operational > 0;
}

void city_buildings_set_mission_post_operational(void) {
    g_city.buildings.mission_post_operational = 1;
}

tile2i city_building_get_festival_square_position() {
    return g_city.buildings.festival_square;
}

void city_buildings_add_festival_square(building* square) {
    g_city.buildings.festival_square = square->tile;
}

void city_buildings_remove_festival_square() {
    g_city.buildings.festival_square = tile2i::invalid;
}

int city_buildings_unknown_value() {
    return g_city.buildings.unknown_value;
}

void city_t::buildings_update_open_water_access() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Open Water Access Update");
}

void city_buildings_t::update_counters() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Buildin Count Update");

    std::fill(buildings.begin(), buildings.end(), record{ 0, 0 });
    std::fill(industry.begin(), industry.end(), record{ 0, 0 });

    g_city.buildings.reset_tracked_buildings_counters();
    g_city.health.reset_mortuary_workers();

    buildings_valid_do([] (building &b) {
        b.dcast()->update_count();
    });
}


int city_buildings_t::count_industry_active(e_resource resource) {
    return industry[resource].active;
}

int city_buildings_t::count_industry_total(e_resource resource) {
    return industry[resource].total;
}

int city_buildings_t::count_active(std::initializer_list<e_building_type> types) {
    int count = 0;
    for (const auto &type : types) {
        count += buildings[type].active;
    }

    return count;
}

int city_buildings_t::count_total(std::initializer_list<e_building_type> types) {
    int count = 0;
    for (const auto &type : types) {
        count += buildings[type].total;
    }

    return count;
}

int city_buildings_t::count_active(e_building_type type) {
    return buildings[type].total;
}

int city_buildings_t::count_total(e_building_type type) {
    return buildings[type].total;
}

void city_buildings_t::increase_count(e_building_type type, bool active) {
    buildings[type].total++;
    buildings[type].active += (active ? 1 : 0);
}

void city_buildings_t::increase_industry_count(int resource, bool active) {
    industry[resource].total++;
    industry[resource].active += (active ? 1 : 0);
}

void city_buildings_t::on_post_load () {
    buildings_valid_do([] (building &b) {
        b.dcast()->on_post_load();
    });

    check_buildings_twins();
}

const city_buildings_t::tracked_buildings_t &city_buildings_t::tracked_buildings() const {
    return g_tracked_buildings;
}

void city_buildings_t::init() {
}

void city_buildings_t::shutdown() {
}

void city_buildings_t::update_tick(bool refresh_only) {
    for (auto it = building_begin(), end = building_end(); it != end; ++it) {
        if (it->is_valid()) {
            it->dcast()->on_tick(refresh_only);
        }
    }
}

void city_buildings_t::reset_tracked_buildings_counters() {
    for (auto &bids: g_tracked_buildings) {
        bids.clear();
    }
}

void city_buildings_t::update_day() {
    buildings_valid_do([] (building &b) {
        b.dcast()->update_day();
    });
}

void city_buildings_t::update_year() {
    buildings_valid_do([] (building &b) {
        b.dcast()->update_year();
    });
}

void city_buildings_t::reload_objects() {
    buildings_valid_do([] (building &b) {
        b.dcast()->on_config_reload();
    });
}

const e_building_type _temple_complex_types[] = {
    BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_PTAH, BUILDING_TEMPLE_COMPLEX_SETH, BUILDING_TEMPLE_COMPLEX_BAST
};

building_id city_buildings_t::temple_complex_id() {
    for (const e_building_type type : _temple_complex_types) {
        const auto &complexes = tracked_buildings().at(type);
        if (!complexes.empty()) {
            return complexes.front();
        }
    }

    return 0;
}

bool city_buildings_t::has_temple_complex() {
    bool has_temple_complex = false;
    for (const e_building_type type : _temple_complex_types) {
        const auto &complexes = tracked_buildings().at(type);
        has_temple_complex |= !complexes.empty();
    }

    return has_temple_complex;
}

span_const<e_building_type> city_buildings_t::temple_complex_types() {
    return span_const<e_building_type>(_temple_complex_types);
}

void city_buildings_t::update_month() {
    buildings_valid_do([] (building &b) {
        b.dcast()->update_month();
    });
}

void city_buildings_t::update_week() {
    buildings_valid_do([] (building &b) {
        b.dcast()->update_week();
    });
}

void city_buildings_t::update_religion_supply_houses() {
    OZZY_PROFILER_SECTION("Game/Update/Religion Supply Update");
    svector<building*, 512> shrines;

    auto mark_shrine_access = [] (building *shrine, int radius) {
        grid_area area = map_grid_get_area(shrine->tile, 1, radius);

        for (int yy = area.tmin.y(), endy = area.tmax.y(); yy <= endy; yy++) {
            for (int xx = area.tmin.x(), endx = area.tmax.x(); xx <= endx; xx++) {
                int building_id = map_building_at(tile2i(xx, yy));

                auto house = building_get(building_id)->dcast_house();
                if (house) {
                    house->runtime_data().shrine_access = true;
                }
            }
        }
    };

    for (auto& b : city_buildings()) {
        if (b.state != BUILDING_STATE_VALID)
            continue;

        if (b.is_shrine()) {
            shrines.push_back(&b);
        } else if (auto house = b.dcast_house(); !!house) {
            house->runtime_data().shrine_access = false;
        }
    }

    for (auto& s : shrines) {
        mark_shrine_access(s, 3);
    }
}

io_buffer *iob_building_count_industry = new io_buffer([] (io_buffer *iob, size_t version) {
    iob->bind____skip(sizeof(int32_t) * RESOURCES_MAX);
    iob->bind____skip(sizeof(int32_t) * RESOURCES_MAX);

    //    // culture 1
    //    data.buildings[BUILDING_BOOTH].total = culture1->read_i32();
    //    data.buildings[BUILDING_BOOTH].active = culture1->read_i32();
    //    data.buildings[BUILDING_BANDSTAND].total = culture1->read_i32();
    //    data.buildings[BUILDING_BANDSTAND].active = culture1->read_i32();
    //    data.buildings[BUILDING_PAVILLION].total = culture1->read_i32();
    //    data.buildings[BUILDING_PAVILLION].active = culture1->read_i32();
    //    data.buildings[BUILDING_SENET_HOUSE].total = culture1->read_i32();
    //    data.buildings[BUILDING_SENET_HOUSE].active = culture1->read_i32();
    //    data.buildings[BUILDING_SCRIBAL_SCHOOL].total = culture1->read_i32();
    //    data.buildings[BUILDING_SCRIBAL_SCHOOL].active = culture1->read_i32();
    //    data.buildings[BUILDING_LIBRARY].total = culture1->read_i32();
    //    data.buildings[BUILDING_LIBRARY].active = culture1->read_i32();
    //    data.buildings[BUILDING_MENU_WATER_CROSSINGS].total = culture1->read_i32();
    //    data.buildings[BUILDING_MENU_WATER_CROSSINGS].active = culture1->read_i32();
    //    data.buildings[BUILDING_DENTIST].total = culture1->read_i32();
    //    data.buildings[BUILDING_DENTIST].active = culture1->read_i32();
    //    data.buildings[BUILDING_MENU_MONUMENTS].total = culture1->read_i32();
    //    data.buildings[BUILDING_MENU_MONUMENTS].active = culture1->read_i32();
    //    data.buildings[BUILDING_APOTHECARY].total = culture1->read_i32();
    //    data.buildings[BUILDING_APOTHECARY].active = culture1->read_i32();
    //    data.buildings[BUILDING_MORTUARY].total = culture1->read_i32();
    //    data.buildings[BUILDING_MORTUARY].active = culture1->read_i32();
    //    data.buildings[BUILDING_TEMPLE_OSIRIS].total = culture1->read_i32();
    //    data.buildings[BUILDING_TEMPLE_RA].total = culture1->read_i32();
    //    data.buildings[BUILDING_TEMPLE_PTAH].total = culture1->read_i32();
    //    data.buildings[BUILDING_TEMPLE_SETH].total = culture1->read_i32();
    //    data.buildings[BUILDING_TEMPLE_BAST].total = culture1->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_OSIRIS].total = culture1->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_RA].total = culture1->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_PTAH].total = culture1->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_SETH].total = culture1->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_BAST].total = culture1->read_i32();
    //    data.buildings[BUILDING_ORACLE].total = culture1->read_i32();
    //
    //    // culture 2
    //    data.buildings[BUILDING_JUGGLER_SCHOOL].total = culture2->read_i32();
    //    data.buildings[BUILDING_JUGGLER_SCHOOL].active = culture2->read_i32();
    //    data.buildings[BUILDING_CONSERVATORY].total = culture2->read_i32();
    //    data.buildings[BUILDING_CONSERVATORY].active = culture2->read_i32();
    //    data.buildings[BUILDING_DANCE_SCHOOL].total = culture2->read_i32();
    //    data.buildings[BUILDING_DANCE_SCHOOL].active = culture2->read_i32();
    //    data.buildings[BUILDING_CHARIOT_MAKER].total = culture2->read_i32();
    //    data.buildings[BUILDING_CHARIOT_MAKER].active = culture2->read_i32();
    //
    //    // culture 3
    //    data.buildings[BUILDING_TEMPLE_OSIRIS].active = culture3->read_i32();
    //    data.buildings[BUILDING_TEMPLE_RA].active = culture3->read_i32();
    //    data.buildings[BUILDING_TEMPLE_PTAH].active = culture3->read_i32();
    //    data.buildings[BUILDING_TEMPLE_SETH].active = culture3->read_i32();
    //    data.buildings[BUILDING_TEMPLE_BAST].active = culture3->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_OSIRIS].active = culture3->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_RA].active = culture3->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_PTAH].active = culture3->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_SETH].active = culture3->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_BAST].active = culture3->read_i32();
    //
    //    // military
    //    data.buildings[BUILDING_MILITARY_ACADEMY].total = military->read_i32();
    //    data.buildings[BUILDING_MILITARY_ACADEMY].active = military->read_i32();
    //    data.buildings[BUILDING_RECRUITER].total = military->read_i32();
    //    data.buildings[BUILDING_RECRUITER].active = military->read_i32();
    //
    //    // support
    //    data.buildings[BUILDING_BAZAAR].total = support->read_i32();
    //    data.buildings[BUILDING_BAZAAR].active = support->read_i32();
    //    data.buildings[BUILDING_WATER_LIFT].total = support->read_i32();
    //    data.buildings[BUILDING_WATER_LIFT].active = support->read_i32();
    //    data.buildings[BUILDING_MENU_BEAUTIFICATION].total = support->read_i32();
    //    data.buildings[BUILDING_MENU_BEAUTIFICATION].active = support->read_i32();
});