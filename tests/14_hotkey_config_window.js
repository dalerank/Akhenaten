// Verifies that window_show_by_id("window_hotkey_config") opens the hotkey
// config window. The init handler logs
// "[test-marker] window_show:window_hotkey_config".

function run_test() {
    __log_info_native('[test:14] opening hotkey config window')
    window_show_by_id("window_hotkey_config")
    __test_pump_frames(10)

    window_go_back()
    __test_pump_frames(2)

    __test_signal_ready()
}

function check_valid() {
    var marker = '[test-marker] window_show:window_hotkey_config'
    if (!__test_find_inlog(marker)) {
        __log_info_native('[test:14] missing marker: ' + marker)
        return false
    }
    return true
}
