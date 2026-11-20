// The house info panel names a nearby building that drags desirability down. Houses of the same or a
// higher level never count (OG: only lower-level houses and non-house buildings), even though every low
// house has a negative desirability of its own.
// Markers:
//   [test-marker] t568_ok
//   [test-marker] t568_fail:<what>

var __t568_failed = false

function t568_fail(what) {
    __log_info_native('[test-marker] t568_fail:' + what)
    __t568_failed = true
}

function t568_worst_next_to(name, neighbour_type, x, y) {
    var house = __test_building_create(BUILDING_HOUSE_MEAGER_SHANTY, x, y)
    var neighbour = __test_building_create(neighbour_type, x + 1, y)
    if (!house || !neighbour) {
        t568_fail(name + ':place')
        return { worst: -1, neighbour: 0 }
    }
    var h = city.get_house(house)
    house_determine_worst_desirability_building(h)
    var worst = h.worst_desirability_building_id
    __log_info_native('[test:568] ' + name + ' worst=' + worst + ' neighbour=' + neighbour)
    return { worst: worst, neighbour: neighbour }
}

function run_test() {
    if (!test_reload_city_session('data/default.map')) {
        t568_fail('map_load')
        __test_signal_ready()
        return
    }

    var x = ((__scenario_map.width / 2) | 0) - 20
    var y = (__scenario_map.height / 2) | 0

    var same = t568_worst_next_to('same_level', BUILDING_HOUSE_MEAGER_SHANTY, x, y)
    if (same.worst != 0) {
        t568_fail('same_level:' + same.worst)
    }
    var higher = t568_worst_next_to('higher_level', BUILDING_HOUSE_COMMON_SHANTY, x + 15, y)
    if (higher.worst != 0) {
        t568_fail('higher_level:' + higher.worst)
    }
    var lower = t568_worst_next_to('lower_level', BUILDING_HOUSE_STURDY_HUT, x + 30, y)
    if (lower.worst != lower.neighbour) {
        t568_fail('lower_level:' + lower.worst)
    }

    test_reload_city_session('data/default.map')
    if (!__t568_failed) {
        __log_info_native('[test-marker] t568_ok')
    }
    __test_signal_ready()
}

function check_valid() {
    return !__t568_failed && __test_find_inlog('[test-marker] t568_ok')
}
