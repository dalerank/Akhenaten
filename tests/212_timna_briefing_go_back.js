// After Timna victory the Behdet/Abydos fork map must reopen from the next mission's
// briefing Back button. go_back used to omit completed_id, so choice[] collapsed and
// Timna reloaded instead.
// Markers:
//   [test-marker] timna_briefing_go_back_ok

var __test212_ok = false

function test212_fail(msg) {
    __log_info_native('[test:212] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:212] Timna briefing go_back restores choice map')

    game.mission_choice_open_scenario_id = 5
    game.mission_choice_completed_scenario_id = -1
    game.mission_briefing_scenario_id = 6
    mission_briefing_window_on_go_back({})
    __test_pump_frames(5)

    if (__test_find_inlog('mission_choice: no active fork for host 5 (completed -1)')) {
        test212_fail('go_back fell through to reload Timna (missing completed_id)')
        return
    }
    if (!__test_find_inlog('mission_briefing: go_back completed_id missing/invalid')) {
        test212_fail('missing go_back fallback log')
        return
    }
    if (!__test_find_inlog('mission_choice: open fork map host=5')) {
        test212_fail('missing open fork map log for Timna')
        return
    }
    if (game.mission_choice_open_scenario_id != 5) {
        test212_fail('expected open_scenario_id=5, got ' + game.mission_choice_open_scenario_id)
        return
    }
    if (game.mission_choice_completed_scenario_id != 5) {
        test212_fail('expected completed_scenario_id=5 after go_back, got '
            + game.mission_choice_completed_scenario_id)
        return
    }

    __log_marker('timna_briefing_go_back_ok')
    __test212_ok = true
    __log_info_native('[test:212] PASS')
    __test_signal_ready()
}

function check_valid() {
    return __test212_ok && __test_find_inlog('[test-marker] timna_briefing_go_back_ok')
}
