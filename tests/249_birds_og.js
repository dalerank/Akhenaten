// FIGURE_BIRDS: OG figure_birds_action (0x0049B750).
// Rest/choose → walk near herd home; spawn ghost; hunted → corpse; damage → flee.
// Markers:
//   [test-marker] birds_spawned_ok
//   [test-marker] birds_rest_to_walk_ok
//   [test-marker] birds_hunted_to_corpse_ok
//   [test-marker] birds_damage_flee_ok

var __test249_ok = false

function test249_fail(msg) {
    __log_info_native('[test:249] ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:249] birds OG')
    test_reload_city_session('data/default.map')
    city.figures.remove_figures(FIGURE_BIRDS)

    var fid = test_figure_create(FIGURE_BIRDS, 12, 14)
    if (!fid) {
        return test249_fail('create failed')
    }
    test_figure_set_force_valid_animation(fid, true)

    // SPAWNED (24): invisible until wait expires → CHOOSE (8).
    __test_figure_set_action(fid, 24)
    __test_figure_set_wait_ticks(fid, 2)
    __test_figure_action_perform(fid)
    if (__test_figure_is_visible(fid) != 0) {
        return test249_fail('spawned want invisible, visible=' + __test_figure_is_visible(fid))
    }
    __test_figure_set_wait_ticks(fid, 0)
    __test_figure_action_perform(fid)
    if (__figure_get_action_state(fid) != 8) {
        return test249_fail('spawned→choose want action 8, got ' + __figure_get_action_state(fid))
    }
    if (__test_figure_is_visible(fid) != 1) {
        return test249_fail('after spawn want visible')
    }
    __log_marker('birds_spawned_ok')

    // REST (18) with wait 0 → WALK (10) near home/tile.
    __test_figure_set_action(fid, 18)
    __test_figure_set_wait_ticks(fid, 0)
    __test_figure_action_perform(fid)
    var act = __figure_get_action_state(fid)
    if (act != 10 && act != 18) {
        return test249_fail('rest→walk want action 10 (or rest retry 18), got ' + act)
    }
    if (act == 10) {
        var dest = __figure_get_destination_tile(fid)
        if (!dest || dest.x < 0 || dest.y < 0) {
            return test249_fail('walk missing destination')
        }
    }
    __log_marker('birds_rest_to_walk_ok')

    // HUNTED (12): after dying_ticks → corpse (149).
    __test_figure_set_action(fid, 12)
    __test_figure_set_wait_ticks(fid, 500)
    __test_figure_action_perform(fid)
    if (__figure_get_action_state(fid) != 149) {
        return test249_fail('hunted→corpse want 149, got ' + __figure_get_action_state(fid))
    }
    __log_marker('birds_hunted_to_corpse_ok')

    // Damage scare bridge → FLEE (16) or ALERT (14).
    city.figures.remove_figures(FIGURE_BIRDS)
    var fid2 = test_figure_create(FIGURE_BIRDS, 20, 20)
    if (!fid2) {
        return test249_fail('create2 failed')
    }
    test_figure_set_force_valid_animation(fid2, true)
    __test_figure_set_action(fid2, 18)
    __test_figure_set_wait_ticks(fid2, 50)
    __test_figure_apply_damage(fid2, 1)
    __test_figure_action_perform(fid2)
    var a2 = __figure_get_action_state(fid2)
    if (a2 != 16 && a2 != 14 && a2 != 10) {
        return test249_fail('damage→flee want 16/14/10, got ' + a2)
    }
    if (!__figure_is_scared(fid2)) {
        return test249_fail('damage want scared flag')
    }
    __log_marker('birds_damage_flee_ok')

    __test249_ok = true
    __test_signal_ready()
}

function check_valid() {
    if (!__test249_ok) {
        return false
    }
    var markers = [
        'birds_spawned_ok',
        'birds_rest_to_walk_ok',
        'birds_hunted_to_corpse_ok',
        'birds_damage_flee_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:249] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}
