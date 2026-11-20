// Courthouse OG spawn (building_figure.c spawn_service_walker for FIGURE_MAGISTRATE): nothing while a magistrate
// is out or without road, then the labor seeker below 101 houses, delays_fast {0,1,3,7,15} by worker %, and the
// magistrate leaves as FIGURE_ACTION_SERVICE_CREATED (ACTION_70).

var __test442_ok = false
var __test442_boost_prev = false

function test442_finish() {
    game_features.set('gameplay_enhanced_walker_spawn_boost', __test442_boost_prev)
    __test_signal_ready()
}

function test442_fail(msg) {
    __log_info_native('[test:442] FAIL: ' + msg)
    test442_finish()
}

function test442_clear() {
    city.figures.remove_figures(FIGURE_MAGISTRATE)
    city.figures.remove_figures(FIGURE_LABOR_SEEKER)
    __test_figures_update()
}

function test442_days_to_spawn(bid, workers) {
    test442_clear()
    __test_building_set_workers(bid, workers)
    city.get_building(bid).figure_spawn_delay = 0
    for (var day = 1; day <= 40; day++) {
        __test_building_spawn_figure(bid)
        if (__test_count_figures(FIGURE_MAGISTRATE) > 0) {
            return day
        }
    }
    return -1
}

function test442_seeker_spawns(bid, houses) {
    test442_clear()
    __test_building_set_workers(bid, 0)
    __test_building_set_houses_covered(bid, houses)
    __test_building_spawn_figure(bid)
    return __test_count_figures(FIGURE_LABOR_SEEKER) > 0
}

function run_test() {
    __log_info_native('[test:442] magistrate spawn OG')
    __test442_boost_prev = game_features.get('gameplay_enhanced_walker_spawn_boost') === true
    game_features.set('gameplay_enhanced_walker_spawn_boost', false)

    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)
    __test_set_city_population(500)

    var bid = test_building_place(BUILDING_COURTHOUSE, -1, -1)
    if (!bid) {
        test442_fail('courthouse place failed')
        return
    }
    var bt = __building_tile(bid)
    for (var dx = -1; dx < 5; dx++) {
        terrain.add({ x: bt.x + dx, y: bt.y + 3 }, TERRAIN_ROAD)
    }
    __test_update_road_network()
    __test_building_set_road_access(bid, bt.x, bt.y + 3)

    // laborers 10: 10 = 100%, 8 = 80%, 5 = 50%, 3 = 30%, 1 = 10% -> delays 0, 1, 3, 7, 15.
    var cases = [[10, 1], [8, 2], [5, 4], [3, 8], [1, 16]]
    for (var i = 0; i < cases.length; i++) {
        var got = test442_days_to_spawn(bid, cases[i][0])
        if (got != cases[i][1]) {
            test442_fail('workers ' + cases[i][0] + ': magistrate expected on day ' + cases[i][1] + ', got ' + got)
            return
        }
    }
    __log_marker('test442_delays')

    if (!test442_seeker_spawns(bid, 100)) {
        test442_fail('labor seeker expected at 100 houses (OG limit 101)')
        return
    }
    if (test442_seeker_spawns(bid, 101)) {
        test442_fail('no labor seeker from 101 houses')
        return
    }
    if (__test_count_figures(FIGURE_MAGISTRATE) != 0) {
        test442_fail('no magistrate without workers')
        return
    }
    __log_marker('test442_labor')

    if (test442_days_to_spawn(bid, 10) != 1) {
        test442_fail('magistrate expected at full staff')
        return
    }
    var fid = __test_building_figure_id(bid, 0)
    if (!fid || __figure_get_type(fid) != FIGURE_MAGISTRATE) {
        test442_fail('magistrate must sit in the service slot')
        return
    }
    if (__figure_get_action_state(fid) != 70) {
        test442_fail('magistrate must start in ACTION_70 (OG service created), got ' + __figure_get_action_state(fid))
        return
    }
    __test_building_set_houses_covered(bid, 0)
    for (var w = 0; w < 10; w++) {
        __test_building_spawn_figure(bid)
    }
    if (__test_count_figures(FIGURE_MAGISTRATE) != 1) {
        test442_fail('one magistrate at a time, got ' + __test_count_figures(FIGURE_MAGISTRATE))
        return
    }
    if (__test_count_figures(FIGURE_LABOR_SEEKER) != 0) {
        test442_fail('OG checks the walker before the labor seeker')
        return
    }
    __log_marker('test442_one_walker')

    __test442_ok = true
    test442_finish()
}

function check_valid() {
    return __test442_ok
        && __test_find_inlog('[test-marker] test442_delays')
        && __test_find_inlog('[test-marker] test442_labor')
        && __test_find_inlog('[test-marker] test442_one_walker')
}
