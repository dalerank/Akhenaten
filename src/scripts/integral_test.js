// Helpers for --integraltests (city session + build_planner placement).

var CAN_PLACE = 0

function test_log_building_placed(bid) {
    if (!bid) {
        return
    }
    var type = __building_type(bid)
    var tile = __building_tile(bid)
    if (!type || !tile) {
        return
    }
    var marker
    if (type == BUILDING_WORK_CAMP) {
        marker = 'test_building_placed:work_camp:' + bid + ':' + tile.x + ',' + tile.y
    } else {
        marker = 'test_building_placed:type_' + type + ':' + bid + ':' + tile.x + ',' + tile.y
    }
    __log_marker(marker)
}

function test_ensure_city_session(map_path) {
    if (game.session_active) {
        return true
    }
    return __test_start_city_session(map_path)
}

function test_reload_city_session(map_path) {
    __test_end_city_session()
    return __test_start_city_session(map_path)
}

function test_planner_enter_build_mode(type) {
    if (!__scenario_building_allowed(type)) {
        __scenario_building_allow(type, true)
    }
    emit event_city_building_mode{ value: type }
    __test_process_events()
    return city_planner.build_type == type
}

function test_planner_exit_build_mode() {
    if (city_planner.in_progress) {
        city_planner.construction_cancel()
    }
    emit event_city_building_mode{ value: BUILDING_NONE }
    __test_process_events()
}

function test_find_buildable_tile(type) {
    if (!test_planner_enter_build_mode(type)) {
        return null
    }

    var footprint = __building_static_building_size(type)
    var w = __scenario_map.width
    var h = __scenario_map.height
    var cx = (w / 2) | 0
    var cy = (h / 2) | 0
    var best = null
    var best_dist_sq = 999999999

    for (var y = footprint; y < h - footprint; y++) {
        for (var x = footprint; x < w - footprint; x++) {
            var dx = x - cx
            var dy = y - cy
            var dist_sq = dx * dx + dy * dy
            if (best && dist_sq >= best_dist_sq) {
                continue
            }
            city_planner.update(x, y)
            if (city_planner.can_be_placed() == CAN_PLACE) {
                best = { x: x, y: y }
                best_dist_sq = dist_sq
            }
        }
    }

    test_planner_exit_build_mode()
    return best
}

function test_building_place(type, x, y) {
    var place = null
    if (x >= 0 && y >= 0) {
        place = { x: x, y: y }
    } else {
        place = test_find_buildable_tile(type)
    }

    if (!place) {
        __log_info_native('[test_planner] no buildable tile for type ' + type)
        return 0
    }

    if (!test_planner_enter_build_mode(type)) {
        __log_info_native('[test_planner] failed to enter build mode for type ' + type)
        return 0
    }

    city_planner.update(place.x, place.y)
    if (city_planner.can_be_placed() != CAN_PLACE) {
        __log_info_native('[test_planner] tile not placeable at ' + place.x + ',' + place.y)
        test_planner_exit_build_mode()
        return 0
    }

    city_planner.construction_start(place.x, place.y)
    city_planner.construction_update(place.x, place.y)
    city_planner.construction_finalize()

    var bid = city_planner.last_created_building_id()
    city_planner.validate_last_created()
    if (!bid || __building_type(bid) != type) {
        __log_info_native('[test_planner] construction_finalize did not create type ' + type)
        test_planner_exit_build_mode()
        return 0
    }
    test_planner_exit_build_mode()
    test_log_building_placed(bid)
    return bid
}

// Synthetic shoreline: land row at cy - 1, water patch below (see tests/17, tests/19).
function test_prepare_shoreline_patch(cx, cy, water_width, water_height) {
    var x0 = cx - ((water_width / 2) | 0)
    for (var dy = 0; dy < water_height; dy++) {
        for (var dx = 0; dx < water_width; dx++) {
            terrain.add({ x: x0 + dx, y: cy + dy }, TERRAIN_WATER)
        }
    }
    __map_water_rebuild_shores()
}

// Paint a square terrain patch centered on (cx, cy). Used for farm meadow/floodplain.
function test_prepare_terrain_patch(cx, cy, size, terrain_mask) {
    var x0 = cx - ((size / 2) | 0)
    var y0 = cy - ((size / 2) | 0)
    for (var dy = 0; dy < size; dy++) {
        for (var dx = 0; dx < size; dx++) {
            terrain.add({ x: x0 + dx, y: y0 + dy }, terrain_mask)
        }
    }
}

// Place a farm on a synthetic meadow/floodplain patch near map center.
function test_farm_place(type, terrain_mask) {
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var footprint = __building_static_building_size(type)
    if (footprint <= 0) {
        footprint = 3
    }
    test_prepare_terrain_patch(cx, cy, footprint + 2, terrain_mask)
    var place_x = cx - ((footprint / 2) | 0)
    var place_y = cy - ((footprint / 2) | 0)
    return test_building_place(type, place_x, place_y)
}

function test_assert_building_placed(bid, type, tag) {
    if (!bid) {
        __log_info_native('[' + tag + '] no building id')
        return false
    }

    if (__building_type(bid) != type) {
        __log_info_native('[' + tag + '] wrong building type for id ' + bid)
        return false
    }

    var tile = __building_tile(bid)
    var at = city.get_building_at(tile.x, tile.y)
    if (!at || at.id != bid) {
        __log_info_native('[' + tag + '] map_building_at mismatch at ' + tile.x + ',' + tile.y)
        return false
    }

    var marker = '[test-marker] test_building_placed:type_' + type + ':' + bid + ':'
    if (!__test_find_inlog(marker)) {
        __log_info_native('[' + tag + '] missing marker: ' + marker)
        return false
    }

    return true
}

function test_shoreline_building_place(type, building_size) {
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var water_width = building_size + 2
    var water_height = 2
    if (building_size >= 3) {
        water_width = building_size + 4
        water_height = 3
    }
    test_prepare_shoreline_patch(cx, cy, water_width, water_height)

    var candidates = [{ x: cx - 1, y: cy - 1 }]
    if (building_size >= 3) {
        candidates.push({ x: cx - 2, y: cy - 1 })
        candidates.push({ x: cx - 1, y: cy - 2 })
    }

    if (!test_planner_enter_build_mode(type)) {
        __log_info_native('[test_planner] failed to enter build mode for type ' + type)
        return 0
    }

    for (var i = 0; i < candidates.length; i++) {
        var place = candidates[i]
        city_planner.update(place.x, place.y)
        if (city_planner.can_be_placed() != CAN_PLACE) {
            continue
        }
        city_planner.construction_start(place.x, place.y)
        city_planner.construction_update(place.x, place.y)
        city_planner.construction_finalize()
        var bid = city_planner.last_created_building_id()
        city_planner.validate_last_created()
        if (bid && __building_type(bid) == type) {
            test_planner_exit_build_mode()
            test_log_building_placed(bid)
            return bid
        }
    }

    __log_info_native('[test_planner] no valid shoreline tile for type ' + type)
    test_planner_exit_build_mode()
    return 0
}
