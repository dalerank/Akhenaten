// OG windows 0x4F/0x50: a click on a chief advisor row opens the comment panel with its text and the
// advisor it points to; a click on a god in the religion advisor opens the god's description (group 59, 32+god).
// Markers:
//   [test-marker] advisor_comment_window_ok
//   [test-marker] advisor_comment_window_skip_ok
//   [test-marker] god_description_window_ok

function t504_fail(msg) {
    __log_info_native('[test:504] ' + msg)
    if (ui.window_is('advisor_comment_window')) {
        window_go_back()
    }
    __test_advisor_state_clear()
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:504] advisor comment window')
    test_ensure_city_session('data/default.map')

    __test_advisor_state_clear()
    __test_advisor_state_set('health', 55)
    if (!advisor_chief_open_comment(ADVISOR_COMMENT_HEALTH)) {
        return t504_fail('health comment did not open')
    }
    __test_pump_frames(2)
    if (!ui.window_is('advisor_comment_window')
        || advisor_comment_state.text_group !== 61
        || advisor_comment_state.text_id !== 119
        || advisor_comment_state.advisor !== ADVISOR_HEALTH) {
        return t504_fail('comment window state group=' + advisor_comment_state.text_group
            + ' text=' + advisor_comment_state.text_id + ' advisor=' + advisor_comment_state.advisor)
    }
    __log_marker('advisor_comment_window_ok')
    window_go_back()
    __test_pump_frames(2)

    __test_advisor_state_set('sentiment', 100)
    if (advisor_chief_open_comment(ADVISOR_COMMENT_SENTIMENT) || ui.window_is('advisor_comment_window')) {
        return t504_fail('sentiment 100 opened a comment')
    }
    __log_marker('advisor_comment_window_skip_ok')
    __test_advisor_state_clear()

    advisor_religion_window_on_god_click({ user_data: 1 })
    __test_pump_frames(2)
    var want = 32 + gods[1].type
    if (!ui.window_is('advisor_comment_window')
        || advisor_comment_state.text_group !== 59
        || advisor_comment_state.text_id !== want
        || advisor_comment_state.advisor !== ADVISOR_NONE) {
        return t504_fail('god description state group=' + advisor_comment_state.text_group
            + ' text=' + advisor_comment_state.text_id + ' want ' + want)
    }
    __log_marker('god_description_window_ok')
    window_go_back()
    __test_pump_frames(2)
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] advisor_comment_window_ok')
        && __test_find_inlog('[test-marker] advisor_comment_window_skip_ok')
        && __test_find_inlog('[test-marker] god_description_window_ok')
}
