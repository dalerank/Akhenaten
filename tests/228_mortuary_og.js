// Mortuary OG spawn_stock_walker: days between embalmers from delays_service {3,7,15,29,44} by worker %,
// linen (walker_cost by difficulty) paid only when the embalmer leaves, less with a Seth complex altar.
// Coverage always sets 96 on inhabited houses (no monthly cap / half-coverage refresh).
// Model cost/fire/damage match Pharaoh_Model_*.txt. Remake service/linen flags default off.
// Below health 30 the embalmer says its own phrase (e01), else its city phrase.

var __test228_ok = false

function test228_fail(msg) {
    __log_info_native('[test:228] FAIL: ' + msg)
    __test_signal_ready()
}

function test228_spawn(bid) {
    building_mortuary_spawn_figure({ bid: bid })
    return __test_count_figures(FIGURE_EMBALMER)
}

function test228_place_mortuary() {
    var bid = test_building_place(BUILDING_MORTUARY, -1, -1)
    if (!bid) {
        return 0
    }
    var zt = __building_tile(bid)
    for (var dx = 0; dx < 3; dx++) {
        terrain.add({ x: zt.x + dx, y: zt.y + 2 }, TERRAIN_ROAD)
    }
    __test_update_road_network()
    __test_building_set_workers(bid, 8)
    var b = city.get_building(bid)
    b.has_road_access = true
    b.figure_spawn_delay = 0
    return bid
}

