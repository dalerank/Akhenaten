// Opens the Granary building info panel via test helpers.
// The init handler logs "[test-marker] window_show:info_window_granary".

function run_test() {
    __log_info_native('[test:08] creating granary and opening info window')
    __test_ensure_city_session('data/default.map')
    var bid = __test_building_create(BUILDING_GRANARY, -1, -1)
    if (!bid) {
        __log_info_native('[test:08] __test_building_create failed')
        __test_signal_ready()
        return
    }

    __test_show_tile_info(bid)
    __test_pump_frames(10)

    window_go_back()
    __test_pump_frames(2)

    __test_signal_ready()
}

function check_valid() {
    var marker = '[test-marker] window_show:info_window_granary'
    if (!__test_find_inlog(marker)) {
        __log_info_native('[test:08] missing marker: ' + marker)
        return false
    }
    return true
}
