// OG trade_export_keep (empire.c empire_update_export_keep): what the city keeps before it
// exports a surplus, per category.
// Markers:
//   [test-marker] trade_keep_food_ok
//   [test-marker] trade_keep_workshop_ok
//   [test-marker] trade_keep_monument_ok
//   [test-marker] trade_keep_other_ok
//   [test-marker] trade_keep_request_ok
//   [test-marker] trade_keep_provisions_ok

var __test460_ok = {}

function test460_fail(msg) {
    __log_info_native('[test:460] ' + msg)
}

function test460_keep(resource) {
    __test_trade_update_export_keep()
    return __test_trade_export_keep(resource)
}

function test460_expect(label, resource, want) {
    var got = test460_keep(resource)
    if (got != want) {
        test460_fail(label + ' want ' + want + ' got ' + got)
        return false
    }
    return true
}

function test460_set_monuments(a, b, c) {
    __scenario_monuments.first = a
    __scenario_monuments.second = b
    __scenario_monuments.third = c
}

function test460_food() {
    // trade_recommends.txt rows: <1000, <2500, <5000, rest.
    var rows = [
        { pop: 500, grain: 600, fish: 600, pottery: 400, beer: 400, linen: 400, papyrus: 300, luxury: 200 },
        { pop: 1000, grain: 1200, fish: 1200, pottery: 800, beer: 800, linen: 800, papyrus: 600, luxury: 400 },
        { pop: 3000, grain: 2400, fish: 2400, pottery: 1600, beer: 1600, linen: 1600, papyrus: 1200, luxury: 800 },
        { pop: 6000, grain: 4000, fish: 4000, pottery: 3000, beer: 3000, linen: 3000, papyrus: 2000, luxury: 1500 }
    ]
    for (var i = 0; i < rows.length; i++) {
        var row = rows[i]
        __test_set_city_population(row.pop)
        var p = 'pop ' + row.pop + ' '
        if (!test460_expect(p + 'grain', RESOURCE_GRAIN, row.grain)
            || !test460_expect(p + 'fish', RESOURCE_FISH, row.fish)
            || !test460_expect(p + 'pottery', RESOURCE_POTTERY, row.pottery)
            || !test460_expect(p + 'beer', RESOURCE_BEER, row.beer)
            || !test460_expect(p + 'linen', RESOURCE_LINEN, row.linen)
            || !test460_expect(p + 'papyrus', RESOURCE_PAPYRUS, row.papyrus)
            || !test460_expect(p + 'luxury', RESOURCE_LUXURY_GOODS, row.luxury)) {
            return false
        }
    }
    return true
}

function test460_workshop() {
    // (workshops using it + 1) * 200; the default map has no staffed workshops.
    var raws = [RESOURCE_REEDS, RESOURCE_CLAY, RESOURCE_GEMS, RESOURCE_BARLEY, RESOURCE_FLAX,
                RESOURCE_STRAW, RESOURCE_COPPER, RESOURCE_TIMBER, RESOURCE_HENNA]
    for (var i = 0; i < raws.length; i++) {
        if (!test460_expect('raw ' + raws[i], raws[i], 200)) {
            return false
        }
    }
    return true
}

function test460_monument() {
    test460_set_monuments(0, 0, 0)
    if (!test460_expect('no monument stone', RESOURCE_STONE, 500)
        || !test460_expect('no monument bricks', RESOURCE_BRICKS, 500)
        || !test460_expect('no monument granite', RESOURCE_GRANITE, 500)) {
        return false
    }
    // Unplaced small pyramid: stone 4800, casing limestone 19200.
    test460_set_monuments(13, 0, 0)
    if (!test460_expect('small pyramid stone', RESOURCE_STONE, 5300)
        || !test460_expect('small pyramid limestone', RESOURCE_LIMESTONE, 19700)
        || !test460_expect('small pyramid bricks', RESOURCE_BRICKS, 500)) {
        return false
    }
    // Two unplaced small mastabas + small obelisk.
    test460_set_monuments(18, 18, 22)
    if (!test460_expect('mastabas bricks', RESOURCE_BRICKS, 2 * 10800 + 500)
        || !test460_expect('obelisk granite', RESOURCE_GRANITE, 10500)) {
        return false
    }
    // Capped at 30000 for the building materials.
    test460_set_monuments(17, 0, 0)
    if (!test460_expect('grand pyramid stone cap', RESOURCE_STONE, 30000)) {
        return false
    }
    test460_set_monuments(0, 0, 0)
    return true
}

function test460_other() {
    var others = [RESOURCE_WEAPONS, RESOURCE_GOLD, RESOURCE_OIL, RESOURCE_MARBLE, RESOURCE_LAMPS, RESOURCE_PAINT]
    for (var i = 0; i < others.length; i++) {
        if (!test460_expect('other ' + others[i], others[i], 1000)) {
            return false
        }
    }
    return true
}

function test460_request() {
    var req = city.create_good_request({
        tag_id: 46001,
        resource: RESOURCE_GOLD,
        amount: 5,
        months_initial: 9
    })
    req.execute()
    __test_process_events()
    if (!__test_request_is_active(46001)) {
        test460_fail('request not active')
        return false
    }
    return test460_expect('gold with request', RESOURCE_GOLD, 1500)
}

function test460_provisions() {
    __test_burial_provisions_clear()
    __test_burial_provisions_set(RESOURCE_OIL, 3)
    var ok = test460_expect('oil with provisions', RESOURCE_OIL, 1300)
    __test_burial_provisions_clear()
    return ok
}

function run_test() {
    __log_info_native('[test:460] trade export keep')
    test_reload_city_session('data/default.map')

    var checks = [
        ['trade_keep_food_ok', test460_food],
        ['trade_keep_workshop_ok', test460_workshop],
        ['trade_keep_monument_ok', test460_monument],
        ['trade_keep_other_ok', test460_other],
        ['trade_keep_request_ok', test460_request],
        ['trade_keep_provisions_ok', test460_provisions]
    ]
    for (var i = 0; i < checks.length; i++) {
        if (checks[i][1]()) {
            __log_marker(checks[i][0])
            __test460_ok[checks[i][0]] = true
        }
    }
    __test_signal_ready()
}

function check_valid() {
    var names = ['trade_keep_food_ok', 'trade_keep_workshop_ok', 'trade_keep_monument_ok',
                 'trade_keep_other_ok', 'trade_keep_request_ok', 'trade_keep_provisions_ok']
    for (var i = 0; i < names.length; i++) {
        if (!__test460_ok[names[i]]) {
            __log_info_native('[test:460] missing ' + names[i])
            return false
        }
    }
    return true
}
