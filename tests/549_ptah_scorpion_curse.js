// Ptah scorpion raid (TEMP Enhanced): game_feature ON, no industry → spawn at TEMPLE_PTAH.
// Markers:
//   [test-marker] ptah_scorpion_feature_on_spawn_ok
//   [test-marker] ptah_scorpion_feature_off_no_spawn_ok
//   [test-marker] ptah_scorpion_no_temple_fallback_ok
//   [test-marker] ptah_scorpion_raid_prey_ok
//   [test-marker] ptah_scorpion_raid_timer_poof_ok

var GOD_PTAH = 2
var ACTION_25_SCORPION_LOOKING_FOR_ATTACK = 25
var __test549_feat_prev = false
var __test549_on_ok = false
var __test549_off_ok = false
var __test549_fallback_ok = false
var __test549_prey_ok = false
var __test549_timer_ok = false

function test549_remove_scorpions() {
    city.figures.remove_figures(FIGURE_SCORPION)
}

function test549_count_scorpions() {
    return __test_count_figures(FIGURE_SCORPION)
}

function test549_place_temple() {
    if (!__scenario_building_allowed(BUILDING_TEMPLE_PTAH)) {
        __scenario_building_allow(BUILDING_TEMPLE_PTAH, true)
    }
    var bid = test_building_place(BUILDING_TEMPLE_PTAH, -1, -1)
    if (!bid) {
        bid = __test_building_create(BUILDING_TEMPLE_PTAH, -1, -1)
    }
    return bid
}

// Industry branch is ~50% (anti_scum_random); retry until scorpions appear or give up.
function test549_try_scorpion_curse(max_tries) {
    for (var i = 0; i < max_tries; i++) {
        test549_remove_scorpions()
        __test_run_console_command('god_major_curse ' + GOD_PTAH)
        if (test549_count_scorpions() > 0) {
            return true
        }
    }
    return false
}

