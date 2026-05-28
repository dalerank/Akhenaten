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
