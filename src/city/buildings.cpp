#include <building/menu.h>
#include "buildings.h"

#include "city/data_private.h"

bool city_buildings_has_palace(void) {
    return city_data.building.senate_placed;
}
int city_buildings_get_palace_id(void) {
    if (!city_buildings_has_palace())
        return 0;
    return city_data.building.senate_building_id;
}
void city_buildings_add_palace(building *palace) {
    city_data.building.senate_placed = 1;
    if (!city_data.building.senate_grid_offset) {
        city_data.building.senate_building_id = palace->id;
        city_data.building.senate_x = palace->x;
        city_data.building.senate_y = palace->y;
        city_data.building.senate_grid_offset = palace->grid_offset;
    }
}
void city_buildings_remove_palace(building *palace) {
    if (palace->grid_offset == city_data.building.senate_grid_offset) {
        city_data.building.senate_grid_offset = 0;
        city_data.building.senate_x = 0;
        city_data.building.senate_y = 0;
        city_data.building.senate_placed = 0;
    }
}

bool city_buildings_has_mansion(void) {
    return city_data.building.mansion_placed;
}
int city_buildings_get_mansion_id(void) {
    if (!city_buildings_has_mansion())
        return 0;
    return city_data.building.mansion_building_id;
}
void city_buildings_add_mansion(building *mansion) {
    city_data.building.mansion_placed = 1;
    if (!city_data.building.mansion_grid_offset) {
        city_data.building.mansion_building_id = mansion->id;
        city_data.building.mansion_x = mansion->x;
        city_data.building.mansion_y = mansion->y;
        city_data.building.mansion_grid_offset = mansion->grid_offset;
    }
}
void city_buildings_remove_mansion(building *mansion) {
    if (mansion->grid_offset == city_data.building.mansion_grid_offset) {
        city_data.building.mansion_grid_offset = 0;
        city_data.building.mansion_x = 0;
        city_data.building.mansion_y = 0;
        city_data.building.mansion_placed = 0;
    }
}

bool city_buildings_has_recruiter(void) {
    return city_data.building.barracks_placed;
}
void city_buildings_add_recruiter(building *recruiter) {
    city_data.building.barracks_placed = 1;
    if (!city_data.building.barracks_grid_offset) {
        city_data.building.barracks_building_id = recruiter->id;
        city_data.building.barracks_x = recruiter->x;
        city_data.building.barracks_y = recruiter->y;
        city_data.building.barracks_grid_offset = recruiter->grid_offset;
    }
}
void city_buildings_remove_recruiter(building *recruiter) {
    if (recruiter->grid_offset == city_data.building.barracks_grid_offset) {
        city_data.building.barracks_grid_offset = 0;
        city_data.building.barracks_x = 0;
        city_data.building.barracks_y = 0;
        city_data.building.barracks_placed = 0;
    }
}
int city_buildings_get_recruiter(void) {
    return city_data.building.barracks_building_id;
}
void city_buildings_set_recruiter(int building_id) {
    city_data.building.barracks_building_id = building_id;
}

bool city_buildings_has_distribution_center(void) {
    return city_data.building.distribution_center_placed;
}
void city_buildings_add_distribution_center(building *center) {
    city_data.building.distribution_center_placed = 1;
    if (!city_data.building.distribution_center_grid_offset) {
        city_data.building.distribution_center_building_id = center->id;
        city_data.building.distribution_center_x = center->x;
        city_data.building.distribution_center_y = center->y;
        city_data.building.distribution_center_grid_offset = center->grid_offset;
    }
}
void city_buildings_remove_distribution_center(building *center) {
    if (center->grid_offset == city_data.building.distribution_center_grid_offset) {
        city_data.building.distribution_center_grid_offset = 0;
        city_data.building.distribution_center_x = 0;
        city_data.building.distribution_center_y = 0;
        city_data.building.distribution_center_placed = 0;
    }
}

int city_buildings_get_trade_center(void) {
    return city_data.building.trade_center_building_id;
}
void city_buildings_set_trade_center(int building_id) {
    city_data.building.trade_center_building_id = building_id;
}

