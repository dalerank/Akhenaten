// Police station OG spawn (building_figure.c spawn_service_walker): delays_fast {0,1,3,7,15} by worker %,
// labor seeker limit 101 houses (min_houses_coverage 100), no weapons step, the constable leaves as
// FIGURE_ACTION_SERVICE_CREATED (ACTION_70) and no second one while the first is out.

var __test590_ok = false
var __test590_boost_prev = false

function test590_finish() {
    game_features.set('gameplay_enhanced_walker_spawn_boost', __test590_boost_prev)
    __test_signal_ready()
}

function test590_fail(msg) {
    __log_info_native('[test:590] FAIL: ' + msg)
    test590_finish()
}

function test590_days_to_spawn(bid, workers) {
    city.figures.remove_figures(FIGURE_CONSTABLE)
    __test_figures_update()
    __test_building_set_workers(bid, workers)
    city.get_building(bid).figure_spawn_delay = 0
    for (var day = 1; day <= 40; day++) {
        __test_building_spawn_figure(bid)
        if (__test_count_figures(FIGURE_CONSTABLE) > 0) {
            return day
        }
    }
    return -1
}

function run_test() {
    __log_info_native('[test:590] constable spawn OG')
    __test590_boost_prev = game_features.get('gameplay_enhanced_walker_spawn_boost') === true
    game_features.set('gameplay_enhanced_walker_spawn_boost', false)

    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)

    if (building_police_station.min_houses_coverage != 100) {
        test590_fail('min_houses_coverage expected 100 (OG labor limit 101), got ' + building_police_station.min_houses_coverage)
        return
    }

    var bid = test_building_place(BUILDING_POLICE_STATION, -1, -1)
    if (!bid) {
        test590_fail('police station place failed')
        return
    }
    var bt = __building_tile(bid)
    for (var dx = -1; dx < 3; dx++) {
        terrain.add({ x: bt.x + dx, y: bt.y + 1 }, TERRAIN_ROAD)
    }
    __test_update_road_network()
    __test_building_set_road_access(bid, bt.x, bt.y + 1)

    // laborers 6: 6 = 100%, 5 = 83%, 3 = 50%, 2 = 33%, 1 = 16% -> delays 0, 1, 3, 7, 15.
    var cases = [[6, 1], [5, 2], [3, 4], [2, 8], [1, 16]]
    for (var i = 0; i < cases.length; i++) {
        var got = test590_days_to_spawn(bid, cases[i][0])
        if (got != cases[i][1]) {
            test590_fail('workers ' + cases[i][0] + ': constable expected on day ' + cases[i][1] + ', got ' + got)
            return
        }
    }
    __log_marker('test590_delays')

    city.figures.remove_figures(FIGURE_CONSTABLE)
    __test_figures_update()
    __test_building_set_workers(bid, 0)
    city.get_building(bid).figure_spawn_delay = 0
    for (var d = 0; d < 20; d++) {
        __test_building_spawn_figure(bid)
    }
    if (__test_count_figures(FIGURE_CONSTABLE) != 0) {
        test590_fail('no constable without workers')
        return
    }
    __log_marker('test590_no_staff')

    if (test590_days_to_spawn(bid, 6) != 1) {
        test590_fail('constable expected at full staff')
        return
    }
    var fid = __test_building_figure_id(bid, 0)
    if (!fid || __figure_get_type(fid) != FIGURE_CONSTABLE) {
        test590_fail('constable must sit in the service slot')
        return
    }
    if (__figure_get_action_state(fid) != 70) {
        test590_fail('constable must start in ACTION_70 (OG service created), got ' + __figure_get_action_state(fid))
        return
    }
    if (city.get_building(bid).stored_resource(RESOURCE_WEAPONS) != 0) {
        test590_fail('police station must not use weapons')
        return
    }
    for (var w = 0; w < 10; w++) {
        __test_building_spawn_figure(bid)
    }
    if (__test_count_figures(FIGURE_CONSTABLE) != 1) {
        test590_fail('one constable at a time, got ' + __test_count_figures(FIGURE_CONSTABLE))
        return
    }
    __log_marker('test590_one_walker')

    __test590_ok = true
    test590_finish()
}

function check_valid() {
    return __test590_ok
        && __test_find_inlog('[test-marker] test590_delays')
        && __test_find_inlog('[test-marker] test590_no_staff')
        && __test_find_inlog('[test-marker] test590_one_walker')
}
