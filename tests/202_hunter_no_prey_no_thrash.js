// Hunter with no prey nearby must not thrash RECALCULATE↔INVESTIGATE every frame.
// After RECALCULATE without prey it either walks INVESTIGATE or pauses in WAIT.

var __test202_ok = false

function run_test() {
    __log_info_native('[test:202] hunter no-prey no thrash')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var tile = { x: 20, y: 20 }
    var bid = __test_building_create(BUILDING_HUNTING_LODGE, tile.x, tile.y)
    if (!bid) {
        __log_info_native('[test:202] lodge create failed')
        __test_signal_ready()
        return
    }

    var hunter = test_figure_create(FIGURE_OSTRICH_HUNTER, tile.x + 2, tile.y)
    if (!hunter) {
        __log_info_native('[test:202] hunter create failed')
        __test_signal_ready()
        return
    }

    test_figure_set_home(hunter, bid)
    __test_figure_set_action(hunter, ACTION_8_RECALCULATE)

    var flips = 0
    var prev = __figure_get_action_state(hunter)
    var saw_wait = false
    var saw_investigate = false

    for (var i = 0; i < 40; i++) {
        __test_pump_frames(1)
        if (!__figure_is_valid(hunter)) {
            __log_info_native('[test:202] FAIL: hunter despawned')
            __test_signal_ready()
            return
        }
        var a = __figure_get_action_state(hunter)
        if (a == ACTION_13_OSTRICH_HUNTER_WAIT_FOR_ACTION) {
            saw_wait = true
        }
        if (a == ACTION_16_OSTRICH_HUNTER_INVESTIGATE) {
            saw_investigate = true
        }
        if (a != prev && (a == ACTION_8_RECALCULATE || a == ACTION_16_OSTRICH_HUNTER_INVESTIGATE
            || prev == ACTION_8_RECALCULATE || prev == ACTION_16_OSTRICH_HUNTER_INVESTIGATE)) {
            flips++
        }
        prev = a
    }

    // Thrash would be ~1 flip/frame (~40). Healthy roam/pause is far fewer.
    if (flips > 20) {
        __log_info_native('[test:202] FAIL: too many action flips=' + flips
            + ' last=' + prev + ' wait=' + saw_wait + ' inv=' + saw_investigate)
        __test_signal_ready()
        return
    }

    __log_marker('test202_hunter_no_prey_stable')
    __test202_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test202_ok
        && __test_find_inlog('[test-marker] test202_hunter_no_prey_stable')
}
