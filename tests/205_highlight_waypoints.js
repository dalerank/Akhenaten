// Water-building extra waypoint highlights (dock tiles / water-lift in-out) live in JS.
// Markers:
//   [test-marker] highlight_water_lift_ok
//   [test-marker] highlight_dock_ok

var __test205_feat_prev = false
var __test205_ok = false

function run_test() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __test205_feat_prev = game_features.get('gameui_walker_waypoints') === true
    game_features.set('gameui_walker_waypoints', true)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    test_prepare_shoreline_patch(cx, cy, 4, 2)

    __scenario_building_allow(BUILDING_WATER_LIFT, true)
    var lift_id = test_building_place(BUILDING_WATER_LIFT, cx - 1, cy - 1)
    if (!lift_id) {
        __log_info_native('[test:205] water lift place failed')
        game_features.set('gameui_walker_waypoints', __test205_feat_prev)
        __test_signal_ready()
        return
    }

    __test_building_update_day(lift_id)
    var lift = city.get_building(lift_id)
    lift.highlight_waypoints()

    var in0 = lift.water_access_tile(0)
    var in1 = lift.water_access_tile(1)
    var out0 = lift.water_output_tile(0)
    var out1 = lift.water_output_tile(1)
    if (__map_is_highlighted(in0) != HIGHLIGHT_GREEN || __map_is_highlighted(in1) != HIGHLIGHT_GREEN) {
        __log_info_native('[test:205] water lift input tiles not green')
        game_features.set('gameui_walker_waypoints', __test205_feat_prev)
        __test_signal_ready()
        return
    }
    if (__map_is_highlighted(out0) != HIGHLIGHT_YELLOW || __map_is_highlighted(out1) != HIGHLIGHT_YELLOW) {
        __log_info_native('[test:205] water lift output tiles not yellow')
        game_features.set('gameui_walker_waypoints', __test205_feat_prev)
        __test_signal_ready()
        return
    }
    __log_marker('highlight_water_lift_ok')

    __scenario_building_allow(BUILDING_DOCK, true)
    var dock_id = __test_building_create(BUILDING_DOCK, cx + 8, cy - 1)
    if (!dock_id) {
        __log_info_native('[test:205] dock create failed')
        game_features.set('gameui_walker_waypoints', __test205_feat_prev)
        __test_signal_ready()
        return
    }

    var dock = city.get_building(dock_id)
    dock.highlight_waypoints()
    var a = dock.water_access_tile(0)
    var b = dock.water_access_tile(1)
    if (a.x >= 0 && __map_is_highlighted(a) != HIGHLIGHT_GREEN) {
        __log_info_native('[test:205] dock tile a not green at ' + a.x + ',' + a.y)
        game_features.set('gameui_walker_waypoints', __test205_feat_prev)
        __test_signal_ready()
        return
    }
    if (b.x >= 0 && __map_is_highlighted(b) != HIGHLIGHT_GREEN) {
        __log_info_native('[test:205] dock tile b not green at ' + b.x + ',' + b.y)
        game_features.set('gameui_walker_waypoints', __test205_feat_prev)
        __test_signal_ready()
        return
    }
    __log_marker('highlight_dock_ok')

    __test205_ok = true
    game_features.set('gameui_walker_waypoints', __test205_feat_prev)
    __test_signal_ready()
}

function check_valid() {
    game_features.set('gameui_walker_waypoints', __test205_feat_prev)
    if (!__test_find_inlog('[test-marker] highlight_water_lift_ok')) {
        __log_info_native('[test:205] missing highlight_water_lift_ok')
        return false
    }
    if (!__test_find_inlog('[test-marker] highlight_dock_ok')) {
        __log_info_native('[test:205] missing highlight_dock_ok')
        return false
    }
    return __test205_ok
}
