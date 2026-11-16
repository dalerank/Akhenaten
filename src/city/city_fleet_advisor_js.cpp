#include "city/city_fleet_advisor.h"

#include "js/js_game.h"

int __fleet_total_warships() {
    return fleet_advisor_collect().total_warships;
}
ANK_FUNCTION(__fleet_total_warships)

int __fleet_total_transports() {
    return fleet_advisor_collect().total_transports;
}
ANK_FUNCTION(__fleet_total_transports)

int __fleet_threat_text() {
    return fleet_advisor_collect().threat_text;
}
ANK_FUNCTION(__fleet_threat_text)

int __fleet_request_text() {
    return fleet_advisor_collect().request_text;
}
ANK_FUNCTION(__fleet_request_text)

bool __fleet_any_in_service() {
    return fleet_advisor_collect().any_free_in_service;
}
ANK_FUNCTION(__fleet_any_in_service)

bool __fleet_requested_by_sea() {
    return fleet_count_troop_requests().by_sea();
}
ANK_FUNCTION(__fleet_requested_by_sea)

int __fleet_ship_id(int index) {
    return fleet_ship_status_by_index(index).figure_id;
}
ANK_FUNCTION_1(__fleet_ship_id)

bool __fleet_ship_free(int index) {
    return fleet_ship_status_by_index(index).free;
}
ANK_FUNCTION_1(__fleet_ship_free)

bool __fleet_ship_at_dock(int index) {
    return fleet_ship_status_by_index(index).at_dock;
}
ANK_FUNCTION_1(__fleet_ship_at_dock)

bool __fleet_ship_in_service(int index) {
    return fleet_ship_status_by_index(index).in_service;
}
ANK_FUNCTION_1(__fleet_ship_in_service)

int __fleet_ship_hull_text(int index) {
    return fleet_ship_status_by_index(index).hull_text;
}
ANK_FUNCTION_1(__fleet_ship_hull_text)

int __fleet_ship_crew_text(int index) {
    return fleet_ship_status_by_index(index).crew_text;
}
ANK_FUNCTION_1(__fleet_ship_crew_text)

tile2i __fleet_ship_tile(int index) {
    return fleet_ship_tile(index);
}
ANK_FUNCTION_1(__fleet_ship_tile)

void __fleet_ship_return_to_dock(int index) {
    fleet_ship_return_to_dock(index);
}
ANK_FUNCTION_1(__fleet_ship_return_to_dock)

int __fleet_ship_toggle_service(int index) {
    return fleet_ship_toggle_service(index);
}
ANK_FUNCTION_1(__fleet_ship_toggle_service)

int __fleet_dispatch_now() {
    return fleet_dispatch_now();
}
ANK_FUNCTION(__fleet_dispatch_now)
