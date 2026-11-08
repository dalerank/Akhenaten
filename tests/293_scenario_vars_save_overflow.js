// Mission vars that do not fit the 2000-byte save chunk: the save keeps whole lines only
// (keys in sorted order) and stays loadable instead of overflowing the buffer.

var __test293_ok = false

function run_test() {
    __log_info_native('[test:293] scenario vars save overflow')
    test_ensure_city_session('data/default.map')

    var filler = 'x'
    while (filler.length < 60) {
        filler = filler + 'x'
    }
    for (var i = 0; i < 40; i++) {
        var key = 'aaa_overflow_' + (i < 10 ? '0' + i : '' + i)
        __test_scenario_var_set_string(key, filler)
    }

    var save_name = 'test_293_vars_overflow.svx'
    if (!__game_write_savegame(save_name)) {
        __log_marker('vars_overflow_fail:write')
        __test_signal_ready()
        return
    }
    if (!__game_load_savegame(save_name)) {
        __game_delete_savegame(save_name)
        __log_marker('vars_overflow_fail:load')
        __test_signal_ready()
        return
    }
    __game_delete_savegame(save_name)

    var vars = __scenario_vars()
    if (vars['aaa_overflow_00'] != filler) {
        __log_marker('vars_overflow_fail:first_var_lost')
        __test_signal_ready()
        return
    }
    __log_marker('vars_overflow_ok')
    __test293_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test293_ok
        && __test_find_inlog('[test-marker] vars_overflow_ok')
        && __test_find_inlog('do not fit the 2000-byte save chunk')
}
