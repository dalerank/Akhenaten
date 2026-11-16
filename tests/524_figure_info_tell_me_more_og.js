// OG building_info.c: a talker's window shows "tell me more" (lang 18/7) while another city problem weighs more
// than 1; the button moves the phrase to the next problem (window_figure_info_button_city_problem) and the advisor
// button follows the phrase's advisor.
// Markers:
//   [test-marker] tell_more_shown_ok
//   [test-marker] tell_more_click_ok
//   [test-marker] tell_more_hidden_ok

function run_test() {
    __log_info_native('[test:524] figure info tell me more')
    test_ensure_city_session('data/default.map')
    __test_city_problem_calm()
    var paused0 = game.paused
    game.paused = true
    function finish() {
        window_go_back()
        __test_pump_frames(2)
        game.paused = paused0
        __test_signal_ready()
    }

    // The work camp only gives a tile to click, as in test 211.
    var bid = __test_building_create(BUILDING_WORK_CAMP, -1, -1)
    var tile = __building_tile(bid)
    var juggler = test_figure_create(FIGURE_JUGGLER, tile.x, tile.y)
    test_figure_set_speed(juggler, 0)
    __test_pump_frames(3)
    __test_show_tile_info(bid)
    __test_pump_frames(10)
    if (__object_info_figure_id() != juggler) {
        __log_info_native('[test:524] figure window did not open for ' + juggler + ' got ' + __object_info_figure_id())
        finish()
        return
    }

    // Weights 8,6,8,8,4,8,0,6 and the juggler on the health problem.
    __test_city_problem_weights(15, 0, 1, 0, 0, 70, 100, 25, 0, 1000, 0, 0)
    __test_figure_set_phrase(juggler, 8, 0)
    __test_pump_frames(3)
    if (__test_info_ui_enabled('tell_more') != 1) {
        __log_info_native('[test:524] tell_more enabled=' + __test_info_ui_enabled('tell_more'))
        finish()
        return
    }
    __log_marker('tell_more_shown_ok')

    var before = __test_info_ui_text('phrase')
    figure_info_window_on_tell_more({})
    __test_pump_frames(3)
    var text = __test_info_ui_text('phrase')
    var said = __test_figure_phrase_now(juggler)
    if (said != '10:7:juggler_g08.wav' || !text || text == before) {
        __log_info_native('[test:524] after click phrase=' + said + ' text "' + before + '" -> "' + text + '"')
        finish()
        return
    }
    __log_marker('tell_more_click_ok')

    __test_city_problem_weights(100, 12, 0, 0, 0, 0, 0, 100, 100, 0, 0, 100)
    __test_pump_frames(3)
    if (__test_info_ui_enabled('tell_more') != 0) {
        __log_info_native('[test:524] calm city still shows tell_more')
        finish()
        return
    }
    __log_marker('tell_more_hidden_ok')
    finish()
}

function check_valid() {
    return __test_find_inlog('[test-marker] tell_more_shown_ok')
        && __test_find_inlog('[test-marker] tell_more_click_ok')
        && __test_find_inlog('[test-marker] tell_more_hidden_ok')
}
