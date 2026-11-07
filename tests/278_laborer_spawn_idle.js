// OG work-camp spawn: laborers start IDLE (8), capped by max_out.

function test278_fail(msg) {
    __log_info_native('[test:278] ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:278] laborer spawn IDLE + max_out')
    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_WORK_CAMP)) {
        __scenario_building_allow(BUILDING_WORK_CAMP, true)
    }

    __test_set_treasury(500000)
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var camp = test_building_place(BUILDING_WORK_CAMP, cx, cy)
    if (!camp) {
        camp = test_building_place(BUILDING_WORK_CAMP, -1, -1)
    }
    if (!camp) {
        return test278_fail('place work camp failed')
    }

    var tile = __building_tile(camp)
    __test_make_road(tile.x + 1, tile.y)
    __test_building_set_road_access(camp, tile.x + 1, tile.y)
    __test_building_set_workers(camp, 20)
    city.get_building(camp).spawned_worker_this_month = 0

    var before = __test_count_figures(FIGURE_LABORER) | 0
    var spawned = 0
    for (var i = 0; i < 40; i++) {
        var fid = __work_camp_spawn_laborer_og(camp) | 0
        if (fid > 0) {
            spawned++
            var act = __test_figure_get_action(fid) | 0
            if (act != 8) {
                return test278_fail('spawned laborer want IDLE(8) got ' + act)
            }
            city.get_building(camp).spawned_worker_this_month = 0
        }
    }

    var after = __test_count_figures(FIGURE_LABORER) | 0
    var delta = after - before
    if (spawned < 1) {
        return test278_fail('expected at least one spawn')
    }
    if (delta > 4) {
        return test278_fail('max_out exceeded: spawned delta=' + delta)
    }
    __log_marker('laborer_spawn_idle_ok:' + spawned)
    __log_marker('laborer_spawn_max_out_ok:' + delta)
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] laborer_spawn_idle_ok:')
        && __test_find_inlog('[test-marker] laborer_spawn_max_out_ok:')
}
