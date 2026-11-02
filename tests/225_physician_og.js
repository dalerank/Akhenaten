// Physician OG: spawn_service_walker with delays_service {3,7,15,29,44} by worker %,
// coverage gives 96 to every inhabited house in radius 2, covered houses lose 25 malaria risk.
// gameplay_change_physician_service_cap restores the remake (monthly cap, half-coverage gate, no malaria cut).

var __test225_ok = false
var __test225_cap_prev = false

function test225_finish() {
    game_features.set('gameplay_change_physician_service_cap', __test225_cap_prev)
    __test_signal_ready()
}

function test225_fail(msg) {
    __log_info_native('[test:225] FAIL: ' + msg)
    test225_finish()
}

function test225_spawn(bid) {
    building_physician_spawn_figure({ bid: bid })
    return __test_count_figures(FIGURE_PHYSICIAN)
}

function test225_check_spawn_delay() {
    var bid = test_building_place(BUILDING_PHYSICIAN, -1, -1)
    if (!bid) {
        test225_fail('place failed')
        return 0
    }

    var zt = __building_tile(bid)
    for (var dx = 0; dx < 4; dx++) {
        terrain.add({ x: zt.x + dx, y: zt.y + 2 }, TERRAIN_ROAD)
    }
    __test_update_road_network()
    __test_check_kingdome_access()

    __test_building_set_workers(bid, 8)
    var b = city.get_building(bid)
    b.has_road_access = true
    b.figure_spawn_delay = 0
    city.figures.remove_figures(FIGURE_PHYSICIAN)

    for (var d = 1; d <= 3; d++) {
        if (test225_spawn(bid) > 0) {
            test225_fail('physician spawned too early at day ' + d)
            return 0
        }
    }
    if (test225_spawn(bid) < 1) {
        test225_fail('physician expected on day 4 at 100% workers')
        return 0
    }
    if (city.get_building(bid).figure_spawn_delay != 0) {
        test225_fail('day counter must reset after spawn')
        return 0
    }
    __log_marker('test225_delay_100pct')
    return bid
}

function test225_marsh_ring(cx, cy, r) {
    for (var i = -r; i <= r; i++) {
        terrain.add({ x: cx + i, y: cy - r }, TERRAIN_MARSHLAND)
        terrain.add({ x: cx + i, y: cy + r }, TERRAIN_MARSHLAND)
        terrain.add({ x: cx - r, y: cy + i }, TERRAIN_MARSHLAND)
        terrain.add({ x: cx + r, y: cy + i }, TERRAIN_MARSHLAND)
    }
}

function run_test() {
    __log_info_native('[test:225] physician OG')
    __test225_cap_prev = game_features.get('gameplay_change_physician_service_cap') === true
    if (game_features.default('gameplay_change_physician_service_cap')) {
        test225_fail('physician remake flag must default OFF')
        return
    }
    game_features.set('gameplay_change_physician_service_cap', false)

    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)

    var physician_id = test225_check_spawn_delay()
    if (!physician_id) {
        return
    }

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var lived_id = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, cx, cy)
    var empty_id = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, cx + 1, cy)
    if (!lived_id || !empty_id) {
        test225_fail('house create failed')
        return
    }
    if (__test_house_set_population(lived_id, 10) < 1) {
        test225_fail('set population failed')
        return
    }

    var fid = test_figure_create(FIGURE_PHYSICIAN, cx, cy + 1)
    if (!fid) {
        test225_fail('physician figure create failed')
        return
    }
    __test_figure_set_home(fid, physician_id)

    city.get_house(lived_id).physician = 60
    var served = __test_figure_provide_service(fid)
    if (city.get_house(lived_id).physician != 96) {
        test225_fail('OG must refresh inhabited house to 96, got ' + city.get_house(lived_id).physician)
        return
    }
    if (city.get_house(empty_id).physician != 0) {
        test225_fail('OG must skip empty house, got ' + city.get_house(empty_id).physician)
        return
    }
    if (served != 1) {
        test225_fail('OG must count inhabited house tiles only, got ' + served)
        return
    }
    __log_marker('test225_og_coverage')

    // Marsh ring at distance 4: grid risk reaches the hut, but no terrain floor (floor needs marsh within 3).
    var ax = cx - 20
    var bx = cx + 20
    var a_id = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, ax, cy)
    var b_id = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, bx, cy)
    if (!a_id || !b_id) {
        test225_fail('malaria house create failed')
        return
    }
    test225_marsh_ring(ax, cy, 4)
    test225_marsh_ring(bx, cy, 4)
    city.get_house(a_id).physician = 96
    city.get_house(b_id).physician = 0
    __test_update_malaria_risk()

    var risk_covered = city.get_building(a_id).malaria_risk
    var risk_plain = city.get_building(b_id).malaria_risk
    if (risk_plain <= 0) {
        test225_fail('test setup: uncovered house has no malaria risk')
        return
    }
    if (risk_covered != Math.max(0, risk_plain - 25)) {
        test225_fail('covered risk expected ' + Math.max(0, risk_plain - 25) + ' got ' + risk_covered + ' (plain ' + risk_plain + ')')
        return
    }
    __log_marker('test225_malaria_cut:' + risk_plain + '->' + risk_covered)

    game_features.set('gameplay_change_physician_service_cap', true)
    __test_update_malaria_risk()
    if (city.get_building(a_id).malaria_risk != city.get_building(b_id).malaria_risk) {
        test225_fail('remake must not cut malaria risk')
        return
    }

    city.get_house(lived_id).physician = 60
    __test_figure_provide_service(fid)
    if (city.get_house(lived_id).physician != 60) {
        test225_fail('remake must skip houses above half coverage, got ' + city.get_house(lived_id).physician)
        return
    }
    __log_marker('test225_remake')

    __test225_ok = true
    test225_finish()
}

function check_valid() {
    return __test225_ok
        && __test_find_inlog('[test-marker] test225_delay_100pct')
        && __test_find_inlog('[test-marker] test225_og_coverage')
        && __test_find_inlog('[test-marker] test225_malaria_cut:')
        && __test_find_inlog('[test-marker] test225_remake')
}
