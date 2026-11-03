// FIG_ENEMY_HEAVY / figure_enemy_chariot: OG pulls_cart (CHARIOT_CART trailer),
// egyptian chariot speed_factor 2, drown on flooded floodplain (via fast_sword).
// Markers:
//   [test-marker] enemy_heavy_params_ok
//   [test-marker] enemy_heavy_cart_ok
//   [test-marker] enemy_heavy_egypt_speed_ok
//   [test-marker] enemy_heavy_drown_ok

var __test241_ok = false

function test241_fail(msg) {
    __log_info_native('[test:241] ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:241] FIG_ENEMY_HEAVY / enemy chariot OG')

    test_ensure_city_session('data/default.map')

    if (!__test_enemy_figure_registered(FIGURE_ENEMY_ASSYRIAN_CHARIOT)) {
        return test241_fail('assyrian chariot not registered')
    }
    if (!__test_enemy_figure_registered(FIGURE_ENEMY_EGYPTIAN_CHARIOT)) {
        return test241_fail('egyptian chariot not registered')
    }
    __log_marker('enemy_heavy_params_ok')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    var chariot = test_figure_create(FIGURE_ENEMY_ASSYRIAN_CHARIOT, cx, cy)
    if (!chariot) {
        return test241_fail('assyrian chariot create failed')
    }
    __test_figure_set_action(chariot, ACTION_151_ENEMY_FAST_SWORD_INITIAL)
    __test_figure_set_wait_ticks(chariot, 1)
    __test_figure_action_perform(chariot)
    // update_animation runs with figure_image_update during draw; drive it via action path
    // by performing again after INITIAL sets up — cart is refreshed in update_animation.
    if (!__test_enemy_chariot_refresh_cart(chariot)) {
        return test241_fail('chariot cart refresh failed')
    }
    if (__test_figure_cart_image_id(chariot) <= 0) {
        return test241_fail('OG pulls_cart: cart_image_id should be set')
    }
    __log_marker('enemy_heavy_cart_ok')

    var egypt = test_figure_create(FIGURE_ENEMY_EGYPTIAN_CHARIOT, cx + 2, cy)
    if (!egypt) {
        return test241_fail('egyptian chariot create failed')
    }
    if (__test_enemy_speed_multiplier(egypt) != 2) {
        return test241_fail('egyptian chariot speed_factor should be 2, got '
            + __test_enemy_speed_multiplier(egypt))
    }
    __log_marker('enemy_heavy_egypt_speed_ok')

    city.figures.remove_figures(FIGURE_ENEMY_ASSYRIAN_CHARIOT)
    city.figures.remove_figures(FIGURE_ENEMY_EGYPTIAN_CHARIOT)
    var drown = test_figure_create(FIGURE_ENEMY_ASSYRIAN_CHARIOT, cx + 4, cy + 4)
    if (!drown) {
        return test241_fail('drown create failed')
    }
    var dt = __figure_get_tile(drown)
    __test_make_floodplain_water(dt.x, dt.y)
    __test_figure_action_perform(drown)
    if (__test_figure_is_alive(drown) == 1) {
        return test241_fail('should drown on flooded floodplain')
    }
    __log_marker('enemy_heavy_drown_ok')

    __test241_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test241_ok
        && __test_find_inlog('[test-marker] enemy_heavy_params_ok')
        && __test_find_inlog('[test-marker] enemy_heavy_cart_ok')
        && __test_find_inlog('[test-marker] enemy_heavy_egypt_speed_ok')
        && __test_find_inlog('[test-marker] enemy_heavy_drown_ok')
}
