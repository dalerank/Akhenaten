#pragma once

#include "grid/point.h"

#include <cstdint>

// Fleet advisor (OG advisors_fleet.c): navy status, a row per warship and the
// kingdom-service / dispatch buttons. Warships are addressed by their 1-based
// index among the player's warships, the way OG figure_warship_by_index does.

enum e_fleet_service_popup {
    FLEET_SERVICE_POPUP_NONE = 0,
    FLEET_SERVICE_POPUP_LAND_TROOPS_NEEDED = 38,
    FLEET_SERVICE_POPUP_NO_TROOPS_NEEDED = 40,
};

enum e_fleet_dispatch_result {
    FLEET_DISPATCH_NONE = 0,
    FLEET_DISPATCH_SENT = 1,
    FLEET_DISPATCH_SEVERAL_REQUESTS = 2,
};

struct fleet_troop_requests {
    int first_by_land = -1;
    int first_by_sea = -1;
    int count_by_land = 0;
    int count_by_sea = 0;

    bool by_land() const { return count_by_land > 0; }
    bool by_sea() const { return count_by_sea > 0; }
};

struct fleet_ship_status {
    int figure_id = 0;
    bool free = false;
    bool at_dock = false;
    bool in_service = false;
    uint8_t hull_text = 0;
    uint8_t crew_text = 0;
};

struct fleet_advisor_status {
    int total_warships = 0;
    int total_transports = 0;
    int warships_in_service = 0;
    bool any_free_in_service = false;
    fleet_troop_requests requests;
    uint8_t threat_text = 0;
    uint8_t request_text = 0;
};

fleet_troop_requests fleet_count_troop_requests();
int fleet_warship_by_index(int index);
fleet_ship_status fleet_ship_status_by_index(int index);

// Also clears every warship's service flag while no sea request waits (OG draw side effect).
fleet_advisor_status fleet_advisor_collect();

tile2i fleet_ship_tile(int index);
void fleet_ship_return_to_dock(int index);
e_fleet_service_popup fleet_ship_toggle_service(int index);
e_fleet_dispatch_result fleet_dispatch_now();
