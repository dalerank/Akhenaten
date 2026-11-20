// Bast lion raid (TEMP Enhanced): game_feature ON, no houses → spawn lions at TEMPLE_BAST/COMPLEX/ZOO.
// Markers:
//   [test-marker] bast_lion_feature_on_spawn_ok
//   [test-marker] bast_lion_feature_off_no_spawn_ok
//   [test-marker] bast_lion_no_temple_fallback_ok
//   [test-marker] bast_lion_houses_smash_no_lions_ok
//   [test-marker] bast_lion_complex_only_spawn_ok
//   [test-marker] bast_lion_raid_prey_ok
//   [test-marker] bast_lion_raid_timer_poof_ok

var GOD_BAST = 4
var ACTION_25_LION_LOOKING_FOR_ATTACK = 25
var __test510_feat_prev = false
var __test510_on_ok = false
var __test510_off_ok = false
var __test510_fallback_ok = false
var __test510_smash_ok = false
var __test510_complex_ok = false
var __test510_prey_ok = false
var __test510_timer_ok = false

function test510_remove_lions() {
    city.figures.remove_figures(FIGURE_LION)
}

function test510_count_lions() {
    return __test_count_figures(FIGURE_LION)
}

function test510_place_temple() {
    if (!__scenario_building_allowed(BUILDING_TEMPLE_BAST)) {
        __scenario_building_allow(BUILDING_TEMPLE_BAST, true)
    }
    var bid = test_building_place(BUILDING_TEMPLE_BAST, -1, -1)
    if (!bid) {
        bid = __test_building_create(BUILDING_TEMPLE_BAST, -1, -1)
    }
    return bid
}

function test510_place_complex() {
    if (!__scenario_building_allowed(BUILDING_TEMPLE_COMPLEX_BAST)) {
        __scenario_building_allow(BUILDING_TEMPLE_COMPLEX_BAST, true)
    }
    var bid = __test_building_create(BUILDING_TEMPLE_COMPLEX_BAST, -1, -1)
    return bid
}

