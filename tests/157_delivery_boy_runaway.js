// RB4: delivery boy runaway when market buyer dies (corpse).
// Markers:
//   [test-marker] delivery_boy_runaway_setup_ok
//   [test-marker] delivery_boy_runaway_action_ok
//   [test-marker] delivery_boy_runaway_no_deposit_ok
//   [test-marker] delivery_boy_runaway_alive_after_kill_ok

var FIGURE_ACTION_132_FOLLOWER_RUNAWAY = 132

function run_test() {
    __log_info_native('[test:157] delivery boy runaway')
    test_ensure_city_session('data/default.map')

    var alone_prev = game_features.get('gameplay_change_delivery_boy_goes_to_market_alone')
    var runaway_prev = game_features.get('gameplay_change_follower_runaway')
    game_features.set('gameplay_change_delivery_boy_goes_to_market_alone', false)
    game_features.set('gameplay_change_follower_runaway', true)
    function finish() {
        game_features.set('gameplay_change_delivery_boy_goes_to_market_alone', alone_prev)
        game_features.set('gameplay_change_follower_runaway', runaway_prev)
        __test_signal_ready()
    }

    var bid = __test_building_create(BUILDING_BAZAAR, -1, -1)
    if (!bid) {
        __log_info_native('[test:157] FAIL: bazaar create')
        finish()
        return
    }

    var tile = __building_tile(bid)
    if (!tile) {
        __log_info_native('[test:157] FAIL: bazaar tile')
        finish()
        return
    }

    var buyer = test_figure_create(FIGURE_MARKET_BUYER, tile.x + 2, tile.y)
    var boy = test_figure_create(FIGURE_DELIVERY_BOY, tile.x + 3, tile.y)
    if (!buyer || !boy) {
        __log_info_native('[test:157] FAIL: spawn buyer/boy')
        finish()
        return
    }

    test_figure_set_home(buyer, bid)
    test_figure_set_home(boy, bid)
    __test_figure_set_leading(boy, buyer)
    __test_figure_set_collecting_item(boy, 0)
    __test_bazaar_set_inventory(bid, 0, 50)
    test_figure_set_force_valid_animation(buyer, true)
    test_figure_set_force_valid_animation(boy, true)

    __log_marker('delivery_boy_runaway_setup_ok')

    var boy_tile_before = __figure_get_tile(boy)
    __test_figure_kill(buyer)
    __test_figure_action_perform(boy)

    if (!__figure_is_valid(boy) || !__test_figure_is_alive(boy)) {
        __log_info_native('[test:157] FAIL: boy poofed instantly after buyer kill')
        finish()
        return
    }
    __log_marker('delivery_boy_runaway_alive_after_kill_ok')

    if (__figure_get_action_state(boy) != FIGURE_ACTION_132_FOLLOWER_RUNAWAY) {
        __log_info_native('[test:157] FAIL: want runaway 132 got ' + __figure_get_action_state(boy))
        finish()
        return
    }
    __log_marker('delivery_boy_runaway_action_ok')

    var inv = __test_bazaar_get_inventory(bid, 0)
    if (inv != 50) {
        __log_info_native('[test:157] FAIL: inventory bumped want 50 got ' + inv)
        finish()
        return
    }

    for (var i = 0; i < 8; i++) {
        __test_figure_action_perform(boy)
    }
    inv = __test_bazaar_get_inventory(bid, 0)
    if (inv != 50) {
        __log_info_native('[test:157] FAIL: inventory bumped during runaway want 50 got ' + inv)
        finish()
        return
    }
    __log_marker('delivery_boy_runaway_no_deposit_ok')

    if (boy_tile_before) {
        __log_info_native('[test:157] boy tile before kill=' + boy_tile_before.x + ',' + boy_tile_before.y)
    }

    finish()
}

function check_valid() {
    var markers = [
        'delivery_boy_runaway_setup_ok',
        'delivery_boy_runaway_alive_after_kill_ok',
        'delivery_boy_runaway_action_ok',
        'delivery_boy_runaway_no_deposit_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:157] missing marker: ' + marker)
            return false
        }
    }
    return true
}
