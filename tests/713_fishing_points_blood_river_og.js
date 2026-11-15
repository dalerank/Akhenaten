// Fishing spots vs OG city_disasters.c city_blood_river_start / tick.c update_map_sweep: the spots stay alive
// through the blood river, they only leave the figure grid until the sweep ends (map_figure_delete / add).
// OG spots also stand still; drifting around the point is the Enhanced gameplay_change_fishing_points_drift.
// Markers:
//   [test-marker] fishing_points_blood_river_og_ok
//   [test-marker] fishing_points_still_og_ok
//   [test-marker] fishing_points_drift_enhanced_ok

var __test713_drift_prev = false

function test713_fail(msg) {
    __log_info_native('[test:713] FAIL: ' + msg)
}

function test713_spots() {
    var ids = []
    for (var i = 1; i < 2000; i++) {
        if (__figure_is_valid(i) && __figure_get_type(i) == FIGURE_FISHING_POINT && __test_figure_is_alive(i) == 1) {
            ids.push(i)
        }
    }
    return ids
}

function test713_setup() {
    test_reload_city_session('data/default.map')
    city.figures.remove_figures(FIGURE_SEAGULLS)
    city.figures.remove_figures(FIGURE_FISHING_POINT)
    __test_clear_scenario_fishing_points()
    __test_set_scenario_fishing_point(0, 12, 14)
    __test_set_scenario_fishing_point(1, 20, 22)
    __test_fishing_points_create()
    return test713_spots()
}

function test713_on_grid(ids) {
    var n = 0
    for (var i = 0; i < ids.length; i++) {
        n += __test_figure_on_map_grid(ids[i])
    }
    return n
}

function test713_blood_river() {
    var ids = test713_setup()
    if (ids.length != 2 || test713_on_grid(ids) != 2) {
        test713_fail('setup: spots=' + ids.join(',') + ' on grid=' + test713_on_grid(ids))
        return
    }

    var ev = city.create_chain_event({ tag_id: 7131, type: EVENT_TYPE_BLOOD_RIVER, amount: 1, trigger: EVENT_TRIGGER_ONCE })
    ev.execute()
    var during = test713_spots()
    if (during.join(',') !== ids.join(',') || test713_on_grid(ids) != 0) {
        test713_fail('sweep start: spots ' + ids.join(',') + ' -> ' + during.join(',') + ' on grid=' + test713_on_grid(ids))
        return
    }

    __test_scenario_events_tick(3 * 816)
    var after = test713_spots()
    if (__test_blood_river_sweep_active() || after.join(',') !== ids.join(',') || test713_on_grid(ids) != 2) {
        test713_fail('sweep end: spots ' + ids.join(',') + ' -> ' + after.join(',') + ' on grid=' + test713_on_grid(ids)
            + ' active=' + __test_blood_river_sweep_active())
        return
    }
    __log_marker('fishing_points_blood_river_og_ok')
}

// Deep-water pool around the first spot, with one land tile on its (0,-2) drift offset.
var TEST713_POOL = { x: 12, y: 14, r: 8 }
var TEST713_LAND = { x: 12, y: 12 }

function test713_pool_setup() {
    var ids = test713_setup()
    for (var y = TEST713_POOL.y - TEST713_POOL.r; y <= TEST713_POOL.y + TEST713_POOL.r; y++) {
        for (var x = TEST713_POOL.x - TEST713_POOL.r; x <= TEST713_POOL.x + TEST713_POOL.r; x++) {
            __test_make_deep_water(x, y)
        }
    }
    __map_terrain_remove(TEST713_LAND, TERRAIN_ALL)
    return ids.length > 0 ? ids[0] : 0
}

// Runs n spot actions; returns { tiles: distinct tiles, error: first broken invariant }.
function test713_run_spot(fid, n) {
    var seen = {}
    var res = { tiles: 0, error: '' }
    for (var t = 0; t < n; t++) {
        __test_figure_action_perform(fid)
        var p = __figure_get_tile(fid)
        var key = p.x + ':' + p.y
        if (!seen[key]) {
            seen[key] = true
            res.tiles++
        }
        if (!__map_terrain_is(p, TERRAIN_DEEPWATER)) {
            res.error = 'tick ' + t + ': spot on non-deep-water tile ' + key
            return res
        }
        if (!__test_blood_river_sweep_active() && __test_figure_on_map_grid(fid) != 1) {
            res.error = 'tick ' + t + ': spot not on the figure grid at ' + key
            return res
        }
    }
    return res
}

function test713_drift() {
    game_features.gameplay_change_fishing_points_drift = false
    var fid = test713_pool_setup()
    var still = test713_run_spot(fid, 600)
    if (!fid || still.error || still.tiles != 1) {
        test713_fail('OG: spot ' + fid + ' took ' + still.tiles + ' tiles ' + still.error)
    } else {
        __log_marker('fishing_points_still_og_ok')
    }

    game_features.gameplay_change_fishing_points_drift = true
    fid = test713_pool_setup()
    var drift = test713_run_spot(fid, 600)
    if (!fid || drift.error || drift.tiles < 3) {
        test713_fail('Enhanced: spot ' + fid + ' took ' + drift.tiles + ' tiles ' + drift.error)
        return
    }

    fid = test713_pool_setup()
    test713_run_spot(fid, 37)
    var before = __figure_get_tile(fid)
    var ev = city.create_chain_event({ tag_id: 7132, type: EVENT_TYPE_BLOOD_RIVER, amount: 1, trigger: EVENT_TRIGGER_ONCE })
    ev.execute()
    var sweep = test713_run_spot(fid, 600)
    var during = __figure_get_tile(fid)
    if (sweep.error || during.x != before.x || during.y != before.y || __test_figure_on_map_grid(fid) != 0) {
        test713_fail('Enhanced sweep: spot moved ' + before.x + ':' + before.y + ' -> ' + during.x + ':' + during.y
            + ' on grid=' + __test_figure_on_map_grid(fid) + ' ' + sweep.error)
        return
    }
    __test_scenario_events_tick(3 * 816)
    var after = test713_run_spot(fid, 600)
    if (__test_blood_river_sweep_active() || after.error || after.tiles < 2) {
        test713_fail('Enhanced after sweep: spot took ' + after.tiles + ' tiles ' + after.error)
        return
    }
    __log_marker('fishing_points_drift_enhanced_ok')
}

function run_test() {
    __log_info_native('[test:713] fishing points through the blood river, drift')
    __test713_drift_prev = !!game_features.gameplay_change_fishing_points_drift
    test713_blood_river()
    test713_drift()
    game_features.gameplay_change_fishing_points_drift = __test713_drift_prev
    __test_signal_ready()
}

function check_valid() {
    var markers = ['fishing_points_blood_river_og_ok', 'fishing_points_still_og_ok', 'fishing_points_drift_enhanced_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:713] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}