function run_test() {
    __log_info_native('[test:510] bast lion curse (CF5)')
    test_reload_city_session('data/default.map')
    __test_set_treasury(50000)
    game.paused = false

    __test510_feat_prev = game_features.get('gameplay_bast_lion_raid') === true

    // Clear any pre-existing houses via OFF smash (or wrath_2 if none).
    game_features.set('gameplay_bast_lion_raid', false)
    __test_run_console_command('god_major_curse ' + GOD_BAST)
    test510_remove_lions()

    // --- Feature ON, no houses: temple spawn ---
    game_features.set('gameplay_bast_lion_raid', true)
    var temple = test510_place_temple()
    if (!temple) {
        __log_info_native('[test:510] failed to place BUILDING_TEMPLE_BAST')
        __test_signal_ready()
        return
    }

    __test_run_console_command('god_major_curse ' + GOD_BAST)
    var lions = test510_count_lions()
    if (lions < 1) {
        __log_info_native('[test:510] feature ON expected lions, got ' + lions)
        __test_signal_ready()
        return
    }
    __log_marker('bast_lion_feature_on_spawn_ok')
    __test510_on_ok = true

    // --- Feature OFF: no lions when no houses ---
    test510_remove_lions()
    game_features.set('gameplay_bast_lion_raid', false)
    __test_run_console_command('god_major_curse ' + GOD_BAST)
    lions = test510_count_lions()
    if (lions != 0) {
        __log_info_native('[test:510] feature OFF expected 0 lions, got ' + lions)
        __test_signal_ready()
        return
    }
    __log_marker('bast_lion_feature_off_no_spawn_ok')
    __test510_off_ok = true

    // --- Feature ON, no houses, no temple/zoo → fallback (wrath_2 path): no lions ---
    test_reload_city_session('data/default.map')
    __test_set_treasury(50000)
    game.paused = false
    game_features.set('gameplay_bast_lion_raid', false)
    __test_run_console_command('god_major_curse ' + GOD_BAST)
    test510_remove_lions()

    game_features.set('gameplay_bast_lion_raid', true)
    __test_run_console_command('god_major_curse ' + GOD_BAST)
    lions = test510_count_lions()
    if (lions != 0) {
        __log_info_native('[test:510] no-temple fallback expected 0 lions, got ' + lions)
        __test_signal_ready()
        return
    }
    __log_marker('bast_lion_no_temple_fallback_ok')
    __test510_fallback_ok = true

    // --- Feature ON + house present → smash, not lions ---
    test510_remove_lions()
    var house = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, -1, -1)
    if (!house) {
        house = test_building_place(BUILDING_HOUSE_CRUDE_HUT, -1, -1)
    }
    if (!house) {
        __log_info_native('[test:510] failed to create house for smash path')
        __test_signal_ready()
        return
    }

    __test_run_console_command('god_major_curse ' + GOD_BAST)
    lions = test510_count_lions()
    if (lions != 0) {
        __log_info_native('[test:510] smash path expected 0 lions, got ' + lions)
        __test_signal_ready()
        return
    }
    __log_marker('bast_lion_houses_smash_no_lions_ok')
    __test510_smash_ok = true

    // --- Feature ON, complex only (no small temple / zoo) → lions ---
    test_reload_city_session('data/default.map')
    __test_set_treasury(50000)
    game.paused = false
    game_features.set('gameplay_bast_lion_raid', false)
    __test_run_console_command('god_major_curse ' + GOD_BAST)
    test510_remove_lions()

    game_features.set('gameplay_bast_lion_raid', true)
    var complex = test510_place_complex()
    if (!complex) {
        __log_info_native('[test:510] failed to create BUILDING_TEMPLE_COMPLEX_BAST')
        __test_signal_ready()
        return
    }
    __test_run_console_command('god_major_curse ' + GOD_BAST)
    lions = test510_count_lions()
    if (lions < 1) {
        __log_info_native('[test:510] complex-only expected lions, got ' + lions)
        __test_signal_ready()
        return
    }
    __log_marker('bast_lion_complex_only_spawn_ok')
    __test510_complex_ok = true

    // --- Raid prey: skip closer ostrich, target invasion enemy ---
    test_reload_city_session('data/default.map')
    __test_set_treasury(50000)
    game.paused = false
    test510_remove_lions()

    var land = test_find_buildable_tile(BUILDING_HOUSE_CRUDE_HUT)
    if (!land) {
        land = { x: 40, y: 40 }
    }
    var ostrich = test_figure_create(FIGURE_OSTRICH, land.x + 1, land.y)
    var enemy = test_figure_create(FIGURE_ENEMY_HYKSOS_SWORDMAN, land.x + 3, land.y)
    var lion = test_figure_create(FIGURE_LION, land.x + 2, land.y)
    if (!ostrich || !enemy || !lion) {
        __log_info_native('[test:510] raid prey spawn failed')
        __test_signal_ready()
        return
    }
    if (!__test_lion_setup_curse_raid(lion, 8)) {
        __log_info_native('[test:510] setup_curse_raid failed')
        __test_signal_ready()
        return
    }
    if (!__test_lion_is_curse_raid(lion)) {
        __log_info_native('[test:510] curse_raid flag not set')
        __test_signal_ready()
        return
    }

    test_figure_set_speed(ostrich, 0)
    test_figure_set_speed(enemy, 0)
    test_figure_set_speed(lion, 0)
    __test_figure_set_action(lion, ACTION_25_LION_LOOKING_FOR_ATTACK)

    var prey_ok = false
    for (var i = 0; i < 120; i++) {
        test_figure_set_speed(ostrich, 0)
        test_figure_set_speed(enemy, 0)
        test_figure_set_speed(lion, 0)
        __test_pump_frames(1)

        if (!__figure_is_valid(lion) || !__figure_is_valid(ostrich) || !__figure_is_valid(enemy)) {
            break
        }
        var target = __figure_get_target_figure_id(lion)
        if (target == ostrich) {
            __log_info_native('[test:510] raid lion targeted ostrich (wildlife leak)')
            __test_signal_ready()
            return
        }
        if (target == enemy) {
            prey_ok = true
            break
        }
    }
    if (!prey_ok) {
        __log_info_native('[test:510] raid lion never targeted enemy')
        __test_signal_ready()
        return
    }
    __log_marker('bast_lion_raid_prey_ok')
    __test510_prey_ok = true

    // --- Duration: days=1 → first update_day poofs ---
    test510_remove_lions()
    var timer_lion = test_figure_create(FIGURE_LION, land.x + 2, land.y)
    if (!timer_lion || !__test_lion_setup_curse_raid(timer_lion, 1)) {
        __log_info_native('[test:510] timer lion setup failed')
        __test_signal_ready()
        return
    }
    __test_figure_update_day(timer_lion)
    if (test510_count_lions() != 0) {
        __log_info_native('[test:510] expected 0 lions after timer poof, got ' + test510_count_lions())
        __test_signal_ready()
        return
    }
    __log_marker('bast_lion_raid_timer_poof_ok')
    __test510_timer_ok = true

    __test_signal_ready()
}

function check_valid() {
    if (!__test510_on_ok || !__test510_off_ok || !__test510_fallback_ok || !__test510_smash_ok
        || !__test510_complex_ok || !__test510_prey_ok || !__test510_timer_ok) {
        __log_info_native('[test:510] one or more phases failed')
        return false
    }

    var markers = [
        'bast_lion_feature_on_spawn_ok',
        'bast_lion_feature_off_no_spawn_ok',
        'bast_lion_no_temple_fallback_ok',
        'bast_lion_houses_smash_no_lions_ok',
        'bast_lion_complex_only_spawn_ok',
        'bast_lion_raid_prey_ok',
        'bast_lion_raid_timer_poof_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:510] missing marker: ' + marker)
            return false
        }
    }
    return true
}

function done() {
    game_features.set('gameplay_bast_lion_raid', __test510_feat_prev)
    test510_remove_lions()
}
