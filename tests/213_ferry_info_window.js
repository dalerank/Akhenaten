// Ferry examine window: title/warnings from lang group 159 (not Tower 91).
// Markers:
//   [test-marker] ferry_info_ok

function run_test() {
    __log_info_native('[test:213] ferry info window')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __scenario_building_allow(BUILDING_FERRY, true)

    var bid = test_shoreline_building_place(BUILDING_FERRY, 2)
    if (!bid) {
        __log_info_native('[test:213] shoreline place failed')
        __test_signal_ready()
        return
    }

    __test_show_tile_info(bid)
    __test_pump_frames(10)

    var title = __test_info_ui_text('title')
    var warning = __test_info_ui_text('warning_text')
    var expect_title = __loc(159, 0)
    var expect_no_link = __loc(159, 1)
    var wrong_tower = __loc(91, 0)

    if (!title || title.indexOf(expect_title) < 0) {
        __log_info_native('[test:213] title mismatch: "' + title + '" expected "' + expect_title + '"')
        window_go_back()
        __test_signal_ready()
        return
    }
    if (title.indexOf(wrong_tower) >= 0) {
        __log_info_native('[test:213] title still shows Tower: "' + title + '"')
        window_go_back()
        __test_signal_ready()
        return
    }
    if (!warning || warning.indexOf(expect_no_link) < 0) {
        __log_info_native('[test:213] warning_text mismatch: "' + warning + '"')
        window_go_back()
        __test_signal_ready()
        return
    }

    __log_marker('ferry_info_ok')
    window_go_back()
    __test_pump_frames(2)
    __test_signal_ready()
}

function check_valid() {
    var marker = '[test-marker] ferry_info_ok'
    if (!__test_find_inlog(marker)) {
        __log_info_native('[test:213] missing marker: ' + marker)
        return false
    }
    return true
}
