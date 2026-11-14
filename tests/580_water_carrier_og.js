// Water supply and water carrier as OG (building_figure.c spawn_water_supply, service.c service_provide_water_coverage):
// - walker delay by the share of workers 100/75/50/25/1% -> 1/3/7/15/29 days, no walker without workers;
//   below desirability 30 on the building tile the share counts half;
// - the carrier gives water and counts only inhabited houses in range; a vacant lot and other buildings do not count.
// Markers:
//   [test-marker] water_supply_spawn_delay_ok
//   [test-marker] water_carrier_coverage_ok

var __test580_ok = false

function test580_fail(msg) {
    __log_info_native('[test:580] FAIL ' + msg)
    __test_signal_ready()
}

// Places a water supply on groundwater with a road below it and returns the day the first carrier leaves, 0 if none.
function test580_spawn_day(x, y, workers, desirability) {
    for (var dy = 0; dy < 2; dy++) {
        for (var dx = 0; dx < 2; dx++) {
            terrain.add({ x: x + dx, y: y + dy }, TERRAIN_GROUNDWATER)
        }
        terrain.add({ x: x + dy, y: y + 2 }, TERRAIN_ROAD)
    }
    var bid = test_building_place(BUILDING_WATER_SUPPLY, x, y)
    if (!bid) {
        return -1
    }
    __test_building_set_workers(bid, workers)
    __test_set_desirability(x, y, desirability)
    city.get_building(bid).figure_spawn_delay = 0
    for (var day = 1; day <= 40; day++) {
        __test_building_spawn_figure(bid)
        if (__building_get_figure_id(bid, BUILDING_SLOT_SERVICE) > 0) {
            return day
        }
    }
    return 0
}

function run_test() {
    __log_info_native('[test:580] water carrier OG')
    test_ensure_city_session('data/default.map')
    __test_set_treasury(100000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    // OG spawn_due: a carrier leaves once the day counter passes the delay, so on day delay + 1.
    var cases = [
        { workers: 5, des: 40, day: 2 },
        { workers: 4, des: 40, day: 4 },
        { workers: 3, des: 40, day: 8 },
        { workers: 2, des: 40, day: 16 },
        { workers: 1, des: 40, day: 30 },
        { workers: 0, des: 40, day: 0 },
        { workers: 5, des: 29, day: 8 },
        { workers: 4, des: 29, day: 16 },
        { workers: 2, des: 29, day: 30 },
    ]
    for (var i = 0; i < cases.length; i++) {
        var c = cases[i]
        var got = test580_spawn_day(cx - 30 + i * 4, cy - 10, c.workers, c.des)
        if (got != c.day) {
            return test580_fail('workers=' + c.workers + ' desirability=' + c.des + ' spawn day=' + got + ' expected ' + c.day)
        }
    }
    __log_marker('water_supply_spawn_delay_ok')

    var hx = cx + 6
    var hy = cy + 6
    var hut = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, hx, hy)
    var lot = __test_building_create(BUILDING_HOUSE_VACANT_LOT, hx + 1, hy)
    var statue = test_building_place(BUILDING_SMALL_STATUE, hx, hy + 1)
    if (!hut || !lot || !statue) {
        return test580_fail('create failed hut=' + hut + ' lot=' + lot + ' statue=' + statue)
    }
    __test_house_set_population(hut, 5)
    __test_house_set_population(lot, 0)
    city.get_house(hut).water_supply = 0
    city.get_house(lot).water_supply = 0

    var fid = __test_figure_create(FIGURE_WATER_CARRIER, hx, hy - 1)
    if (!fid) {
        return test580_fail('water carrier create failed')
    }
    var served = __test_figure_provide_service(fid)
    var hut_water = city.get_house(hut).water_supply | 0
    var lot_water = city.get_house(lot).water_supply | 0
    if (served != 1 || hut_water != 96 || lot_water != 0) {
        return test580_fail('served=' + served + ' hut water=' + hut_water + ' lot water=' + lot_water)
    }
    __log_marker('water_carrier_coverage_ok')

    __test580_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test580_ok
        && __test_find_inlog('[test-marker] water_supply_spawn_delay_ok')
        && __test_find_inlog('[test-marker] water_carrier_coverage_ok')
}
