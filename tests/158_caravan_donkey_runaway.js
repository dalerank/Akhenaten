// RB4: caravan donkey — OG dies with leader; Enhanced runaway (132) when feature on.
// Markers:
//   [test-marker] caravan_donkey_og_dead_ok
//   [test-marker] caravan_donkey_runaway_setup_ok
//   [test-marker] caravan_donkey_runaway_alive_after_kill_ok
//   [test-marker] caravan_donkey_runaway_action_ok

var FIGURE_ACTION_132_FOLLOWER_RUNAWAY = 132

function run_test() {
    __log_info_native('[test:158] caravan donkey runaway')
    test_ensure_city_session('data/default.map')

    var prev = game_features.get('gameplay_change_follower_runaway')
    function finish() {
        game_features.set('gameplay_change_follower_runaway', prev)
        __test_signal_ready()
    }

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    // OG default: donkey dies with the caravan head.
    game_features.set('gameplay_change_follower_runaway', false)
    var head_og = test_figure_create(FIGURE_TRADE_CARAVAN, cx, cy)
    var donkey_og = test_figure_create(FIGURE_TRADE_CARAVAN_DONKEY, cx + 1, cy)
    if (!head_og || !donkey_og) {
        __log_info_native('[test:158] FAIL: spawn OG caravan/donkey')
        finish()
        return
    }
    __test_figure_set_leading(donkey_og, head_og)
    test_figure_set_force_valid_animation(head_og, true)
    test_figure_set_force_valid_animation(donkey_og, true)
    __test_figure_kill(head_og)
    __test_figure_action_perform(donkey_og)
    if (__figure_is_valid(donkey_og) && __test_figure_is_alive(donkey_og)) {
        __log_info_native('[test:158] FAIL: OG donkey should die with leader')
        finish()
        return
    }
    __log_marker('caravan_donkey_og_dead_ok')

    // Enhanced: flee to exit (132).
    game_features.set('gameplay_change_follower_runaway', true)
    var head = test_figure_create(FIGURE_TRADE_CARAVAN, cx, cy + 2)
    var donkey = test_figure_create(FIGURE_TRADE_CARAVAN_DONKEY, cx + 1, cy + 2)
    if (!head || !donkey) {
        __log_info_native('[test:158] FAIL: spawn Enhanced caravan/donkey')
        finish()
        return
    }

    __test_figure_set_leading(donkey, head)
    test_figure_set_force_valid_animation(head, true)
    test_figure_set_force_valid_animation(donkey, true)

    __log_marker('caravan_donkey_runaway_setup_ok')

    __test_figure_kill(head)
    __test_figure_action_perform(donkey)

    if (!__figure_is_valid(donkey) || !__test_figure_is_alive(donkey)) {
        __log_info_native('[test:158] FAIL: donkey poofed instantly after head kill')
        finish()
        return
    }
    __log_marker('caravan_donkey_runaway_alive_after_kill_ok')

    if (__figure_get_action_state(donkey) != FIGURE_ACTION_132_FOLLOWER_RUNAWAY) {
        __log_info_native('[test:158] FAIL: want runaway 132 got ' + __figure_get_action_state(donkey))
        finish()
        return
    }
    __log_marker('caravan_donkey_runaway_action_ok')

    finish()
}

function check_valid() {
    var markers = [
        'caravan_donkey_og_dead_ok',
        'caravan_donkey_runaway_setup_ok',
        'caravan_donkey_runaway_alive_after_kill_ok',
        'caravan_donkey_runaway_action_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:158] missing marker: ' + marker)
            return false
        }
    }
    return true
}
