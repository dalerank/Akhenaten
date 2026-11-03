// FIG_BARBARIAN / FIGURE_INDIGENOUS_NATIVE: OG action ids 8..11, hut spawn every 5 days,
// drown on flooded floodplain, die when the hut no longer owns the walker.
// Markers:
//   [test-marker] native_params_ok
//   [test-marker] native_spawn_ok
//   [test-marker] native_action_ids_ok
//   [test-marker] native_drown_ok
//   [test-marker] native_home_poof_ok

var ACTION_8_NATIVE_GOING_TO_MEETING = 8
var ACTION_10_NATIVE_CREATED = 10

var __test236_ok = false

function test236_fail(msg) {
    __log_info_native('[test:236] ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:236] indigenous native OG')

    if (__test_figure_type_max_roam(FIGURE_INDIGENOUS_NATIVE) != 800) {
        return test236_fail('max_roam want 800 got ' + __test_figure_type_max_roam(FIGURE_INDIGENOUS_NATIVE))
    }
    // figure_category_native = 5
    if (__test_figure_type_category(FIGURE_INDIGENOUS_NATIVE) != 5) {
        return test236_fail('category want native(5) got ' + __test_figure_type_category(FIGURE_INDIGENOUS_NATIVE))
    }
    __log_marker('native_params_ok')

    test_reload_city_session('data/default.map')
    city.figures.remove_figures(FIGURE_INDIGENOUS_NATIVE)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var meeting = __test_building_create(BUILDING_UNUSED_NATIVE_MEETING_89, cx + 6, cy)
    var hut = __test_building_create(BUILDING_UNUSED_NATIVE_HUT_88, cx, cy)
    if (!hut || !meeting) {
        return test236_fail('create failed hut=' + hut + ' meeting=' + meeting)
    }
    __test_building_set_native_meeting(hut, meeting)
    city.get_building(hut).figure_spawn_delay = 4

    var before = __test_count_figures(FIGURE_INDIGENOUS_NATIVE)
    __test_buildings_generate_figures()
    var after = __test_count_figures(FIGURE_INDIGENOUS_NATIVE)
    if (after != before + 1) {
        return test236_fail('spawn want +1 got ' + before + ' -> ' + after)
    }
    __log_marker('native_spawn_ok')

    var fid = 0
    for (var i = 1; i < 2000; i++) {
        if (__figure_is_valid(i) && __figure_get_type(i) == FIGURE_INDIGENOUS_NATIVE && __test_figure_is_alive(i) == 1) {
            fid = i
            break
        }
    }
    if (!fid) {
        return test236_fail('no native figure after spawn')
    }
    if (__test_figure_get_action(fid) != ACTION_10_NATIVE_CREATED) {
        return test236_fail('created action want 10 got ' + __test_figure_get_action(fid))
    }

    // Advance past wait so the native walks to the meeting (action 8).
    for (var t = 0; t < 20; t++) {
        __test_figure_action_perform(fid)
        if (__test_figure_get_action(fid) == ACTION_8_NATIVE_GOING_TO_MEETING) {
            break
        }
    }
    if (__test_figure_get_action(fid) != ACTION_8_NATIVE_GOING_TO_MEETING) {
        return test236_fail('after wait want action 8 got ' + __test_figure_get_action(fid))
    }
    __log_marker('native_action_ids_ok')

    city.figures.remove_figures(FIGURE_INDIGENOUS_NATIVE)
    var drown = test_figure_create(FIGURE_INDIGENOUS_NATIVE, cx + 2, cy + 2)
    if (!drown) {
        return test236_fail('drown create failed')
    }
    var dt = __figure_get_tile(drown)
    __test_make_floodplain_water(dt.x, dt.y)
    __test_figure_action_perform(drown)
    if (__test_figure_is_alive(drown) == 1) {
        return test236_fail('should drown on flooded floodplain')
    }
    __log_marker('native_drown_ok')

    city.figures.remove_figures(FIGURE_INDIGENOUS_NATIVE)
    var orphan = test_figure_create(FIGURE_INDIGENOUS_NATIVE, cx, cy)
    if (!orphan) {
        return test236_fail('orphan create failed')
    }
    __test_figure_set_home(orphan, hut)
    // Hut does not name this walker — OG poofs when figure_id mismatches.
    __test_figure_action_perform(orphan)
    if (__test_figure_is_alive(orphan) == 1) {
        return test236_fail('should poof when hut does not own walker')
    }
    __log_marker('native_home_poof_ok')

    __test236_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test236_ok
        && __test_find_inlog('[test-marker] native_params_ok')
        && __test_find_inlog('[test-marker] native_spawn_ok')
        && __test_find_inlog('[test-marker] native_action_ids_ok')
        && __test_find_inlog('[test-marker] native_drown_ok')
        && __test_find_inlog('[test-marker] native_home_poof_ok')
}