function run_test() {
    __log_info_native('[test:549] ptah scorpion curse (CF6)')
    test_reload_city_session('data/default.map')
    __test_set_treasury(50000)
    game.paused = false

    __test549_feat_prev = game_features.get('gameplay_ptah_scorpion_raid') === true

    // Clear any prior curse side-effects with feature OFF.
    game_features.set('gameplay_ptah_scorpion_raid', false)
    __test_run_console_command('god_major_curse ' + GOD_PTAH)
    test549_remove_scorpions()

    // --- Feature ON, no industry: temple spawn (industry-fail path) ---
    game_features.set('gameplay_ptah_scorpion_raid', true)
    var temple = test549_place_temple()
    if (!temple) {
        __log_info_native('[test:549] failed to place BUILDING_TEMPLE_PTAH')
        __test_signal_ready()
        return
    }

    if (!test549_try_scorpion_curse(40)) {
        __log_info_native('[test:549] feature ON expected scorpions after retries')
        __test_signal_ready()
        return
    }
    __log_marker('ptah_scorpion_feature_on_spawn_ok')
    __test549_on_ok = true

    // --- Feature OFF: no scorpions when no industry ---
    test549_remove_scorpions()
    game_features.set('gameplay_ptah_scorpion_raid', false)
    for (var off_i = 0; off_i < 12; off_i++) {
        __test_run_console_command('god_major_curse ' + GOD_PTAH)
        if (test549_count_scorpions() != 0) {
            __log_info_native('[test:549] feature OFF expected 0 scorpions, got ' + test549_count_scorpions())
            __test_signal_ready()
            return
        }
    }
    __log_marker('ptah_scorpion_feature_off_no_spawn_ok')
    __test549_off_ok = true

    // --- Feature ON, no temple → fallback: no scorpions ---
    test_reload_city_session('data/default.map')
    __test_set_treasury(50000)
    game.paused = false
    game_features.set('gameplay_ptah_scorpion_raid', false)
    __test_run_console_command('god_major_curse ' + GOD_PTAH)
    test549_remove_scorpions()

    game_features.set('gameplay_ptah_scorpion_raid', true)
    for (var fb_i = 0; fb_i < 12; fb_i++) {
        __test_run_console_command('god_major_curse ' + GOD_PTAH)
        if (test549_count_scorpions() != 0) {
            __log_info_native('[test:549] no-temple fallback expected 0 scorpions, got ' + test549_count_scorpions())
            __test_signal_ready()
            return
        }
    }
    __log_marker('ptah_scorpion_no_temple_fallback_ok')
    __test549_fallback_ok = true

    // --- Raid prey: skip closer ostrich, target invasion enemy ---
    test_reload_city_session('data/default.map')
    __test_set_treasury(50000)
    game.paused = false
    test549_remove_scorpions()

    var land = test_find_buildable_tile(BUILDING_HOUSE_CRUDE_HUT)
    if (!land) {
        land = { x: 40, y: 40 }
    }
    var ostrich = test_figure_create(FIGURE_OSTRICH, land.x + 1, land.y)
    var enemy = test_figure_create(FIGURE_ENEMY_HYKSOS_SWORDMAN, land.x + 3, land.y)
    var scorpion = test_figure_create(FIGURE_SCORPION, land.x + 2, land.y)
    if (!ostrich || !enemy || !scorpion) {
        __log_info_native('[test:549] raid prey spawn failed')
        __test_signal_ready()
        return
    }
    if (!__test_scorpion_setup_curse_raid(scorpion, 8)) {
        __log_info_native('[test:549] setup_curse_raid failed')
        __test_signal_ready()
        return
    }
    if (!__test_scorpion_is_curse_raid(scorpion)) {
        __log_info_native('[test:549] curse_raid flag not set')
        __test_signal_ready()
        return
    }

    test_figure_set_speed(ostrich, 0)
    test_figure_set_speed(enemy, 0)
    test_figure_set_speed(scorpion, 0)
    __test_figure_set_action(scorpion, ACTION_25_SCORPION_LOOKING_FOR_ATTACK)

    var prey_ok = false
    for (var i = 0; i < 120; i++) {
        test_figure_set_speed(ostrich, 0)
        test_figure_set_speed(enemy, 0)
        test_figure_set_speed(scorpion, 0)
        __test_pump_frames(1)

        if (!__figure_is_valid(scorpion) || !__figure_is_valid(ostrich) || !__figure_is_valid(enemy)) {
            break
        }
        var target = __figure_get_target_figure_id(scorpion)
        if (target == ostrich) {
            __log_info_native('[test:549] raid scorpion targeted ostrich (wildlife leak)')
            __test_signal_ready()
            return
        }
        if (target == enemy) {
            prey_ok = true
            break
        }
    }
    if (!prey_ok) {
        __log_info_native('[test:549] raid scorpion never targeted enemy')
        __test_signal_ready()
        return
    }
    __log_marker('ptah_scorpion_raid_prey_ok')
    __test549_prey_ok = true

    // --- Duration: days=1 → first update_day poofs ---
    test549_remove_scorpions()
    var timer_scorpion = test_figure_create(FIGURE_SCORPION, land.x + 2, land.y)
    if (!timer_scorpion || !__test_scorpion_setup_curse_raid(timer_scorpion, 1)) {
        __log_info_native('[test:549] timer scorpion setup failed')
        __test_signal_ready()
        return
    }
    __test_figure_update_day(timer_scorpion)
    if (test549_count_scorpions() != 0) {
        __log_info_native('[test:549] expected 0 scorpions after timer poof, got ' + test549_count_scorpions())
        __test_signal_ready()
        return
    }
    __log_marker('ptah_scorpion_raid_timer_poof_ok')
    __test549_timer_ok = true

    __test_signal_ready()
}

function check_valid() {
    if (!__test549_on_ok || !__test549_off_ok || !__test549_fallback_ok || !__test549_prey_ok || !__test549_timer_ok) {
        __log_info_native('[test:549] one or more phases failed')
        return false
    }

    var markers = [
        'ptah_scorpion_feature_on_spawn_ok',
        'ptah_scorpion_feature_off_no_spawn_ok',
        'ptah_scorpion_no_temple_fallback_ok',
        'ptah_scorpion_raid_prey_ok',
        'ptah_scorpion_raid_timer_poof_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:549] missing marker: ' + marker)
            return false
        }
    }
    return true
}

function done() {
    game_features.set('gameplay_ptah_scorpion_raid', __test549_feat_prev)
    test549_remove_scorpions()
}
