// TPG1–4: New Era trader per-good 1600 (gameplay_change_trader_per_good_1600).
// Markers:
//   [test-marker] trader_per_good_cap_ok
//   [test-marker] trader_per_good_buy_full_ok
//   [test-marker] trader_per_good_two_goods_ok
//   [test-marker] trader_per_good_has_traded_max_ok
//   [test-marker] trader_per_good_off_ok

var __test084_cap_ok = false
var __test084_buy_ok = false
var __test084_two_ok = false
var __test084_htm_ok = false
var __test084_off_ok = false

function run_test() {
    __log_info_native('[test:084] trader per-good 1600')
    test_ensure_city_session('data/default.map')

    game_features.set('gameplay_change_trader_per_good_1600', false)
    game_features.set('gameplay_change_trader_capacity_1600', false)

    if (__test_empire_trader_per_good_cap() != 0 || __test_empire_trader_ignore_total_bag() != 0) {
        __log_info_native('[test:084] OFF want cap=0 ignore=0')
        __test_signal_ready()
        return
    }

    game_features.set('gameplay_change_trader_per_good_1600', true)
    if (__test_empire_trader_per_good_cap() != 1600 || __test_empire_trader_ignore_total_bag() != 1) {
        __log_info_native('[test:084] ON want cap=1600 ignore=1 got '
            + __test_empire_trader_per_good_cap() + '/' + __test_empire_trader_ignore_total_bag())
        game_features.set('gameplay_change_trader_per_good_1600', false)
        __test_signal_ready()
        return
    }
    __log_marker('trader_per_good_cap_ok')
    __test084_cap_ok = true

    if (__test_empire_trader_buy_full_at(RESOURCE_POTTERY, 1500) != 0) {
        __log_info_native('[test:084] buy_full should be false at 1500')
        game_features.set('gameplay_change_trader_per_good_1600', false)
        __test_signal_ready()
        return
    }
    if (__test_empire_trader_buy_full_at(RESOURCE_POTTERY, 1600) != 1) {
        __log_info_native('[test:084] buy_full should be true at 1600')
        game_features.set('gameplay_change_trader_per_good_1600', false)
        __test_signal_ready()
        return
    }
    __log_marker('trader_per_good_buy_full_ok')
    __test084_buy_ok = true

    // Remaining room under cap (double-haul must not overshoot).
    if (__test_empire_trader_buy_room_at(RESOURCE_POTTERY, 1500) != 100) {
        __log_info_native('[test:084] buy_room at 1500 want 100 got '
            + __test_empire_trader_buy_room_at(RESOURCE_POTTERY, 1500))
        game_features.set('gameplay_change_trader_per_good_1600', false)
        __test_signal_ready()
        return
    }
    if (__test_empire_trader_buy_room_at(RESOURCE_POTTERY, 1600) != 0) {
        __log_info_native('[test:084] buy_room at 1600 want 0')
        game_features.set('gameplay_change_trader_per_good_1600', false)
        __test_signal_ready()
        return
    }

    // pottery at cap must not block beer (New Era multi-good visit).
    var two = __test_empire_trader_two_goods_buy_full(1600, 0)
    if (two != 10) {
        __log_info_native('[test:084] two-goods want pottery-full only (10) got ' + two)
        game_features.set('gameplay_change_trader_per_good_1600', false)
        __test_signal_ready()
        return
    }
    two = __test_empire_trader_two_goods_buy_full(1600, 1600)
    if (two != 11) {
        __log_info_native('[test:084] two-goods want both full (11) got ' + two)
        game_features.set('gameplay_change_trader_per_good_1600', false)
        __test_signal_ready()
        return
    }
    __log_marker('trader_per_good_two_goods_ok')
    __test084_two_ok = true

    // has_traded_max ignores totals when B is ON.
    if (__test_empire_trader_has_traded_max(1600, 0, 1600) != 0) {
        __log_info_native('[test:084] has_traded_max under B should be false at bought=1600')
        game_features.set('gameplay_change_trader_per_good_1600', false)
        __test_signal_ready()
        return
    }
    if (__test_empire_trader_has_traded_max(3200, 3200, 1600) != 0) {
        __log_info_native('[test:084] has_traded_max under B should stay false at high totals')
        game_features.set('gameplay_change_trader_per_good_1600', false)
        __test_signal_ready()
        return
    }
    __log_marker('trader_per_good_has_traded_max_ok')
    __test084_htm_ok = true

    game_features.set('gameplay_change_trader_per_good_1600', false)
    if (__test_empire_trader_buy_full_at(RESOURCE_POTTERY, 1600) != 0) {
        __log_info_native('[test:084] OFF buy_full must not gate at 1600')
        __test_signal_ready()
        return
    }
    if (__test_empire_trader_has_traded_max(1600, 0, 1600) != 1) {
        __log_info_native('[test:084] OFF has_traded_max should be true at bought=1600')
        __test_signal_ready()
        return
    }
    __log_marker('trader_per_good_off_ok')
    __test084_off_ok = true

    __test_signal_ready()
}

function check_valid() {
    if (!__test084_cap_ok) {
        __log_info_native('[test:084] cap check failed')
        return false
    }
    if (!__test084_buy_ok) {
        __log_info_native('[test:084] buy_full check failed')
        return false
    }
    if (!__test084_two_ok) {
        __log_info_native('[test:084] two-goods check failed')
        return false
    }
    if (!__test084_htm_ok) {
        __log_info_native('[test:084] has_traded_max check failed')
        return false
    }
    if (!__test084_off_ok) {
        __log_info_native('[test:084] OFF regression check failed')
        return false
    }
    return true
}

run_test()
