// A lost render device drops every texture, the residency atlas page included: the atlas must
// invalidate, repack onto a fresh page and keep drawing.

var __test595_ok = false

function run_test() {
    __log_info_native('[test:595] residency atlas survives a render device reset')
    test_ensure_city_session('data/default.map')
    __test_pump_frames(5)

    var had_page = __test_find_inlog('residency_atlas: page allocated')
    __test_render_device_reset()
    __test_pump_frames(5)

    if (had_page && !__test_find_inlog('residency_atlas: atlas invalidated')) {
        __log_info_native('[test:595] FAIL: atlas page kept across the device reset')
        return __test_signal_ready()
    }

    __test_run_console_command('render_stats t595')
    if (!__test_find_inlog('render_stats[t595]')) {
        __log_info_native('[test:595] FAIL: render_stats wrote nothing')
        return __test_signal_ready()
    }

    __log_marker('render_atlas_device_reset_ok')
    __test595_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test595_ok && __test_find_inlog('[test-marker] render_atlas_device_reset_ok')
}
