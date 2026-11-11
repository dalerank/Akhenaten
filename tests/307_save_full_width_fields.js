// game_time is four OG int32 fields bound at full width; a BC (negative) year must
// survive save -> load together with tick/day/month, and so must a request's
// months_left (OG int16).
// The on-disk sign-extension bytes themselves are not observable from JS.
// Markers:
//   [test-marker] save_full_width_year_ok
//   [test-marker] save_full_width_request_months_ok

function test307_fail(msg) {
    __log_info_native('[test:307] FAIL: ' + msg)
    __test_signal_ready()
}

function test307_roundtrip(save_name) {
    if (!__game_write_savegame(save_name)) {
        test307_fail('write_savegame failed: ' + save_name)
        return false
    }
    if (!__game_load_savegame(save_name)) {
        __game_delete_savegame(save_name)
        test307_fail('load_savegame failed: ' + save_name)
        return false
    }
    __game_delete_savegame(save_name)
    return true
}

function run_test() {
    __log_info_native('[test:307] save full-width fields')
    test_ensure_city_session('data/default.map')

    var want_year = -2850
    game.simtime.year = want_year
    game.simtime.month = 7
    game.simtime.day = 9
    game.simtime.tick = 13
    if (game.simtime.year != want_year) {
        test307_fail('could not set simtime.year, got ' + game.simtime.year)
        return
    }

    var tag = 30701
    var req = city.create_good_request({
        tag_id: tag,
        resource: RESOURCE_DEBEN,
        amount: 20,
        months_initial: 14
    })
    req.execute()
    __test_process_events()
    var months = __test_request_months_left(tag)
    if (months <= 0) {
        test307_fail('request months_left before save=' + months)
        return
    }

    if (!test307_roundtrip('test_307_full_width.svx')) {
        return
    }

    if (game.simtime.year != want_year || game.simtime.month != 7
        || game.simtime.day != 9 || game.simtime.tick != 13) {
        test307_fail('after load y=' + game.simtime.year + ' m=' + game.simtime.month
            + ' d=' + game.simtime.day + ' t=' + game.simtime.tick)
        return
    }
    __log_marker('save_full_width_year_ok')

    if (__test_request_months_left(tag) !== months) {
        test307_fail('request months_left after load=' + __test_request_months_left(tag) + ' want=' + months)
        return
    }
    __log_marker('save_full_width_request_months_ok')
    __test_signal_ready()
}

function check_valid() {
    var markers = ['save_full_width_year_ok', 'save_full_width_request_months_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:307] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}
