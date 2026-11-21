// Clearing land over a fort asks for a confirmation first and leaves the fort standing until the answer.
// Markers:
//   [test-marker] t573_ok
//   [test-marker] t573_fail:<what>

var __t573_failed = false

function t573_fail(what) {
    __log_info_native('[test-marker] t573_fail:' + what)
    __t573_failed = true
}

function t573_run() {
    if (!test_reload_city_session('data/default.map')) {
        return t573_fail('load')
    }
    __test_set_treasury(50000)
    __scenario_building_allow(BUILDING_FORT_INFANTRY, true)
    __scenario_building_allow(BUILDING_FORT_GROUND, true)
    var tile = test_find_buildable_tile(BUILDING_FORT_INFANTRY)
    if (!tile) {
        return t573_fail('no_tile')
    }
    var bid = test_building_place(BUILDING_FORT_INFANTRY, tile.x, tile.y)
    if (!bid) {
        return t573_fail('place')
    }

    if (!test_planner_enter_build_mode(BUILDING_CLEAR_LAND)) {
        return t573_fail('clear_land_mode')
    }
    city_planner.construction_start(tile.x, tile.y)
    city_planner.construction_update(tile.x, tile.y)
    city_planner.construction_finalize()
    __test_process_events()
    if (!__test_popup_dialog_is_open()) {
        return t573_fail('no_confirmation')
    }
    if (__building_at(tile.x, tile.y) != bid) {
        return t573_fail('cleared_before_yes')
    }
    test_planner_exit_build_mode()
}

function run_test() {
    t573_run()
    if (!__t573_failed) {
        __log_info_native('[test-marker] t573_ok')
    }
    __test_signal_ready()
}

function check_valid() {
    return !__t573_failed && __test_find_inlog('[test-marker] t573_ok')
}
