// Verifies that the `show_mission_won` console command opens
// `window_mission_won`. The window's init handler writes
// "[test-marker] window_show:window_mission_won" to the log,
// which is what we look for to confirm the window actually became
// active (i.e. the event was emitted, the autoconfig window was
// resolved and pushed on the stack, and its init() ran).

function run_test() {
    __log_info_native('[test:03] dispatching console line: show_mission_won')
    __test_run_console_command('show_mission_won')

    // Pump enough frames for the event to be dispatched, the window
    // to be pushed onto the stack, and its draw_background -> init()
    // path (where __log_marker fires) to run.
    __test_pump_frames(10)

    window_go_back()
    __test_pump_frames(2)

    __test_signal_ready()
}

function check_valid() {
    var marker = '[test-marker] window_show:window_mission_won'
    if (!__test_find_inlog(marker)) {
        __log_info_native('[test:03] missing marker: ' + marker)
        return false
    }
    return true
}
