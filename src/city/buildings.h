#pragma once

#include "grid/point.h"
#include "core/custom_span.hpp"
#include "building/building.h"

#include <array>

struct city_buildings_t {
    struct record {
        uint16_t active;
        uint16_t total;
    };

    int32_t festival_building_id;
    tile2i festival_square;

    int32_t senet_house_placed;

    bool distribution_center_placed;
    int32_t distribution_center_building_id;
    tile2i distribution_center;

    int32_t trade_center_building_id;
    int8_t triumphal_arches_available;
    int8_t triumphal_arches_placed;

    int8_t fishing_boats_requested;
    int8_t warships_requested;
    int8_t transport_ships_requested;

    using tracked_building_ids = std::vector<building_id>;
    using tracked_buildings_t = std::array<tracked_building_ids, BUILDING_MAX>;
    const tracked_buildings_t &tracked_buildings() const;

    int32_t mission_post_operational;
    tile2i main_native_meeting;
    int8_t unknown_value;

    std::array<record, BUILDING_MAX> buildings;
    std::array<record, RESOURCES_MAX> industry;

    void init();
    void shutdown();

    void update_tick(bool refresh_only);
    void update_water_supply_houses();
    void mark_well_access(building *well);
    void update_wells_range();
    void update_canals_from_water_lifts();
    void update_religion_supply_houses();
    void update_counters();
    void on_post_load();
    void update_month();
    void update_week();
    void update_day();
    void reload_objects();

    building_id temple_complex_id();
    bool has_temple_complex();
    span_const<e_building_type> temple_complex_types();

    int get_palace_id();

    void remove_palace(building &palace);

    void reset_tracked_buildings_counters();
    void track_building(building &b, bool active);
    const tracked_building_ids &track_buildings(e_building_type type) const { return tracked_buildings().at(type); }

    void clear_fishing_boat_requests() { fishing_boats_requested = 0; }
    void request_fishing_boat() { ++fishing_boats_requested; }
    void request_warship_ship() { ++warships_requested; }
    void request_transport_ship() { ++transport_ships_requested; }

    bool has_working_dock() const { return !tracked_buildings().at(BUILDING_DOCK).empty(); }
    bool has_working_shipyard() const { return !tracked_buildings().at(BUILDING_SHIPWRIGHT).empty(); }

    void increase_count(e_building_type type, bool active);
    void increase_industry_count(int resource, bool active);

    int count_active(std::initializer_list<e_building_type> types);
    int count_active(e_building_type type);
    int count_total(std::initializer_list<e_building_type> types);
    int count_total(e_building_type type);

    int count_industry_active(e_resource resource);
    int count_industry_total(e_resource resource);

    void check_buildings_twins();
};


bool city_buildings_has_distribution_center(void);
void city_buildings_add_distribution_center(building* center);
void city_buildings_remove_distribution_center(building* center);

int city_buildings_get_trade_center();
void city_buildings_set_trade_center(int building_id);

bool city_buildings_has_senet_house();
void city_buildings_add_senet_house();
void city_buildings_remove_senet_house();

int city_buildings_triumphal_arch_available();
void city_buildings_earn_triumphal_arch();
void city_buildings_build_triumphal_arch();
void city_buildings_remove_triumphal_arch();

tile2i city_buildings_main_native_meeting_center();
void city_buildings_set_main_native_meeting_center(int x, int y);

int city_buildings_is_mission_post_operational();
void city_buildings_set_mission_post_operational();

tile2i city_building_get_festival_square_position();

int city_buildings_unknown_value();
