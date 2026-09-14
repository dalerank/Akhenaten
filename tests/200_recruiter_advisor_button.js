// Recruiter info: only the military advisor button, matching original barracks.
// Markers:
//   [test-marker] recruiter_advisor_ok

function run_test() {
    __log_info_native('[test:200] recruiter advisor button')
    test_ensure_city_session('data/default.map')
    city.set_advisor_available(ADVISOR_MILITARY, 1)

    var bid = __test_building_create(BUILDING_RECRUITER, -1, -1)
    if (!bid) {
        __log_info_native('[test:200] __test_building_create failed')
        __test_signal_ready()
        return
    }

    __test_show_tile_info(bid)
    __test_pump_frames(10)

    var oi = city.object_info
    var first = __test_info_ui_enabled('first_advisor')
    var second = __test_info_ui_enabled('second_advisor')
    var third = __test_info_ui_enabled('third_advisor')
    if (oi.go_to_advisor_first != ADVISOR_MILITARY
        || oi.go_to_advisor_left_a != ADVISOR_NONE
        || oi.go_to_advisor_left_b != ADVISOR_NONE
        || first != 1 || second != 0 || third != 0) {
        __log_info_native('[test:200] advisors mismatch first=' + oi.go_to_advisor_first
            + ' a=' + oi.go_to_advisor_left_a + ' b=' + oi.go_to_advisor_left_b
            + ' enabled=' + first + ',' + second + ',' + third)
        window_go_back()
        __test_signal_ready()
        return
    }

    __log_marker('recruiter_advisor_ok')
    window_go_back()
    __test_pump_frames(2)
    __test_signal_ready()
}

function check_valid() {
    var marker = '[test-marker] recruiter_advisor_ok'
    if (!__test_find_inlog(marker)) {
        __log_info_native('[test:200] missing marker: ' + marker)
        return false
    }
    return true
}
