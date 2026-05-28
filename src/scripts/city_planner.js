log_info("akhenaten: city_planner.js started")

city_planner = extend(__city_planner, {
    // 
})

city_planner.update = function(x, y) {
    __city_planner_update(x, y)
}

city_planner.can_be_placed = function() {
    return __city_planner_can_be_placed()
}

city_planner.construction_start = function(x, y) {
    __city_planner_construction_start(x, y)
}

city_planner.construction_update = function(x, y) {
    __city_planner_construction_update(x, y)
}

city_planner.construction_finalize = function() {
    __city_planner_construction_finalize()
}

city_planner.construction_cancel = function() {
    __city_planner_construction_cancel()
}

city_planner.last_created_building_id = function() {
    return __city_planner_last_created_building_id()
}

city_planner.validate_last_created = function() {
    __city_planner_validate_last_created()
}
