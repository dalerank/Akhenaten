// HL3: understaffed lodge keeps configured spawn cooldown after a hunter spawn.
// At 50% workers spawn_delay=10; reset must be 0 (not 10), else the next day
// already clears the gate.
// Markers:
//   [test-marker] lodge_spawn_delay_ok

var __test129_ok = false

function test129_fail(msg) {
    __log_info_native('[test:129] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:129] hunting lodge spawn delay (HL3)')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test_building_place(BUILDING_HUNTING_LODGE, -1, -1)
    if (!bid) {
        test129_fail('lodge place failed')
        return
    }

    // 3/6 workers → 50% → spawn_delay pct 50 = 10
    __test_building_set_workers(bid, 3)

    var hunters0 = __test_count_figures(FIGURE_OSTRICH_HUNTER)
        + __test_count_figures(FIGURE_ANTELOPE_HUNTER)
        + __test_count_figures(FIGURE_BIRDS_HUNTER)

    // Warm delay to just below threshold so one spawn_figure call can fire.
    __test_building_set_figure_spawn_delay(bid, 9)
    var spawned = __test_hunting_lodge_spawn_figure(bid)
    if (spawned != 1) {
        test129_fail('expected first hunter spawn, got delta=' + spawned)
        return
    }
    if (__test_building_figure_spawn_delay(bid) != 0) {
        test129_fail('after spawn delay want 0, got '
            + __test_building_figure_spawn_delay(bid))
        return
    }

    // Immediate follow-up must respect cooldown (delay becomes 1 < 10).
    spawned = __test_hunting_lodge_spawn_figure(bid)
    if (spawned != 0) {
        test129_fail('cooldown should block second spawn, got delta=' + spawned)
        return
    }
    if (__test_building_figure_spawn_delay(bid) != 1) {
        test129_fail('blocked spawn should leave delay=1, got '
            + __test_building_figure_spawn_delay(bid))
        return
    }

    // After a full cooldown window, spawn again.
    __test_building_set_figure_spawn_delay(bid, 9)
    spawned = __test_hunting_lodge_spawn_figure(bid)
    if (spawned != 1) {
        test129_fail('expected second hunter after cooldown, got delta=' + spawned)
        return
    }

    var hunters1 = __test_count_figures(FIGURE_OSTRICH_HUNTER)
        + __test_count_figures(FIGURE_ANTELOPE_HUNTER)
        + __test_count_figures(FIGURE_BIRDS_HUNTER)
    if (hunters1 != hunters0 + 2) {
        test129_fail('hunter count want +2, before=' + hunters0 + ' after=' + hunters1)
        return
    }

    __log_marker('lodge_spawn_delay_ok')
    __test129_ok = true
    __log_info_native('[test:129] PASS')
    __test_signal_ready()
}

function check_valid() {
    if (!__test129_ok) {
        __log_info_native('[test:129] run_test did not complete')
        return false
    }
    if (!__test_find_inlog('[test-marker] lodge_spawn_delay_ok')) {
        __log_info_native('[test:129] missing marker: lodge_spawn_delay_ok')
        return false
    }
    return true
}
