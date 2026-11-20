// Every way into a city leaves the session listeners in place: after loading a map, loading a save from
// inside the city and loading a map again, the planner still reacts to event_city_building_mode and the
// tile info event still opens the building info window.
// Markers:
//   [test-marker] t525_ok:<phase>
//   [test-marker] t525_fail:<phase>:<what>

var __t525_map = 'data/default.map'
var __t525_failed = false

function t525_check(phase, bid) {
    if (!test_planner_enter_build_mode(BUILDING_STONEMASONS_GUILD)) {
        __log_info_native('[test-marker] t525_fail:' + phase + ':planner')
        __t525_failed = true
        return
    }
    test_planner_exit_build_mode()

    __test_show_tile_info(bid)
    __test_pump_frames(5)
    var opened = __ui_window_is('window_building_info')
    if (opened) {
        window_go_back()
        __test_pump_frames(2)
    }
    if (!opened) {
        __log_info_native('[test-marker] t525_fail:' + phase + ':tile_info')
        __t525_failed = true
        return
    }
    __log_info_native('[test-marker] t525_ok:' + phase)
}

function run_test() {
    if (!test_reload_city_session(__t525_map)) {
        __log_info_native('[test-marker] t525_fail:map:load')
        __t525_failed = true
        __test_signal_ready()
        return
    }
    var bid = __test_building_create(BUILDING_STONEMASONS_GUILD, -1, -1)
    if (!bid) {
        __log_info_native('[test-marker] t525_fail:map:building')
        __t525_failed = true
        __test_signal_ready()
        return
    }
    t525_check('map', bid)

    __test_save_memory('t796')
    if (!__test_load_memory('t796')) {
        __log_info_native('[test-marker] t525_fail:save:load')
        __t525_failed = true
    } else {
        __test_process_events()
        t525_check('save', bid)
    }
    __test_drop_memory_save('t796')

    if (!test_reload_city_session(__t525_map)) {
        __log_info_native('[test-marker] t525_fail:map_again:load')
        __t525_failed = true
        __test_signal_ready()
        return
    }
    bid = __test_building_create(BUILDING_STONEMASONS_GUILD, -1, -1)
    t525_check('map_again', bid)

    __test_signal_ready()
}

function check_valid() {
    if (__t525_failed) {
        return false
    }
    return __test_find_inlog('[test-marker] t525_ok:map')
        && __test_find_inlog('[test-marker] t525_ok:save')
        && __test_find_inlog('[test-marker] t525_ok:map_again')
}
