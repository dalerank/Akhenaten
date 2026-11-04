// FIG_BALLISTA / FIGURE_BALLISTA: OG tower ballista — params, home/sentry/worker
// kill, and FIRING aim tick fires FIGURE_JAVELIN (not bolt).
// Markers:
//   [test-marker] ballista_params_ok
//   [test-marker] ballista_spawn_ok
//   [test-marker] ballista_no_sentry_poof_ok
//   [test-marker] ballista_no_workers_poof_ok
//   [test-marker] ballista_fire_javelin_ok

var ACTION_180_BALLISTA_CREATED = 180
var ACTION_181_BALLISTA_FIRING = 181
var BUILDING_SLOT_BALLISTA = 3

var __test245_ok = false

function test245_fail(msg) {
    __log_info_native('[test:245] ' + msg)
    __test_signal_ready()
}

function test245_find(type) {
    for (var i = 1; i < 2000; i++) {
        if (__figure_is_valid(i) && __figure_get_type(i) == type && __test_figure_is_alive(i) == 1) {
            return i
        }
    }
    return 0
}

function run_test() {
    __log_info_native('[test:245] FIG_BALLISTA / ballista OG')

    // figure_category_inactive = 0
    if (__test_figure_type_category(FIGURE_BALLISTA) != 0) {
        return test245_fail('category want inactive(0) got ' + __test_figure_type_category(FIGURE_BALLISTA))
    }
    if (__test_figure_type_missile_attack(FIGURE_BALLISTA) != 100) {
        return test245_fail('missile_attack want 100 got ' + __test_figure_type_missile_attack(FIGURE_BALLISTA))
    }
    if (__test_figure_type_missile_delay(FIGURE_BALLISTA) != 100) {
        return test245_fail('missile_delay want 100 got ' + __test_figure_type_missile_delay(FIGURE_BALLISTA))
    }
    if (__test_figure_type_missile_range(FIGURE_BALLISTA) != 15) {
        return test245_fail('missile_range want 15 got ' + __test_figure_type_missile_range(FIGURE_BALLISTA))
    }
    __log_marker('ballista_params_ok')

    test_reload_city_session('data/default.map')
    city.figures.remove_figures(FIGURE_BALLISTA)
    city.figures.remove_figures(FIGURE_TOWER_SENTRY)
    city.figures.remove_figures(FIGURE_JAVELIN)
    city.figures.remove_figures(FIGURE_BOLT)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    var tower = __test_building_create(BUILDING_MUD_TOWER, cx, cy)
    if (!tower) {
        return test245_fail('tower create failed')
    }
    __test_building_force_road_access(tower)
    __test_building_set_workers(tower, 10)
    __test_make_wall(cx, cy)

    var sentry = test_figure_create(FIGURE_TOWER_SENTRY, cx, cy)
    if (!sentry) {
        return test245_fail('sentry create failed')
    }
    __test_figure_set_home(sentry, tower)
    __test_building_set_figure_slot(tower, 0, sentry)

    var ballista = test_figure_create(FIGURE_BALLISTA, cx, cy)
    if (!ballista) {
        return test245_fail('ballista create failed')
    }
    __test_figure_set_home(ballista, tower)
    __test_building_set_figure_slot(tower, BUILDING_SLOT_BALLISTA, ballista)
    __test_figure_set_action(ballista, ACTION_180_BALLISTA_CREATED)
    __test_figure_action_perform(ballista)
    if (__test_figure_is_alive(ballista) != 1) {
        return test245_fail('ballista should survive with workers+sentry')
    }
    if (__test_figure_get_action(ballista) != ACTION_180_BALLISTA_CREATED) {
        return test245_fail('spawn action want 180 got ' + __test_figure_get_action(ballista))
    }
    __log_marker('ballista_spawn_ok')

    // No sentry → poof
    city.figures.remove_figures(FIGURE_BALLISTA)
    __test_building_set_figure_slot(tower, 0, 0)
    ballista = test_figure_create(FIGURE_BALLISTA, cx, cy)
    __test_figure_set_home(ballista, tower)
    __test_building_set_figure_slot(tower, BUILDING_SLOT_BALLISTA, ballista)
    __test_figure_set_action(ballista, ACTION_180_BALLISTA_CREATED)
    __test_figure_action_perform(ballista)
    if (__test_figure_is_alive(ballista) == 1) {
        return test245_fail('should poof without sentry')
    }
    __log_marker('ballista_no_sentry_poof_ok')

    // No workers → poof
    city.figures.remove_figures(FIGURE_BALLISTA)
    sentry = test_figure_create(FIGURE_TOWER_SENTRY, cx, cy)
    __test_figure_set_home(sentry, tower)
    __test_building_set_figure_slot(tower, 0, sentry)
    __test_building_set_workers(tower, 0)
    ballista = test_figure_create(FIGURE_BALLISTA, cx, cy)
    __test_figure_set_home(ballista, tower)
    __test_building_set_figure_slot(tower, BUILDING_SLOT_BALLISTA, ballista)
    __test_figure_set_action(ballista, ACTION_180_BALLISTA_CREATED)
    __test_figure_action_perform(ballista)
    if (__test_figure_is_alive(ballista) == 1) {
        return test245_fail('should poof without workers')
    }
    __log_marker('ballista_no_workers_poof_ok')

    // FIRING aim tick fires FIGURE_JAVELIN (not bolt)
    __test_building_set_workers(tower, 10)
    city.figures.remove_figures(FIGURE_BALLISTA)
    city.figures.remove_figures(FIGURE_JAVELIN)
    city.figures.remove_figures(FIGURE_BOLT)
    city.figures.remove_figures(FIGURE_ENEMY_EGYPTIAN_SPEAR)

    ballista = test_figure_create(FIGURE_BALLISTA, cx, cy)
    __test_figure_set_home(ballista, tower)
    __test_building_set_figure_slot(tower, BUILDING_SLOT_BALLISTA, ballista)

    var enemy = test_figure_create(FIGURE_ENEMY_EGYPTIAN_SPEAR, cx + 3, cy)
    if (!enemy) {
        return test245_fail('enemy bait failed')
    }

    var delay = __test_figure_type_missile_delay(FIGURE_BALLISTA)
    __test_figure_set_action(ballista, ACTION_181_BALLISTA_FIRING)
    __test_figure_set_wait_ticks_missile(ballista, delay)
    __test_figure_set_wait_ticks(ballista, 9) // aim_ticks - 1 → next tick == 10 fires
    var javelins_before = __test_count_figures(FIGURE_JAVELIN)
    var bolts_before = __test_count_figures(FIGURE_BOLT)
    __test_figure_action_perform(ballista)
    if (__test_count_figures(FIGURE_JAVELIN) != javelins_before + 1) {
        return test245_fail('FIRING aim should spawn FIGURE_JAVELIN, got '
            + __test_count_figures(FIGURE_JAVELIN) + ' (before ' + javelins_before + ')')
    }
    if (__test_count_figures(FIGURE_BOLT) != bolts_before) {
        return test245_fail('must not fire FIGURE_BOLT')
    }
    __log_marker('ballista_fire_javelin_ok')

    __test245_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test245_ok
        && __test_find_inlog('[test-marker] ballista_params_ok')
        && __test_find_inlog('[test-marker] ballista_spawn_ok')
        && __test_find_inlog('[test-marker] ballista_no_sentry_poof_ok')
        && __test_find_inlog('[test-marker] ballista_no_workers_poof_ok')
        && __test_find_inlog('[test-marker] ballista_fire_javelin_ok')
}
