// Verifies that the `show_victory_dialog` console command opens
// `window_victory_dialog`. The window's init handler writes
// "[test-marker] window_show:window_victory_dialog" to the log.

function run_test() {
    __log_info_native('[test:15] dispatching console line: show_victory_dialog')
    __test_run_console_command('show_victory_dialog')

    __test_pump_frames(10)

    window_go_back()
    __test_pump_frames(2)

    __test_signal_ready()
}

function check_valid() {
    var marker = '[test-marker] window_show:window_victory_dialog'
    if (!__test_find_inlog(marker)) {
        __log_info_native('[test:15] missing marker: ' + marker)
        return false
    }
    return true
}
