// #635: loading an early (calendar-start) save re-shows the mission start message;
// a later-month save must not.
// Markers:
//   [test-marker] start_message_early_reshow_ok
//   [test-marker] start_message_late_no_reshow_ok

var __test208_ok = false

function test208_fail(msg) {
    __log_info_native('[test:208] FAIL: ' + msg)
    __test_signal_ready()
}

function test208_roundtrip(save_name) {
    if (!__game_write_savegame(save_name)) {
        test208_fail('write_savegame failed: ' + save_name)
        return false
    }
    if (!__game_load_savegame(save_name)) {
        __game_delete_savegame(save_name)
        test208_fail('load_savegame failed: ' + save_name)
        return false
    }
    __game_delete_savegame(save_name)
    return true
}

function run_test() {
    __log_info_native('[test:208] start_message early vs late save load')
    __game_load_mission(0, 1)

    if (!mission.start_message_shown) {
        test208_fail('expected start_message_shown after mission0 start')
        return
    }
    if (game.simtime.year != scenario.start_year || game.simtime.month != 0) {
        test208_fail('expected calendar start after mission0 load y='
            + game.simtime.year + ' m=' + game.simtime.month
            + ' start_year=' + scenario.start_year)
        return
    }

    if (!test208_roundtrip('test_208_early_start_msg.svx')) {
        return
    }
    if (!__test_find_inlog('mission_start_message: cleared for early save load m=0')) {
        test208_fail('early save load did not clear start_message_shown')
        return
    }
    if (!mission.start_message_shown) {
        test208_fail('start_message_shown should be true again after early reshown')
        return
    }
    __log_marker('start_message_early_reshow_ok')

    game.simtime.month = 3
    if (game.simtime.month != 3) {
        test208_fail('could not set simtime.month for late-save case')
        return
    }
    mission.start_message_shown = true

    if (!test208_roundtrip('test_208_late_start_msg.svx')) {
        return
    }
    if (__test_find_inlog('mission_start_message: cleared for early save load m=3')) {
        test208_fail('late save load incorrectly cleared start_message_shown')
        return
    }
    if (!mission.start_message_shown) {
        test208_fail('start_message_shown should stay true after late load')
        return
    }
    __log_marker('start_message_late_no_reshow_ok')

    __test208_ok = true
    __log_info_native('[test:208] PASS')
    __test_signal_ready()
}

function check_valid() {
    if (!__test208_ok) {
        return false
    }
    return __test_find_inlog('[test-marker] start_message_early_reshow_ok')
        && __test_find_inlog('[test-marker] start_message_late_no_reshow_ok')
}
