// Flat buildings view (FM*): session flag, flatten predicate, raise set, feature sync.
// Markers:
//   [test-marker] flat_view_on_ok
//   [test-marker] flat_should_flatten_ok
//   [test-marker] flat_raise_ok
//   [test-marker] flat_unraise_ok
//   [test-marker] flat_overlay_blocks_ok
//   [test-marker] flat_view_off_clears_raise_ok

// The view is gated by gameui_flat_buildings, which is off under OG defaults.
// Enable it here instead of relying on --enhanced, and restore it on every exit.
var __test88_feat_prev = false

function test88_finish() {
    game_features.set('gameui_flat_buildings', __test88_feat_prev)
    __test_signal_ready()
}

function test88_fail(reason) {
    __log_info_native('[test:88] ' + reason)
    test88_finish()
}

function run_test() {
    __log_info_native('[test:88] flat buildings view')
    test_ensure_city_session('data/default.map')

    __test88_feat_prev = game_features.get('gameui_flat_buildings') === true
    game_features.set('gameui_flat_buildings', true)

    __test_set_treasury(500000)
    if (!__scenario_building_allowed(BUILDING_VILLAGE_PALACE)) {
        __scenario_building_allow(BUILDING_VILLAGE_PALACE, true)
    }

    var bid = __test_building_create(BUILDING_VILLAGE_PALACE, -1, -1)
    if (!bid) {
        test88_fail('palace create failed')
        return
    }

    __city_flat_buildings_set(0)
    if (__city_flat_should_flatten(bid)) {
        test88_fail('should not flatten when view Off')
        return
    }

    __city_flat_buildings_set(1)
    if (!__city_flat_buildings_active()) {
        test88_fail('view On failed (feature off?)')
        return
    }
    __log_marker('flat_view_on_ok')

    if (!__city_flat_should_flatten(bid)) {
        test88_fail('expected flatten for palace while On')
        return
    }
    __log_marker('flat_should_flatten_ok')

    __city_flat_toggle_raised(bid)
    if (!__city_flat_is_raised(bid) || __city_flat_should_flatten(bid)) {
        test88_fail('raise should exclude from flatten')
        return
    }
    __log_marker('flat_raise_ok')

    __city_flat_toggle_raised(bid)
    if (__city_flat_is_raised(bid) || !__city_flat_should_flatten(bid)) {
        test88_fail('unraise should flatten again')
        return
    }
    __log_marker('flat_unraise_ok')

    // Overlay temporarily wins over flatten (view flag stays On).
    city.current_overlay = OVERLAY_FIRE
    if (__city_flat_should_flatten(bid)) {
        city.current_overlay = OVERLAY_NONE
        test88_fail('overlay should block flatten')
        return
    }
    city.current_overlay = OVERLAY_NONE
    if (!__city_flat_should_flatten(bid) || !__city_flat_buildings_active()) {
        test88_fail('after overlay exit should flatten again')
        return
    }
    __log_marker('flat_overlay_blocks_ok')

    __city_flat_toggle_raised(bid)
    __city_flat_buildings_set(0)
    if (__city_flat_is_raised(bid) || __city_flat_buildings_active()) {
        test88_fail('Off should clear raise + view')
        return
    }
    __log_marker('flat_view_off_clears_raise_ok')

    test88_finish()
}

function check_valid() {
    var markers = [
        'flat_view_on_ok',
        'flat_should_flatten_ok',
        'flat_raise_ok',
        'flat_unraise_ok',
        'flat_overlay_blocks_ok',
        'flat_view_off_clears_raise_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:88] missing marker: ' + marker)
            return false
        }
    }
    return true
}
