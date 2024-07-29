#pragma once

#include "grid/point.h"
#include "building/building.h"

struct city_buildings_t {
    bool palace_placed;
    int32_t palace_building_id;
    tile2i palace_point;

    int32_t festival_building_id;
    tile2i festival_square;

    bool mansion_placed;
    int32_t mansion_building_id;
    tile2i mansion;

    int32_t senet_house_placed;

    struct {
        bool placed;
        int32_t building_id;
        tile2i tile;
    } recruiter;

    bool distribution_center_placed;
    int32_t distribution_center_building_id;
    tile2i distribution_center;

    int32_t trade_center_building_id;
    int8_t triumphal_arches_available;
    int8_t triumphal_arches_placed;
    int16_t working_wharfs;
    int32_t shipyard_boats_requested;
    int16_t working_docks;
    int16_t working_dock_ids[10];
    int16_t working_shipyards;
    int32_t mission_post_operational;
    tile2i main_native_meeting;
    int8_t unknown_value;

    bool temple_complex_placed;
    int32_t temple_complex_id;

    void update_tick(bool refresh_only);
    void update_water_supply_houses();
    void mark_well_access(building *well);
    void update_wells_range();
    void update_canals_from_water_lifts();
    void update_religion_supply_houses();
    void update_counters();
    void update_unique_building_positions();
    void reset_dock_wharf_counters();
    void update_month();
    void update_day();

    bool has_working_shipyard();
    int get_palace_id();
};


int city_buildings_get_palace_id();
void city_buildings_add_palace(building* palace);
void city_buildings_remove_palace(building* palace);

bool city_buildings_has_mansion();
int city_buildings_get_mansion_id();
void city_buildings_add_mansion(building* mansion);
void city_buildings_remove_mansion(building* mansion);

bool city_buildings_has_recruiter();
void city_buildings_add_recruiter(building* recruiter);
void city_buildings_remove_recruiter(building* recruiter);
int city_buildings_get_recruiter();
void city_buildings_set_recruiter(int building_id);

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

void city_buildings_add_dock();
void city_buildings_remove_dock();

void city_buildings_add_working_wharf(int needs_fishing_boat);
void city_buildings_add_working_dock(int building_id);
void city_buildings_add_working_shipyard(int building_id);
bool city_buildings_has_working_dock();
int city_buildings_get_working_dock(int index);

map_point city_buildings_main_native_meeting_center();
void city_buildings_set_main_native_meeting_center(int x, int y);

int city_buildings_is_mission_post_operational();
void city_buildings_set_mission_post_operational();

map_point city_building_get_festival_square_position();
void city_buildings_add_festival_square(building* square);
void city_buildings_remove_festival_square();

bool city_buildings_has_temple_complex();
int city_buildings_get_temple_complex();
void city_buildings_add_temple_complex(building* complex);
void city_buildings_remove_temple_complex();

int city_buildings_unknown_value();