bool city_buildings_has_hippodrome(void) {
    return city_data.building.hippodrome_placed;
}
void city_buildings_add_hippodrome(void) {
    city_data.building.hippodrome_placed = 1;
}
void city_buildings_remove_hippodrome(void) {
    city_data.building.hippodrome_placed = 0;
}

int city_buildings_triumphal_arch_available(void) {
    return city_data.building.triumphal_arches_available > city_data.building.triumphal_arches_placed;
}
void city_buildings_build_triumphal_arch(void) {
    city_data.building.triumphal_arches_placed++;
}
void city_buildings_remove_triumphal_arch(void) {
    if (city_data.building.triumphal_arches_placed > 0)
        city_data.building.triumphal_arches_placed--;

}
void city_buildings_earn_triumphal_arch(void) {
    city_data.building.triumphal_arches_available++;
}

void city_buildings_add_dock(void) {
    city_data.building.working_docks++;
}
void city_buildings_remove_dock(void) {
    city_data.building.working_docks--;
}
void city_buildings_reset_dock_wharf_counters(void) {
    city_data.building.working_wharfs = 0;
    city_data.building.shipyard_boats_requested = 0;
    for (int i = 0; i < 8; i++) {
        city_data.building.working_dock_ids[i] = 0;
    }
    city_data.building.working_docks = 0;
}
void city_buildings_add_working_wharf(int needs_fishing_boat) {
    ++city_data.building.working_wharfs;
    if (needs_fishing_boat)
        ++city_data.building.shipyard_boats_requested;

}
void city_buildings_add_working_dock(int building_id) {
    if (city_data.building.working_docks < 10)
        city_data.building.working_dock_ids[city_data.building.working_docks] = building_id;

    ++city_data.building.working_docks;
}

int city_buildings_shipyard_boats_requested(void) {
    return city_data.building.shipyard_boats_requested;
}

bool city_buildings_has_working_dock(void) {
    return city_data.building.working_docks > 0;
}
int city_buildings_get_working_dock(int index) {
    return city_data.building.working_dock_ids[index];
}

void city_buildings_main_native_meeting_center(int *x, int *y) {
    *x = city_data.building.main_native_meeting.x;
    *y = city_data.building.main_native_meeting.y;
}
void city_buildings_set_main_native_meeting_center(int x, int y) {
    city_data.building.main_native_meeting.x = x;
    city_data.building.main_native_meeting.y = y;
}

int city_buildings_is_mission_post_operational(void) {
    return city_data.building.mission_post_operational > 0;
}
void city_buildings_set_mission_post_operational(void) {
    city_data.building.mission_post_operational = 1;
}

bool city_building_has_festival_square(void) {
    return city_data.building.festival_square_placed;
}
void city_building_get_festival_square_position(int *x, int *y) {
    *x = city_data.building.festival_square_x;
    *y = city_data.building.festival_square_y;
}
void city_buildings_add_festival_square(building *square) {
    city_data.building.festival_square_placed = true;
    city_data.building.festival_square_x = square->x;
    city_data.building.festival_square_y = square->y;
}
void city_buildings_remove_festival_square(void) {
    city_data.building.festival_square_x = -1;
    city_data.building.festival_square_y = -1;
    city_data.building.festival_square_placed = false;
}

bool city_buildings_has_temple_complex(void) {
    return city_data.building.temple_complex_placed;
}
int city_buildings_get_temple_complex(void) {
    return city_data.building.temple_complex_id;
}
void city_buildings_add_temple_complex(building *complex) {
    city_data.building.temple_complex_placed = true;
    city_data.building.temple_complex_id = complex->id;
    building_menu_update_temple_complexes();
}
void city_buildings_remove_temple_complex(void) {
    city_data.building.temple_complex_id = 0;
    city_data.building.temple_complex_placed = false;
    building_menu_update_temple_complexes();
}

int city_buildings_unknown_value(void) {
    return city_data.building.unknown_value;
}
