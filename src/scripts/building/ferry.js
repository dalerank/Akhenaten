log_info("akhenaten: loading building_ferry")

[es=(building_ferry, highlight_waypoints)]
function building_ferry_highlight_waypoints(ev) {
    var building = city.get_building(ev.bid)
    __map_highlight_set(building.water_access_tile(0), HIGHLIGHT_GREEN)
    __map_highlight_set(building.water_access_tile(1), HIGHLIGHT_GREEN)
}
