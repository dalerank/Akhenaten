// Festival priest without a festival square vs OG walkers.c figure_festival_priest_action:
//   picking the next spot with the square gone kills the priest; one sent while there is no square heads for
//   (-1 + 2, -1 + 2) on the roads and dies when it cannot get there.
// Markers:
//   [test-marker] festival_priest_square_gone_dies_ok
//   [test-marker] festival_priest_no_square_dies_ok

var ACTION_ARRIVED = 11

function t611_fail(msg) {
    __log_info_native('[test:611] FAIL: ' + msg)
}

function t611_priests() {
    var ids = []
    for (var i = 1; i < 2000; i++) {
        if (__test_figure_is_alive(i) && __figure_get_type(i) == FIGURE_FESTIVAL_PRIEST) {
            ids.push(i)
        }
    }
    return ids
}

function t611_perform_until(fid, action, max_ticks) {
    for (var t = 0; t < max_ticks && __figure_is_valid(fid); t++) {
        __test_figure_action_perform(fid)
        if (__figure_is_valid(fid) && __figure_get_action_state(fid) == action) {
            return t + 1
        }
    }
    return -1
}

function run_test() {
    __log_info_native('[test:611] festival priest without a square')
    test_reload_city_session('data/default.map')
    __test_set_treasury(1000000)
    __camera_rotate_north()
    city.figures.remove_figures(FIGURE_FESTIVAL_PRIEST)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    for (var x = cx - 10; x <= cx + 10; x++) {
        terrain.add({ x: x, y: cy }, TERRAIN_ROAD)
    }
    for (var d = -2; d <= 2; d++) {
        terrain.add({ x: cx + 7, y: cy + d }, TERRAIN_ROAD)
    }
    var square = test_building_place(BUILDING_FESTIVAL_SQUARE, cx + 5, cy - 2)
    var temple = test_building_place(BUILDING_TEMPLE_PTAH, cx - 8, cy + 1)
    if (!(square > 0) || !(temple > 0)) {
        t611_fail('setup: square ' + square + ' temple ' + temple)
        __test_signal_ready()
        return
    }
    __test_building_set_workers(temple, 20)
    __test_map_routing_update_land()
    __test_city_buildings_update_tick()

    __test_festival_spawn_celebrants(10)
    var ids = t611_priests()
    if (ids.length != 1) {
        t611_fail('want one priest, got ' + ids.length)
        __test_signal_ready()
        return
    }
    var fid = ids[0]
    if (t611_perform_until(fid, ACTION_ARRIVED, 5000) < 0) {
        t611_fail('priest ' + fid + ' never reached the square, alive ' + __figure_is_valid(fid))
        __test_signal_ready()
        return
    }
    __test_destroy_buildings_of_type(BUILDING_FESTIVAL_SQUARE)
    __test_city_buildings_update_tick()
    for (var t = 0; t < 3 && __figure_is_valid(fid); t++) {
        __test_figure_action_perform(fid)
    }
    if (__figure_is_valid(fid)) {
        t611_fail('priest ' + fid + ' outlived the square, action ' + __figure_get_action_state(fid))
        __test_signal_ready()
        return
    }
    __log_marker('festival_priest_square_gone_dies_ok')

    __test_festival_spawn_celebrants(10)
    ids = t611_priests()
    if (ids.length != 1) {
        t611_fail('no square: want one priest, got ' + ids.length)
        __test_signal_ready()
        return
    }
    fid = ids[0]
    for (var t2 = 0; t2 < 5000 && __figure_is_valid(fid); t2++) {
        __test_figure_action_perform(fid)
    }
    if (__figure_is_valid(fid)) {
        var tile = __figure_get_tile(fid)
        t611_fail('priest ' + fid + ' still alive at ' + tile.x + ',' + tile.y + ' action ' + __figure_get_action_state(fid))
        __test_signal_ready()
        return
    }
    __log_marker('festival_priest_no_square_dies_ok')
    __test_signal_ready()
}

function check_valid() {
    var markers = ['festival_priest_square_gone_dies_ok', 'festival_priest_no_square_dies_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:611] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

function done() {
    city.figures.remove_figures(FIGURE_FESTIVAL_PRIEST)
}
