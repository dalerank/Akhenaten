// Apothecary OG: spawn_service_walker with delays_service {3,7,15,29,44} by worker %,
// coverage gives 96 to every inhabited house in radius 2, no malaria cut and no health floor.
// House culture health aggregate is physician+mortuary (not apothecary). Advisor coverage is
// share of people with living apothecary access. Model fire_risk by difficulty, damage_risk 0.
// gameplay_change_apothecary_remake restores health floor 50 and the malaria cut.

var __test226_ok = false
var __test226_flag_prev = false

function test226_finish() {
    game_features.set('gameplay_change_apothecary_remake', __test226_flag_prev)
    __test_signal_ready()
}

function test226_fail(msg) {
    __log_info_native('[test:226] FAIL: ' + msg)
    test226_finish()
}

function test226_spawn(bid) {
    building_apothecary_spawn_figure({ bid: bid })
    return __test_count_figures(FIGURE_HERBALIST)
}

function test226_check_spawn_delay() {
    var bid = test_building_place(BUILDING_APOTHECARY, -1, -1)
    if (!bid) {
        test226_fail('place failed')
        return 0
    }

    var zt = __building_tile(bid)
    for (var dx = 0; dx < 3; dx++) {
        terrain.add({ x: zt.x + dx, y: zt.y + 1 }, TERRAIN_ROAD)
    }
    __test_update_road_network()
    __test_check_kingdome_access()

    __test_building_set_workers(bid, 5)
    var b = city.get_building(bid)
    b.has_road_access = true
    b.figure_spawn_delay = 0
    city.figures.remove_figures(FIGURE_HERBALIST)

    for (var d = 1; d <= 3; d++) {
        if (test226_spawn(bid) > 0) {
            test226_fail('herbalist spawned too early at day ' + d)
            return 0
        }
    }
    if (test226_spawn(bid) < 1) {
        test226_fail('herbalist expected on day 4 at 100% workers')
        return 0
    }
    __log_marker('test226_delay_100pct')
    return bid
}

function test226_marsh_ring(cx, cy, r) {
    for (var i = -r; i <= r; i++) {
        terrain.add({ x: cx + i, y: cy - r }, TERRAIN_MARSHLAND)
        terrain.add({ x: cx + i, y: cy + r }, TERRAIN_MARSHLAND)
        terrain.add({ x: cx - r, y: cy + i }, TERRAIN_MARSHLAND)
        terrain.add({ x: cx + r, y: cy + i }, TERRAIN_MARSHLAND)
    }
}

