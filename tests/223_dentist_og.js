// Dentist OG: spawn_service_walker with delays_service {3,7,15,29,44} by worker %,
// coverage gives 96 to every inhabited house in radius 2 (no monthly cap, no half-coverage gate).
// gameplay_change_dentist_service_cap restores the remake cap; toothache flag defaults off.

var __test223_ok = false
var __test223_cap_prev = false

function test223_finish() {
    game_features.set('gameplay_change_dentist_service_cap', __test223_cap_prev)
    __test_signal_ready()
}

function test223_fail(msg) {
    __log_info_native('[test:223] FAIL: ' + msg)
    test223_finish()
}

function test223_spawn(bid) {
    building_dentist_spawn_figure({ bid: bid })
    return __test_count_figures(FIGURE_DENTIST)
}

function test223_check_spawn_delay() {
    var bid = test_building_place(BUILDING_DENTIST, -1, -1)
    if (!bid) {
        test223_fail('place failed')
        return 0
    }

    var zt = __building_tile(bid)
    for (var dx = 0; dx < 3; dx++) {
        terrain.add({ x: zt.x + dx, y: zt.y + 1 }, TERRAIN_ROAD)
    }
    __test_update_road_network()
    __test_check_kingdome_access()

    __test_building_set_workers(bid, 2)
    var b = city.get_building(bid)
    b.has_road_access = true
    b.figure_spawn_delay = 0
    city.figures.remove_figures(FIGURE_DENTIST)

    for (var d = 1; d <= 3; d++) {
        if (test223_spawn(bid) > 0) {
            test223_fail('dentist spawned too early at day ' + d)
            return 0
        }
    }
    if (test223_spawn(bid) < 1) {
        test223_fail('dentist expected on day 4 at 100% workers')
        return 0
    }
    if (city.get_building(bid).figure_spawn_delay != 0) {
        test223_fail('day counter must reset after spawn')
        return 0
    }
    __log_marker('test223_delay_100pct')
    return bid
}

function run_test() {
    __log_info_native('[test:223] dentist OG')
    __test223_cap_prev = game_features.get('gameplay_change_dentist_service_cap') === true
    if (game_features.default('gameplay_change_dentist_service_cap') || game_features.default('gameplay_change_dentist_toothache')) {
        test223_fail('dentist remake flags must default OFF')
        return
    }
    game_features.set('gameplay_change_dentist_service_cap', false)

    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)

    var dentist_id = test223_check_spawn_delay()
    if (!dentist_id) {
        return
    }

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var lived_id = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, cx, cy)
    var empty_id = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, cx + 1, cy)
    if (!lived_id || !empty_id) {
        test223_fail('house create failed')
        return
    }
    if (__test_house_set_population(lived_id, 10) < 1) {
        test223_fail('set population failed')
        return
    }

    var fid = test_figure_create(FIGURE_DENTIST, cx, cy + 1)
    if (!fid) {
        test223_fail('dentist figure create failed')
        return
    }
    __test_figure_set_home(fid, dentist_id)

    city.get_house(lived_id).dentist = 60
    var served = __test_figure_provide_service(fid)
    if (city.get_house(lived_id).dentist != 96) {
        test223_fail('OG must refresh inhabited house to 96, got ' + city.get_house(lived_id).dentist)
        return
    }
    if (city.get_house(empty_id).dentist != 0) {
        test223_fail('OG must skip empty house, got ' + city.get_house(empty_id).dentist)
        return
    }
    if (served != 1) {
        test223_fail('OG must count inhabited house tiles only, got ' + served)
        return
    }
    __log_marker('test223_og_coverage')

    game_features.set('gameplay_change_dentist_service_cap', true)
    city.get_house(lived_id).dentist = 60
    __test_figure_provide_service(fid)
    if (city.get_house(lived_id).dentist != 60) {
        test223_fail('remake must skip houses above half coverage, got ' + city.get_house(lived_id).dentist)
        return
    }
    __log_marker('test223_remake_cap')

    __test223_ok = true
    test223_finish()
}

function check_valid() {
    return __test223_ok
        && __test_find_inlog('[test-marker] test223_delay_100pct')
        && __test_find_inlog('[test-marker] test223_og_coverage')
        && __test_find_inlog('[test-marker] test223_remake_cap')
}
