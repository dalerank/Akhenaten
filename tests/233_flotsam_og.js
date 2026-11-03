// FIGURE_FLOTSAM: OG kinds/frames/sprites (figure_flotsam_action 0x00494B30), spawned on demand at the river
// entry and removed at the exit instead of OG's 20 figures parked there.
// Markers:
//   [test-marker] flotsam_disabled_ok      no spawn while the scenario has flotsam off
//   [test-marker] flotsam_spawn_ok         spawned at the river entry, floating (9) and visible
//   [test-marker] flotsam_image_ok | flotsam_image_skipped
//   [test-marker] flotsam_feature_off_ok   daily spawn does nothing without gameplay_city_flotsam_enabled
//   [test-marker] flotsam_daily_cap_ok     daily spawn adds flotsam, stops exactly at figure_flotsam.max_alive, OG kinds only
//   [test-marker] flotsam_arrival_ok       reaching the exit removes the figure
//   [test-marker] flotsam_og_wait_ok       an OG-save waiting flotsam (8) floats after its wait
//   [test-marker] flotsam_unknown_action_ok an unknown action (old 128) removes it

var ACTION_FLOTSAM_CREATED = 8
var ACTION_FLOTSAM_FLOATING = 9
var FLOTSAM_MAX_ALIVE = figure_flotsam.max_alive

var __test233_ok = false

function test233_flotsam_ids() {
    var ids = []
    for (var i = 1; i < 2000; i++) {
        if (__figure_is_valid(i) && __figure_get_type(i) == FIGURE_FLOTSAM && __test_figure_is_alive(i) == 1) {
            ids.push(i)
        }
    }
    return ids
}

function test233_fail(msg) {
    __log_info_native('[test:233] ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:233] flotsam')
    test_reload_city_session('data/default.map')
    city.figures.remove_figures(FIGURE_FLOTSAM)

    var prev_feature = game_features.gameplay_city_flotsam_enabled
    var prev_enabled = scenario.flotsam_enabled
    game_features.gameplay_city_flotsam_enabled = false

    var probe = test_figure_create(FIGURE_FLOTSAM, -1, -1)
    if (!probe) {
        return test233_fail('probe create failed')
    }
    var tile = __figure_get_tile(probe)
    city.figures.remove_figures(FIGURE_FLOTSAM)
    __test_make_deep_water(tile.x, tile.y)
    __test_set_scenario_river_points(tile.x, tile.y, tile.x, tile.y)

    scenario.flotsam_enabled = false
    if (__test_flotsam_spawn(0) != 0 || test233_flotsam_ids().length != 0) {
        return test233_fail('spawned while the scenario has flotsam off')
    }
    __log_marker('flotsam_disabled_ok')

    scenario.flotsam_enabled = true
    var f = __test_flotsam_spawn(0)
    var at = f ? __figure_get_tile(f) : null
    if (!f || __test_figure_get_action(f) != ACTION_FLOTSAM_FLOATING || __test_figure_is_visible(f) != 1
        || __figure_get_resource(f) != 0 || at.x != tile.x || at.y != tile.y) {
        return test233_fail('spawn want floating+visible kind 0 at entry, fid=' + f
            + (f ? ' action=' + __test_figure_get_action(f) + ' visible=' + __test_figure_is_visible(f)
                + ' kind=' + __figure_get_resource(f) : ''))
    }
    __log_marker('flotsam_spawn_ok')

    __test_figure_action_perform(f)
    var first = city.get_figure(f).params.first_img('walk')
    if (first > 0) {
        var img = __test_figure_main_image_id(f)
        if (img < first || img > first + 4) {
            return test233_fail('bobbing image ' + img + ' outside ' + first + '..' + (first + 4))
        }
        __log_marker('flotsam_image_ok')
    } else {
        __log_marker('flotsam_image_skipped')
    }
    city.figures.remove_figures(FIGURE_FLOTSAM)

    for (var d = 0; d < 200; d++) {
        __test_flotsam_spawn_update_day()
    }
    if (test233_flotsam_ids().length != 0) {
        return test233_fail('daily spawn ran with the feature off')
    }
    __log_marker('flotsam_feature_off_ok')

    game_features.gameplay_city_flotsam_enabled = true
    for (var d2 = 0; d2 < 400; d2++) {
        __test_flotsam_spawn_update_day()
    }
    game_features.gameplay_city_flotsam_enabled = false
    var ids = test233_flotsam_ids()
    if (!(FLOTSAM_MAX_ALIVE > 0) || ids.length != FLOTSAM_MAX_ALIVE) {
        return test233_fail('daily spawn want max_alive=' + FLOTSAM_MAX_ALIVE + ' flotsam, got ' + ids.length)
    }
    for (var i = 0; i < ids.length; i++) {
        var kind = __figure_get_resource(ids[i])
        if (kind < 0 || kind > 3) {
            return test233_fail('flotsam ' + ids[i] + ' bad kind ' + kind)
        }
    }
    __log_marker('flotsam_daily_cap_ok')
    city.figures.remove_figures(FIGURE_FLOTSAM)

    var g = __test_flotsam_spawn(1)
    for (var t = 0; t < 80 && __test_figure_is_alive(g) == 1; t++) {
        __test_figure_action_perform(g)
    }
    if (__test_figure_is_alive(g) == 1) {
        return test233_fail('flotsam at the exit not removed, action=' + __test_figure_get_action(g))
    }
    __log_marker('flotsam_arrival_ok')

    var w = __test_flotsam_spawn(2)
    __test_figure_set_action(w, ACTION_FLOTSAM_CREATED)
    __test_figure_set_wait_ticks(w, 3)
    __test_figure_action_perform(w)
    if (__test_figure_get_action(w) != ACTION_FLOTSAM_CREATED || __test_figure_is_visible(w) != 0) {
        return test233_fail('waiting flotsam want 8+hidden, action=' + __test_figure_get_action(w)
            + ' visible=' + __test_figure_is_visible(w))
    }
    __test_figure_action_perform(w)
    __test_figure_action_perform(w)
    if (__test_figure_get_action(w) != ACTION_FLOTSAM_FLOATING || __test_figure_is_visible(w) != 1) {
        return test233_fail('after wait want floating+visible, action=' + __test_figure_get_action(w)
            + ' visible=' + __test_figure_is_visible(w))
    }
    __log_marker('flotsam_og_wait_ok')

    __test_figure_set_action(w, 128)
    __test_figure_action_perform(w)
    if (__test_figure_is_alive(w) == 1) {
        return test233_fail('unknown action want removal, action=' + __test_figure_get_action(w))
    }
    __log_marker('flotsam_unknown_action_ok')

    city.figures.remove_figures(FIGURE_FLOTSAM)
    scenario.flotsam_enabled = prev_enabled
    game_features.gameplay_city_flotsam_enabled = prev_feature
    __test233_ok = true
    __test_signal_ready()
}

function check_valid() {
    if (!__test233_ok) {
        return false
    }
    var markers = [
        'flotsam_disabled_ok',
        'flotsam_spawn_ok',
        'flotsam_feature_off_ok',
        'flotsam_daily_cap_ok',
        'flotsam_arrival_ok',
        'flotsam_og_wait_ok',
        'flotsam_unknown_action_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:233] missing marker: ' + markers[i])
            return false
        }
    }
    return __test_find_inlog('[test-marker] flotsam_image_ok') || __test_find_inlog('[test-marker] flotsam_image_skipped')
}