function run_test() {
    __log_info_native('[test:226] apothecary OG')
    __test226_flag_prev = game_features.get('gameplay_change_apothecary_remake') === true
    if (game_features.default('gameplay_change_apothecary_remake')) {
        test226_fail('apothecary remake flag must default OFF')
        return
    }
    game_features.set('gameplay_change_apothecary_remake', false)

    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)

    var apothecary_id = test226_check_spawn_delay()
    if (!apothecary_id) {
        return
    }

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var lived_id = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, cx, cy)
    var empty_id = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, cx + 1, cy)
    if (!lived_id || !empty_id) {
        test226_fail('house create failed')
        return
    }
    if (__test_house_set_population(lived_id, 10) < 1) {
        test226_fail('set population failed')
        return
    }

    var fid = test_figure_create(FIGURE_HERBALIST, cx, cy + 1)
    if (!fid) {
        test226_fail('herbalist figure create failed')
        return
    }
    __test_figure_set_home(fid, apothecary_id)

    var lived = city.get_building(lived_id)
    lived.common_health = 5
    var served = __test_figure_provide_service(fid)
    if (city.get_house(lived_id).apothecary != 96) {
        test226_fail('OG must give inhabited house 96, got ' + city.get_house(lived_id).apothecary)
        return
    }
    if (city.get_house(empty_id).apothecary != 0) {
        test226_fail('OG must skip empty house, got ' + city.get_house(empty_id).apothecary)
        return
    }
    if (served != 1) {
        test226_fail('OG must count inhabited house tiles only, got ' + served)
        return
    }
    if (city.get_building(lived_id).common_health != 5) {
        test226_fail('OG must not raise house health, got ' + city.get_building(lived_id).common_health)
        return
    }
    __log_marker('test226_og_coverage')

    city.get_house(lived_id).apothecary = 96
    city.get_house(lived_id).physician = 0
    city.get_house(lived_id).mortuary = 0
    city.get_house(empty_id).apothecary = 0
    city.get_house(empty_id).physician = 96
    city.get_house(empty_id).mortuary = 0
    if (__test_house_set_population(empty_id, 5) < 1) {
        test226_fail('set empty house population failed')
        return
    }
    __test_house_calculate_culture_aggregates()
    if (city.get_house(lived_id).health != 0) {
        test226_fail('OG health aggregate must ignore apothecary, got ' + city.get_house(lived_id).health)
        return
    }
    if (city.get_house(empty_id).health != 1) {
        test226_fail('OG health aggregate must count physician, got ' + city.get_house(empty_id).health)
        return
    }
    city.get_house(empty_id).mortuary = 96
    __test_house_calculate_culture_aggregates()
    if (city.get_house(empty_id).health != 2) {
        test226_fail('OG health aggregate must count physician+mortuary, got ' + city.get_house(empty_id).health)
        return
    }
    __log_marker('test226_og_health_aggregate')

    city.get_house(lived_id).apothecary = 0
    __test_health_update_coverage()
    var cov_without = city.coverage.apothecary
    city.get_house(lived_id).apothecary = 96
    __test_health_update_coverage()
    var cov_with = city.coverage.apothecary
    if (cov_with <= cov_without) {
        test226_fail('OG coverage must rise with house access: ' + cov_without + ' -> ' + cov_with)
        return
    }
    __log_marker('test226_og_advisor_coverage')

    var expected_fire = [4, 17, 20, 24, 30]
    for (var d = 0; d < 5; d++) {
        if (building_apothecary.fire_risk[d] != expected_fire[d]) {
            test226_fail('fire_risk[' + d + '] expected ' + expected_fire[d] + ' got ' + building_apothecary.fire_risk[d])
            return
        }
    }
    if (building_apothecary.damage_risk[0] != 0) {
        test226_fail('damage_risk must be 0, got ' + building_apothecary.damage_risk[0])
        return
    }
    __log_marker('test226_og_model')

    var ax = cx - 20
    var bx = cx + 20
    var a_id = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, ax, cy)
    var b_id = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, bx, cy)
    if (!a_id || !b_id) {
        test226_fail('malaria house create failed')
        return
    }
    test226_marsh_ring(ax, cy, 4)
    test226_marsh_ring(bx, cy, 4)
    city.get_house(a_id).apothecary = 96
    city.get_house(b_id).apothecary = 0
    __test_update_malaria_risk()
    var risk_covered = city.get_building(a_id).malaria_risk
    var risk_plain = city.get_building(b_id).malaria_risk
    if (risk_plain <= 0) {
        test226_fail('test setup: uncovered house has no malaria risk')
        return
    }
    if (risk_covered != risk_plain) {
        test226_fail('OG apothecary must not cut malaria: ' + risk_covered + ' vs ' + risk_plain)
        return
    }
    __log_marker('test226_og_no_malaria')

    game_features.set('gameplay_change_apothecary_remake', true)
    __test_update_malaria_risk()
    if (city.get_building(a_id).malaria_risk >= city.get_building(b_id).malaria_risk) {
        test226_fail('remake must cut malaria risk')
        return
    }
    lived = city.get_building(lived_id)
    lived.common_health = 5
    __test_figure_provide_service(fid)
    if (city.get_building(lived_id).common_health != 50) {
        test226_fail('remake must raise house health to 50, got ' + city.get_building(lived_id).common_health)
        return
    }
    __log_marker('test226_remake')

    __test226_ok = true
    test226_finish()
}

function check_valid() {
    return __test226_ok
        && __test_find_inlog('[test-marker] test226_delay_100pct')
        && __test_find_inlog('[test-marker] test226_og_coverage')
        && __test_find_inlog('[test-marker] test226_og_health_aggregate')
        && __test_find_inlog('[test-marker] test226_og_advisor_coverage')
        && __test_find_inlog('[test-marker] test226_og_model')
        && __test_find_inlog('[test-marker] test226_og_no_malaria')
        && __test_find_inlog('[test-marker] test226_remake')
}
