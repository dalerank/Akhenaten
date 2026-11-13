// OG spawn_industry ships 100 output for every 100 input cycle (building_figure.c), and raw sites
// add num_workers progress per day (building_industry.c). gameplay_change_industry_remake_rates
// restores the remake rates: pottery production_rate 20, quarries workers/2, gem mines workers/3.
// Markers:
//   [test-marker] industry_rates_og_ok
//   [test-marker] industry_rates_remake_ok

var __test441_ok = false
var __test441_feat_prev = null

function test441_fail(msg) {
    __log_info_native('[test:441] FAIL: ' + msg)
    if (__test441_feat_prev !== null) {
        game_features.set('gameplay_change_industry_remake_rates', __test441_feat_prev)
    }
    __test_signal_ready()
}

function test441_pottery_output(cx, cy) {
    var bid = __test_building_create(BUILDING_POTTERY_WORKSHOP, cx, cy)
    if (!bid) {
        return -1
    }
    __test_building_force_road_access(bid)
    __test_building_set_houses_covered(bid, 100)
    __test_building_set_workers(bid, 12)
    var b = city.get_building(bid)
    // start_production takes 100; the remake update_production also waits for another 100 in stock.
    b.consume_resource(RESOURCE_CLAY, -200)
    __test_building_update_day(bid)
    if (b.stored_resource(RESOURCE_CLAY) != 100) {
        return -2
    }
    var i
    for (i = 0; i < 60; i++) {
        __test_city_industry_update_production()
        __test_building_update_day(bid)
    }
    return b.stored_resource(RESOURCE_POTTERY)
}

function test441_raw_progress(type, x, y, init_deposit) {
    terrain.add({ x: x + 2, y: y }, TERRAIN_ROCK)
    terrain.add({ x: x + 2, y: y + 1 }, TERRAIN_ROCK)
    init_deposit()
    var bid = test_building_place(type, x, y)
    if (!bid) {
        bid = __test_building_create(type, x, y)
    }
    if (!bid) {
        return -1
    }
    __test_building_set_workers(bid, 8)
    city.get_building(bid).houses_covered = 100
    __test_building_update_day(bid)
    __test_city_industry_update_production()
    return __building_industry_progress(bid)
}

function test441_run(remake, expect_pottery, expect_quarry, expect_gems) {
    game_features.set('gameplay_change_industry_remake_rates', remake)
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var label = remake ? 'remake' : 'og'

    var pottery = test441_pottery_output(cx, cy)
    if (pottery != expect_pottery) {
        return label + ' pottery from 100 clay want ' + expect_pottery + ' got ' + pottery
    }
    var quarry = test441_raw_progress(BUILDING_STONE_QUARRY, cx + 8, cy, __test_map_quarry_deposits_init)
    if (quarry != expect_quarry) {
        return label + ' stone quarry progress want ' + expect_quarry + ' got ' + quarry
    }
    var gems = test441_raw_progress(BUILDING_GEMSTONE_MINE, cx, cy + 8, __test_map_gems_init)
    if (gems != expect_gems) {
        return label + ' gem mine progress want ' + expect_gems + ' got ' + gems
    }
    return ''
}

function run_test() {
    __log_info_native('[test:441] OG workshop output and raw site rates')
    __test441_feat_prev = !!game_features.get('gameplay_change_industry_remake_rates')

    // update_day starts raw progress at 1, then one production tick with 8 workers.
    var err = test441_run(false, 100, 1 + 8, 1 + 8)
    if (err) {
        return test441_fail(err)
    }
    __log_marker('industry_rates_og_ok')

    err = test441_run(true, building_pottery.production_rate, 1 + 4, 1 + 2)
    if (err) {
        return test441_fail(err)
    }
    __log_marker('industry_rates_remake_ok')

    game_features.set('gameplay_change_industry_remake_rates', __test441_feat_prev)
    __test441_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test441_ok
        && __test_find_inlog('[test-marker] industry_rates_og_ok')
        && __test_find_inlog('[test-marker] industry_rates_remake_ok')
}
