// Egyptian / kingdom spearman missile spawn (Julius parity).
// Bug: create used home_building_id + target.tile→f->tile (missiles spawned on
// the target, not the thrower). Fixed → create(id, tile, dst).
// Markers:
//   [test-marker] spearman_missile_control_ok
//   [test-marker] spearman_missile_egyptian_ok
//   [test-marker] spearman_missile_kingdome_ok
//   [test-marker] spearman_missile_all_ok

function run_test() {
    __log_info_native('[test:038] egyptian/kingdom spearman missile spawn')
    test_ensure_city_session('data/default.map')

    if (!__test_enemy_figure_registered(FIGURE_ENEMY_EGYPTIAN_SPEAR)) {
        __log_info_native('[test:038] control failed: egyptian spear not registered')
        __test_signal_ready()
        return
    }
    __log_marker('spearman_missile_control_ok')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    var soldier = test_figure_create(FIGURE_INFANTRY, cx + 2, cy)
    if (!soldier || !__figure_is_valid(soldier)) {
        __log_info_native('[test:038] infantry bait spawn failed')
        __test_signal_ready()
        return
    }

    var spear = test_figure_create(FIGURE_ENEMY_EGYPTIAN_SPEAR, cx, cy)
    if (!spear || !__figure_is_valid(spear)) {
        __log_info_native('[test:038] egyptian spear spawn failed')
        __test_signal_ready()
        return
    }
    if (!__test_spearman_fire_initial_missile(spear)) {
        __log_info_native('[test:038] egyptian spear missile spawn/src tile failed')
        __test_signal_ready()
        return
    }
    __log_marker('spearman_missile_egyptian_ok')

    var javelin = test_figure_create(FIGURE_ENEMY_KINGDOME_JAVELIN, cx, cy + 1)
    if (!javelin || !__figure_is_valid(javelin)) {
        __log_info_native('[test:038] kingdom javelin spawn failed')
        __test_signal_ready()
        return
    }
    if (!__test_spearman_fire_initial_missile(javelin)) {
        __log_info_native('[test:038] kingdom javelin missile spawn/src tile failed')
        __test_signal_ready()
        return
    }
    __log_marker('spearman_missile_kingdome_ok')
    __log_marker('spearman_missile_all_ok')

    __test_figure_kill(spear)
    __test_figure_kill(javelin)
    __test_figure_kill(soldier)
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'spearman_missile_control_ok',
        'spearman_missile_egyptian_ok',
        'spearman_missile_kingdome_ok',
        'spearman_missile_all_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:038] missing marker: ' + marker)
            return false
        }
    }
    return true
}