function run_test() {
    __log_info_native('[test:228] mortuary OG')
    var flags = [
        'gameplay_change_mortuary_service_cap',
        'gameplay_change_mortuary_linen_upkeep',
        'gameplay_change_mortuary_mothballed_linen'
    ]
    for (var i = 0; i < flags.length; i++) {
        if (game_features.default(flags[i])) {
            test228_fail(flags[i] + ' must default OFF')
            return
        }
    }
    game_features.set('gameplay_change_mortuary_service_cap', false)

    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)
    __test_check_kingdome_access()

    var bid = test228_place_mortuary()
    if (!bid) {
        test228_fail('place failed')
        return
    }
    city.figures.remove_figures(FIGURE_EMBALMER)

    var cost = dcy_get(building_mortuary.walker_cost)
    if (cost <= 0) {
        test228_fail('walker_cost not configured')
        return
    }

    for (var d = 0; d < 10; d++) {
        if (test228_spawn(bid) > 0) {
            test228_fail('embalmer spawned without linen at day ' + d)
            return
        }
    }
    var b = city.get_building(bid)
    if (b.figure_spawn_delay != 10) {
        test228_fail('day counter must keep running without linen, got ' + b.figure_spawn_delay)
        return
    }
    __log_marker('test228_no_linen_no_embalmer')

    b.consume_resource(RESOURCE_LINEN, -(cost * 2))
    if (test228_spawn(bid) < 1) {
        test228_fail('expected embalmer once linen stocked, cost=' + cost)
        return
    }
    b = city.get_building(bid)
    if (b.stored_resource(RESOURCE_LINEN) != cost) {
        test228_fail('linen after spawn expected ' + cost + ' got ' + b.stored_resource(RESOURCE_LINEN))
        return
    }
    if (b.figure_spawn_delay != 0) {
        test228_fail('day counter must reset after spawn, got ' + b.figure_spawn_delay)
        return
    }
    __log_marker('test228_paid_on_spawn:' + cost)

    // 100% workers: OG delay 3 => the 4th day spawns.
    var bid2 = test228_place_mortuary()
    if (!bid2) {
        test228_fail('second place failed')
        return
    }
    city.get_building(bid2).consume_resource(RESOURCE_LINEN, -cost)
    var embalmers = __test_count_figures(FIGURE_EMBALMER)
    for (var day = 1; day <= 3; day++) {
        if (test228_spawn(bid2) > embalmers) {
            test228_fail('embalmer spawned too early at day ' + day)
            return
        }
    }
    if (test228_spawn(bid2) <= embalmers) {
        test228_fail('embalmer expected on day 4 at 100% workers')
        return
    }
    __log_marker('test228_delay_100pct')

    var cid = test_building_place(BUILDING_TEMPLE_COMPLEX_SETH, -1, -1)
    var complex = city.get_temple_complex()
    if (!cid || !complex || complex.type != BUILDING_TEMPLE_COMPLEX_SETH) {
        test228_fail('seth complex place failed id=' + cid)
        return
    }
    if (building_mortuary_walker_cost() != cost) {
        test228_fail('discount applied without altar')
        return
    }
    complex.temple_complex_upgrades = TEMPLE_COMPLEX_UPGRADE_ALTAR
    var discounted = Math.floor(cost * dcy_get(building_mortuary.seth_altar_walker_cost_pct) / 100)
    if (building_mortuary_walker_cost() != discounted) {
        test228_fail('seth altar cost expected ' + discounted + ' got ' + building_mortuary_walker_cost())
        return
    }
    __log_marker('test228_seth_altar_cost:' + discounted)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var lived_id = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, cx, cy)
    var empty_id = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, cx + 1, cy)
    if (!lived_id || !empty_id) {
        test228_fail('house create failed')
        return
    }
    if (__test_house_set_population(lived_id, 10) < 1) {
        test228_fail('set population failed')
        return
    }
    city.get_house(lived_id).mortuary = 50
    city.get_house(empty_id).mortuary = 0

    var fid = test_figure_create(FIGURE_EMBALMER, cx, cy + 1)
    if (!fid) {
        test228_fail('embalmer figure create failed')
        return
    }
    __test_figure_set_home(fid, bid)
    var served = __test_figure_provide_service(fid)
    if (city.get_house(lived_id).mortuary != 96) {
        test228_fail('OG must refresh inhabited house to 96, got ' + city.get_house(lived_id).mortuary)
        return
    }
    if (city.get_house(empty_id).mortuary != 0) {
        test228_fail('OG must skip empty house, got ' + city.get_house(empty_id).mortuary)
        return
    }
    if (served != 1) {
        test228_fail('OG must count inhabited house tiles only, got ' + served)
        return
    }
    __log_marker('test228_og_coverage')

    var expected_cost = [20, 80, 100, 120, 150]
    var expected_fire = [4, 17, 20, 24, 30]
    for (var d = 0; d < 5; d++) {
        if (building_mortuary.cost[d] != expected_cost[d]) {
            test228_fail('cost[' + d + '] expected ' + expected_cost[d] + ' got ' + building_mortuary.cost[d])
            return
        }
        if (building_mortuary.fire_risk[d] != expected_fire[d]) {
            test228_fail('fire_risk[' + d + '] expected ' + expected_fire[d] + ' got ' + building_mortuary.fire_risk[d])
            return
        }
    }
    if (building_mortuary.damage_risk[0] != 0) {
        test228_fail('damage_risk must be 0, got ' + building_mortuary.damage_risk[0])
        return
    }
    __log_marker('test228_og_model')

    var key = figure_embalmer_phrase_key()
    var low_health = city.health_rating < 30
    if (!figure_embalmer.sounds[key] || (low_health && key != 'embalmer_health_worsening')) {
        test228_fail('bad phrase key ' + key + ' health=' + city.health_rating)
        return
    }
    __log_marker('test228_phrase:' + key)

    __test228_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test228_ok
        && __test_find_inlog('[test-marker] test228_no_linen_no_embalmer')
        && __test_find_inlog('[test-marker] test228_paid_on_spawn:')
        && __test_find_inlog('[test-marker] test228_delay_100pct')
        && __test_find_inlog('[test-marker] test228_seth_altar_cost:')
        && __test_find_inlog('[test-marker] test228_og_coverage')
        && __test_find_inlog('[test-marker] test228_og_model')
        && __test_find_inlog('[test-marker] test228_phrase:')
}
