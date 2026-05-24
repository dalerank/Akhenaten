// Opens the Stonemasons' Guild building info panel via test helpers.
// The init handler logs "[test-marker] window_show:stonemason_guild_info_window".

function run_test() {
    __log_info_native('[test:06] creating stonemason guild and opening info window')
    __test_ensure_city_session('data/default.map')
    var bid = __test_building_create(BUILDING_STONEMASONS_GUILD, -1, -1)
    if (!bid) {
        __log_info_native('[test:06] __test_building_create failed')
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
    var marker = '[test-marker] window_show:stonemason_guild_info_window'
    if (!__test_find_inlog(marker)) {
        __log_info_native('[test:06] missing marker: ' + marker)
        return false
    }
    return true
}
