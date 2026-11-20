// Seth asp raid (TEMP Enhanced): game_feature ON, no batalion → spawn asps at TEMPLE_SETH.
// Markers:
//   [test-marker] seth_asp_feature_on_spawn_ok
//   [test-marker] seth_asp_feature_off_no_spawn_ok
//   [test-marker] seth_asp_no_temple_fallback_ok
//   [test-marker] seth_asp_raid_prey_ok
//   [test-marker] seth_asp_raid_timer_poof_ok

var GOD_SETH = 3
var ACTION_25_ASP_LOOKING_FOR_ATTACK = 25
var __test541_feat_prev = false
var __test541_on_ok = false
var __test541_off_ok = false
var __test541_fallback_ok = false
var __test541_prey_ok = false
var __test541_timer_ok = false

function test541_remove_asps() {
    city.figures.remove_figures(FIGURE_ASP)
}

function test541_count_asps() {
    return __test_count_figures(FIGURE_ASP)
}

function test541_place_temple() {
    if (!__scenario_building_allowed(BUILDING_TEMPLE_SETH)) {
        __scenario_building_allow(BUILDING_TEMPLE_SETH, true)
    }
    var bid = test_building_place(BUILDING_TEMPLE_SETH, -1, -1)
    if (!bid) {
        bid = __test_building_create(BUILDING_TEMPLE_SETH, -1, -1)
    }
    return bid
}

// Hail branch is ~50% (anti_scum_random); retry until asps appear or give up.
function test541_try_asp_curse(max_tries) {
    for (var i = 0; i < max_tries; i++) {
        test541_remove_asps()
        __test_run_console_command('god_major_curse ' + GOD_SETH)
        if (test541_count_asps() > 0) {
            return true
        }
    }
    return false
}

