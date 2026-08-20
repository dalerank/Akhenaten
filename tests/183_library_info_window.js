// Library examine window: description (87.1) + staffing/papyrus status (87.2/87.3).
// Markers:
//   [test-marker] library_info_ok

function run_test() {
    __log_info_native('[test:183] library info window')
    test_ensure_city_session('data/default.map')
    var bid = __test_building_create(BUILDING_LIBRARY, -1, -1)
    if (!bid) {
        __log_info_native('[test:183] __test_building_create failed')
        __test_signal_ready()
        return
    }

    __test_show_tile_info(bid)
    __test_pump_frames(10)

    var warning = __test_info_ui_text('warning_text')
    var workers = __test_info_ui_text('workers_desc')
    var stored = __test_info_ui_text('resource_stored')
    var expect_warn = __loc("#library_info")
    var expect_idle = __loc("#library_info_idle")
    var expect_road = __loc("#building_no_road_access")

    if (!warning || warning.indexOf(expect_warn) < 0) {
        __log_info_native('[test:183] warning_text mismatch: "' + warning + '"')
        window_go_back()
        __test_signal_ready()
        return
    }
    if (!workers || (workers.indexOf(expect_idle) < 0 && workers.indexOf(expect_road) < 0)) {
        __log_info_native('[test:183] workers_desc mismatch: "' + workers + '"')
        window_go_back()
        __test_signal_ready()
        return
    }
    if (!stored) {
        __log_info_native('[test:183] resource_stored empty')
        window_go_back()
        __test_signal_ready()
        return
    }

    __log_marker('library_info_ok')
    window_go_back()
    __test_pump_frames(2)
    __test_signal_ready()
}

function check_valid() {
    var marker = '[test-marker] library_info_ok'
    if (!__test_find_inlog(marker)) {
        __log_info_native('[test:183] missing marker: ' + marker)
        return false
    }
    return true
}
