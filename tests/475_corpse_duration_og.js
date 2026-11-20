// Corpse lifetime: OG figure_combat_handle_corpse runs once per tick and removes the corpse on tick 128
// (FIGURE_CORPSE_LAST_TICK 127) for every figure type.
// Markers:
//   [test-marker] corpse_hyena_ok
//   [test-marker] corpse_crocodile_ok
//   [test-marker] corpse_ostrich_ok

var __test475_ok = false

function test475_fail(msg) {
    __log_info_native('[test:475] FAIL: ' + msg)
    __test_signal_ready()
}

function test475_corpse_ticks(type, x, y) {
    var fid = test_figure_create(type, x, y)
    if (!fid) {
        return -1
    }
    __test_figure_kill(fid)
    __test_figure_set_wait_ticks(fid, 0)
    for (var t = 1; t <= 600; t++) {
        __test_figure_action_perform_dying(fid)
        if (!__figure_is_valid(fid)) {
            return t
        }
    }
    return 0
}

function test475_expect(type, x, y, marker) {
    var ticks = test475_corpse_ticks(type, x, y)
    if (ticks != 128) {
        test475_fail(marker + ': type ' + type + ' corpse want removed on tick 128, got ' + ticks)
        return false
    }
    __log_marker(marker)
    return true
}

function run_test() {
    __log_info_native('[test:475] corpse duration OG')
    test_reload_city_session('data/default.map')
    city.remove_animals()

    var packed = __test_find_accessible_herd_tile(FIGURE_OSTRICH)
    if (packed < 0) {
        return test475_fail('no land tile')
    }
    var x = (packed >> 16) & 0xffff
    var y = packed & 0xffff

    if (!test475_expect(FIGURE_HYENA, x, y, 'corpse_hyena_ok')) return
    if (!test475_expect(FIGURE_CROCODILE, x, y, 'corpse_crocodile_ok')) return
    if (!test475_expect(FIGURE_OSTRICH, x, y, 'corpse_ostrich_ok')) return

    __test475_ok = true
    __test_signal_ready()
}

function check_valid() {
    if (!__test475_ok) {
        return false
    }
    var markers = ['corpse_hyena_ok', 'corpse_crocodile_ok', 'corpse_ostrich_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:475] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

function done() {
    city.remove_animals()
}
