// Fishing spots vs OG: scenario_start.c:144 creates them once and they live on; respawning them every month
// (fresh figures, fresh crt/LFSR draws) is the Enhanced gameplay_change_fishing_points_monthly_respawn.
// A respawned spot may get the same figure id back, so each spot is ticked forward first: a kept spot keeps
// its animation state, a respawned one starts over.
// Markers:
//   [test-marker] fishing_points_kept_og_ok
//   [test-marker] fishing_points_respawn_enhanced_ok

var __test312_feat_prev = false

function test312_fail(msg) {
    __log_info_native('[test:312] FAIL: ' + msg)
}

// "id:state" of every live fishing spot.
function test312_spot_ids() {
    var ids = []
    for (var i = 1; i < 2000; i++) {
        if (__figure_is_valid(i) && __figure_get_type(i) == FIGURE_FISHING_POINT && __test_figure_is_alive(i) == 1) {
            ids.push(i + ':' + __test_fishing_spot_state(i))
        }
    }
    return ids.join(',')
}

function test312_tick_spots(n) {
    for (var i = 1; i < 2000; i++) {
        if (__figure_is_valid(i) && __figure_get_type(i) == FIGURE_FISHING_POINT && __test_figure_is_alive(i) == 1) {
            for (var t = 0; t < n; t++) {
                __test_fishing_spot_og_tick(i)
            }
        }
    }
}

function test312_setup() {
    test_reload_city_session('data/default.map')
    __city_resource_set_produce(RESOURCE_FISH, true)
    city.figures.remove_figures(FIGURE_SEAGULLS)
    city.figures.remove_figures(FIGURE_FISHING_POINT)
    __test_clear_scenario_fishing_points()
    __test_set_scenario_fishing_point(0, 12, 14)
    __test_set_scenario_fishing_point(1, 20, 22)
    __test_fishing_points_create()
    test312_tick_spots(5)
    return test312_spot_ids()
}

function run_test() {
    __log_info_native('[test:312] fishing points monthly')
    __test312_feat_prev = !!game_features.gameplay_change_fishing_points_monthly_respawn

    game_features.gameplay_change_fishing_points_monthly_respawn = false
    var before = test312_setup()
    __test_city_update_month()
    var after = test312_spot_ids()
    if (before === '') {
        test312_fail('no fishing spots created')
    } else if (after !== before) {
        test312_fail('OG: spots changed over a month ' + before + ' -> ' + after)
    } else {
        __log_marker('fishing_points_kept_og_ok')
    }

    game_features.gameplay_change_fishing_points_monthly_respawn = true
    before = test312_setup()
    __test_city_update_month()
    after = test312_spot_ids()
    if (after === '' || after === before) {
        test312_fail('Enhanced: spots not respawned ' + before + ' -> ' + after)
    } else {
        __log_marker('fishing_points_respawn_enhanced_ok')
    }

    game_features.gameplay_change_fishing_points_monthly_respawn = __test312_feat_prev
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('fishing_points_kept_og_ok') && __test_find_inlog('fishing_points_respawn_enhanced_ok')
}