function run_test() {
    __log_info_native('[test:541] seth asp curse (CF7)')
    test_reload_city_session('data/default.map')
    __test_set_treasury(50000)
    game.paused = false

    __test541_feat_prev = game_features.get('gameplay_seth_asp_raid') === true

    // Clear any prior curse side-effects with feature OFF.
    game_features.set('gameplay_seth_asp_raid', false)
    __test_run_console_command('god_major_curse ' + GOD_SETH)
    test541_remove_asps()

    // --- Feature ON, no batalion: temple spawn (hail noeffect path) ---
    game_features.set('gameplay_seth_asp_raid', true)
    var temple = test541_place_temple()
    if (!temple) {
        __log_info_native('[test:541] failed to place BUILDING_TEMPLE_SETH')
        __test_signal_ready()
        return
    }

    if (!test541_try_asp_curse(40)) {
        __log_info_native('[test:541] feature ON expected asps after retries')
        __test_signal_ready()
        return
    }
    __log_marker('seth_asp_feature_on_spawn_ok')
    __test541_on_ok = true

    // --- Feature OFF: no asps when no batalion ---
    test541_remove_asps()
    game_features.set('gameplay_seth_asp_raid', false)
    for (var off_i = 0; off_i < 12; off_i++) {
        __test_run_console_command('god_major_curse ' + GOD_SETH)
        if (test541_count_asps() != 0) {
            __log_info_native('[test:541] feature OFF expected 0 asps, got ' + test541_count_asps())
            __test_signal_ready()
            return
        }
    }
    __log_marker('seth_asp_feature_off_no_spawn_ok')
    __test541_off_ok = true

    // --- Feature ON, no temple → fallback: no asps ---
    test_reload_city_session('data/default.map')
    __test_set_treasury(50000)
    game.paused = false
    game_features.set('gameplay_seth_asp_raid', false)
    __test_run_console_command('god_major_curse ' + GOD_SETH)
    test541_remove_asps()

    game_features.set('gameplay_seth_asp_raid', true)
    for (var fb_i = 0; fb_i < 12; fb_i++) {
        __test_run_console_command('god_major_curse ' + GOD_SETH)
        if (test541_count_asps() != 0) {
            __log_info_native('[test:541] no-temple fallback expected 0 asps, got ' + test541_count_asps())
            __test_signal_ready()
            return
        }
    }
    __log_marker('seth_asp_no_temple_fallback_ok')
    __test541_fallback_ok = true

    // --- Raid prey: skip closer ostrich, target invasion enemy ---
    test_reload_city_session('data/default.map')
    __test_set_treasury(50000)
    game.paused = false
    test541_remove_asps()

    var land = test_find_buildable_tile(BUILDING_HOUSE_CRUDE_HUT)
    if (!land) {
        land = { x: 40, y: 40 }
    }
    var ostrich = test_figure_create(FIGURE_OSTRICH, land.x + 1, land.y)
    var enemy = test_figure_create(FIGURE_ENEMY_HYKSOS_SWORDMAN, land.x + 3, land.y)
    var asp = test_figure_create(FIGURE_ASP, land.x + 2, land.y)
    if (!ostrich || !enemy || !asp) {
        __log_info_native('[test:541] raid prey spawn failed')
        __test_signal_ready()
        return
    }
    if (!__test_asp_setup_curse_raid(asp, 8)) {
        __log_info_native('[test:541] setup_curse_raid failed')
        __test_signal_ready()
        return
    }
    if (!__test_asp_is_curse_raid(asp)) {
        __log_info_native('[test:541] curse_raid flag not set')
        __test_signal_ready()
        return
    }

    test_figure_set_speed(ostrich, 0)
    test_figure_set_speed(enemy, 0)
    test_figure_set_speed(asp, 0)
    __test_figure_set_action(asp, ACTION_25_ASP_LOOKING_FOR_ATTACK)

    var prey_ok = false
    for (var i = 0; i < 120; i++) {
        test_figure_set_speed(ostrich, 0)
        test_figure_set_speed(enemy, 0)
        test_figure_set_speed(asp, 0)
        __test_pump_frames(1)

        if (!__figure_is_valid(asp) || !__figure_is_valid(ostrich) || !__figure_is_valid(enemy)) {
            break
        }
        var target = __figure_get_target_figure_id(asp)
        if (target == ostrich) {
            __log_info_native('[test:541] raid asp targeted ostrich (wildlife leak)')
            __test_signal_ready()
            return
        }
        if (target == enemy) {
            prey_ok = true
            break
        }
    }
    if (!prey_ok) {
        __log_info_native('[test:541] raid asp never targeted enemy')
        __test_signal_ready()
        return
    }
    __log_marker('seth_asp_raid_prey_ok')
    __test541_prey_ok = true

    // --- Duration: days=1 → first update_day poofs ---
    test541_remove_asps()
    var timer_asp = test_figure_create(FIGURE_ASP, land.x + 2, land.y)
    if (!timer_asp || !__test_asp_setup_curse_raid(timer_asp, 1)) {
        __log_info_native('[test:541] timer asp setup failed')
        __test_signal_ready()
        return
    }
    __test_figure_update_day(timer_asp)
    if (test541_count_asps() != 0) {
        __log_info_native('[test:541] expected 0 asps after timer poof, got ' + test541_count_asps())
        __test_signal_ready()
        return
    }
    __log_marker('seth_asp_raid_timer_poof_ok')
    __test541_timer_ok = true

    __test_signal_ready()
}

function check_valid() {
    if (!__test541_on_ok || !__test541_off_ok || !__test541_fallback_ok || !__test541_prey_ok || !__test541_timer_ok) {
        __log_info_native('[test:541] one or more phases failed')
        return false
    }

    var markers = [
        'seth_asp_feature_on_spawn_ok',
        'seth_asp_feature_off_no_spawn_ok',
        'seth_asp_no_temple_fallback_ok',
        'seth_asp_raid_prey_ok',
        'seth_asp_raid_timer_poof_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:541] missing marker: ' + marker)
            return false
        }
    }
    return true
}

function done() {
    game_features.set('gameplay_seth_asp_raid', __test541_feat_prev)
    test541_remove_asps()
}
