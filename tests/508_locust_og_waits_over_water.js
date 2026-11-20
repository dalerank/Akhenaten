// Locusts vs OG figure/plagues.c figure_locust_action: a waiting locust (FIGURE_ACTION_LOCUST_CREATED, no route yet)
// over water stays alive and keeps waiting; OG has no drowning for a figure that may fly anywhere.
// Markers:
//   [test-marker] locust_og_waits_over_water_ok

var ACTION_LOCUST_CREATED = 120

function test508_fail(msg) {
    __log_info_native('[test:508] FAIL: ' + msg)
}

function test508_place_farm() {
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var shifts = [[0, 0], [6, 0], [0, 6], [-6, 0], [0, -6], [6, 6], [-6, -6], [12, 0], [0, 12]]
    for (var i = 0; i < shifts.length; i++) {
        var x = cx + shifts[i][0]
        var y = cy + shifts[i][1]
        test_prepare_terrain_patch(x + 1, y + 1, 5, TERRAIN_FLOODPLAIN)
        var farm = test_building_place(BUILDING_GRAIN_FARM, x, y)
        if (farm) {
            return farm
        }
    }
    return 0
}

function test508_first_locust() {
    for (var i = 1; i < 2000; i++) {
        if (__figure_is_valid(i) && __figure_get_type(i) == FIGURE_LOCUST) {
            return i
        }
    }
    return 0
}

function test508_run() {
    test_reload_city_session('data/default.map')
    __scenario_building_allow(BUILDING_GRAIN_FARM, true)
    __test_set_treasury(500000)
    city.figures.remove_figures(FIGURE_LOCUST)
    if (!test508_place_farm()) {
        test508_fail('no farm placed')
        return
    }
    for (var month = 1; month <= 12 && !test508_first_locust(); month++) {
        __test_plagues_set_locusts_countdown(-1)
        __test_locust_update_month(month)
    }
    var fid = test508_first_locust()
    if (!fid || __figure_get_action_state(fid) != ACTION_LOCUST_CREATED) {
        test508_fail('no waiting locust')
        return
    }
    __test_figure_set_wait_ticks(fid, 50)
    var tile = __figure_get_tile(fid)
    __test_make_lake(tile.x, tile.y, 1, 1)
    if (!__map_terrain_is(tile, TERRAIN_WATER)) {
        test508_fail('no water under the locust at ' + tile.x + ',' + tile.y)
        return
    }
    __test_run_ticks(5)
    if (!__test_figure_is_alive(fid) || __figure_get_action_state(fid) != ACTION_LOCUST_CREATED) {
        test508_fail('waiting locust over water: alive=' + __test_figure_is_alive(fid) + ' action='
            + __figure_get_action_state(fid))
        return
    }
    __log_marker('locust_og_waits_over_water_ok')
}

function run_test() {
    __log_info_native('[test:508] OG locust waits over water')
    try {
        test508_run()
    } catch (e) {
        test508_fail('exception: ' + e)
    }
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] locust_og_waits_over_water_ok')
}

function done() {
    city.figures.remove_figures(FIGURE_LOCUST)
}
