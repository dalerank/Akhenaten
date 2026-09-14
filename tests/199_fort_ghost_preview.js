// Fort ghost_preview lives in fort.js (shared by charioteers/infantry/archers).
// Markers:
//   [test-marker] test199_ghost_tables
//   [test-marker] test199_max_forts
//   [test-marker] test199_placement_check
//   [test-marker] test199_out_of_money_blocks
//   [test-marker] test199_place_ok

var __test199_ok = false

function run_test() {
    __log_info_native('[test:199] fort ghost preview')
    test_reload_city_session('data/default.map')
    __test_set_treasury(50000)
    if (!__scenario_building_allowed(BUILDING_FORT_INFANTRY)) {
        __scenario_building_allow(BUILDING_FORT_INFANTRY, true)
    }
    if (!__scenario_building_allowed(BUILDING_FORT_GROUND)) {
        __scenario_building_allow(BUILDING_FORT_GROUND, true)
    }

    var ghost = building_fort_ghost_config(BUILDING_FORT_INFANTRY)
    var n_ground = 0
    while (ghost && ghost.ground_check_offset && ghost.ground_check_offset[n_ground] !== undefined) {
        n_ground++
    }
    var n_main = 0
    while (ghost && ghost.main_view_offset && ghost.main_view_offset[n_main] !== undefined) {
        n_main++
    }
    var n_view = 0
    while (ghost && ghost.ground_view_offset && ghost.ground_view_offset[n_view] !== undefined) {
        n_view++
    }
    if (!ghost || n_ground != 16 || n_main != 4 || n_view != 4) {
        __log_info_native('[test:199] FAIL: ghost tables ground=' + n_ground + ' main=' + n_main + ' view=' + n_view
            + ' cfg_ghost=' + (building_fort_infantry && building_fort_infantry.ghost))
        __test_signal_ready()
        return
    }
    __log_marker('test199_ghost_tables')

    if ((city.max_forts | 0) < 6) {
        __log_info_native('[test:199] FAIL: max_forts=' + city.max_forts)
        __test_signal_ready()
        return
    }
    __log_marker('test199_max_forts')

    var tile = test_find_buildable_tile(BUILDING_FORT_INFANTRY)
    if (!tile) {
        __log_info_native('[test:199] FAIL: no buildable tile')
        __test_signal_ready()
        return
    }

    city_planner.build_type = BUILDING_FORT_INFANTRY
    city_planner.global_rotation = 0
    var ev = { start: tile, end: tile, pixel: { x: 0, y: 0 } }
    var check = building_fort_placement_check(ev)
    if (!check
        || check.fort_tiles.length != 9
        || check.ground_tiles.length != 16
        || check.orientation_index < 0
        || check.orientation_index > 3) {
        __log_info_native('[test:199] FAIL: placement_check sizes'
            + ' fort=' + (check ? check.fort_tiles.length : -1)
            + ' ground=' + (check ? check.ground_tiles.length : -1)
            + ' ori=' + (check ? check.orientation_index : -1))
        __test_signal_ready()
        return
    }
    __log_marker('test199_placement_check')

    __test_set_treasury(-5000)
    var broke = building_fort_placement_check(ev)
    __test_set_treasury(50000)
    if (!broke || !broke.fully_blocked || !broke.blocked) {
        __log_info_native('[test:199] FAIL: out of money should fully block')
        __test_signal_ready()
        return
    }
    __log_marker('test199_out_of_money_blocks')

    var bid = test_building_place(BUILDING_FORT_INFANTRY, tile.x, tile.y)
    if (!bid) {
        __log_info_native('[test:199] FAIL: place fort')
        __test_signal_ready()
        return
    }
    __log_marker('test199_place_ok')

    __test199_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test199_ok
        && __test_find_inlog('[test-marker] test199_ghost_tables')
        && __test_find_inlog('[test-marker] test199_max_forts')
        && __test_find_inlog('[test-marker] test199_placement_check')
        && __test_find_inlog('[test-marker] test199_out_of_money_blocks')
        && __test_find_inlog('[test-marker] test199_place_ok')
}
