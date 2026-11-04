// FIGURE_OSTRICH: OG figure_ostrich_action (0x0049BD40) — items 1–8 safe port.
// Markers:
//   [test-marker] ostrich_spawned_ok
//   [test-marker] ostrich_choose_rest_walk_ok
//   [test-marker] ostrich_hunted_to_corpse_ok
//   [test-marker] ostrich_damage_flee_ok

var __test250_ok = false

function test250_fail(msg) {
    __log_info_native('[test:250] ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:250] ostrich OG')
    test_reload_city_session('data/default.map')
    city.figures.remove_figures(FIGURE_OSTRICH)

    var fid = test_figure_create(FIGURE_OSTRICH, 12, 14)
    if (!fid) {
        return test250_fail('create failed')
    }
    test_figure_set_force_valid_animation(fid, true)

    __test_figure_set_action(fid, 24)
    __test_figure_set_wait_ticks(fid, 2)
    __test_figure_action_perform(fid)
    if (__test_figure_is_visible(fid) != 0) {
        return test250_fail('spawned want invisible, visible=' + __test_figure_is_visible(fid))
    }
    __test_figure_set_wait_ticks(fid, 0)
    __test_figure_action_perform(fid)
    var after_spawn = __figure_get_action_state(fid)
    // CHOOSE (8) immediately picks REST(18)/GRAZE(19)
    if (after_spawn != 8 && after_spawn != 18 && after_spawn != 19) {
        return test250_fail('spawned→choose/rest/graze want 8/18/19, got ' + after_spawn)
    }
    if (__test_figure_is_visible(fid) != 1) {
        return test250_fail('after spawn want visible')
    }
    __log_marker('ostrich_spawned_ok')

    __test_figure_set_action(fid, 18)
    __test_figure_set_wait_ticks(fid, 0)
    __test_figure_action_perform(fid)
    var act = __figure_get_action_state(fid)
    if (act != 10 && act != 18) {
        return test250_fail('rest→walk want 10 (or rest retry 18), got ' + act)
    }
    __log_marker('ostrich_choose_rest_walk_ok')

    __test_figure_set_action(fid, 12)
    __test_figure_set_wait_ticks(fid, 500)
    __test_figure_action_perform(fid)
    if (__figure_get_action_state(fid) != 149) {
        return test250_fail('hunted→corpse want 149, got ' + __figure_get_action_state(fid))
    }
    __log_marker('ostrich_hunted_to_corpse_ok')

    city.figures.remove_figures(FIGURE_OSTRICH)
    var fid2 = test_figure_create(FIGURE_OSTRICH, 20, 20)
    if (!fid2) {
        return test250_fail('create2 failed')
    }
    test_figure_set_force_valid_animation(fid2, true)
    __test_figure_set_action(fid2, 18)
    __test_figure_set_wait_ticks(fid2, 50)
    __test_figure_apply_damage(fid2, 1)
    __test_figure_action_perform(fid2)
    var a2 = __figure_get_action_state(fid2)
    if (a2 != 16 && a2 != 14 && a2 != 10) {
        return test250_fail('damage→flee want 16/14/10, got ' + a2)
    }
    if (!__figure_is_scared(fid2)) {
        return test250_fail('damage want scared flag')
    }
    __log_marker('ostrich_damage_flee_ok')

    __test250_ok = true
    __test_signal_ready()
}

function check_valid() {
    if (!__test250_ok) {
        return false
    }
    var markers = [
        'ostrich_spawned_ok',
        'ostrich_choose_rest_walk_ok',
        'ostrich_hunted_to_corpse_ok',
        'ostrich_damage_flee_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:250] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}
