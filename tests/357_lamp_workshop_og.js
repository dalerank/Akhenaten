// OG lamp maker: Pharaoh_Model row 232, production cycle (100 oil + 100 pottery taken when the
// 100 lamp cart leaves, progress to 400), animation on any oil and any pottery, city sound,
// info window staffing texts and construction_warning_check_lamps.

var __test357_ok = false

var NEEDS_BOTH = '#building_needs_oil_and_pottery'
var NEEDS_OIL = '#building_needs_oil'
var NEEDS_POTTERY = '#building_needs_pottery'
var OIL_OVERSEER = '#import_oil_overseer'
var OIL_ROUTE = '#import_oil_trade_route'
var BUILD_POTTER = '#build_potter'
var POTTERY_OVERSEER = '#import_pottery_overseer'
var POTTERY_ROUTE = '#import_pottery_trade_route'
var SETUP_TRADE = '#setup_trade_route_to_import'
var OVERSEER_IMPORT = '#overseer_of_commerce_to_import'
var ALL_WARNINGS = [NEEDS_BOTH, NEEDS_OIL, NEEDS_POTTERY, OIL_OVERSEER, OIL_ROUTE, BUILD_POTTER,
    POTTERY_OVERSEER, POTTERY_ROUTE, SETUP_TRADE, OVERSEER_IMPORT]

function test357_fail(msg) {
    __log_info_native('[test:357] FAIL: ' + msg)
    __test_signal_ready()
}

function test357_same(a, b) {
    if (a.length != b.length) {
        return false
    }
    for (var i = 0; i < a.length; i++) {
        if (a[i] != b[i]) {
            return false
        }
    }
    return true
}

function test357_place() {
    __test_construction_warnings_reset()
    var bid = test_building_place(BUILDING_LAMP_WORKSHOP, -1, -1)
    __test_process_events()
    return bid
}

function test357_shown() {
    var shown = []
    for (var i = 0; i < ALL_WARNINGS.length; i++) {
        if (__test_construction_warning_count(ALL_WARNINGS[i]) > 0) {
            shown.push(ALL_WARNINGS[i])
        }
    }
    return shown.join(',')
}

function test357_expect_warnings(label, expected) {
    if (!test357_place()) {
        test357_fail(label + ': place failed')
        return false
    }
    var shown = test357_shown()
    if (shown != expected.join(',')) {
        test357_fail(label + ': warnings [' + shown + '] expected [' + expected.join(',') + ']')
        return false
    }
    return true
}

function test357_stock_yard(resource) {
    var yard = __test_building_create(BUILDING_STORAGE_YARD, -1, -1)
    return yard && __test_storage_yard_add_resource(yard, resource, 100)
}

function test357_reload() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    if (!__scenario_building_allowed(BUILDING_STORAGE_YARD)) {
        __scenario_building_allow(BUILDING_STORAGE_YARD, true)
    }
}

function test357_check_model() {
    var cfg = building_lamp_workshop
    if (!test357_same(cfg.cost, [20, 80, 100, 120, 150]) || !test357_same(cfg.fire_risk, [4, 15, 20, 24, 30])
        || !test357_same(cfg.damage_risk, [0]) || !test357_same(cfg.laborers, [12])) {
        test357_fail('model row: cost=' + cfg.cost + ' fire=' + cfg.fire_risk + ' damage=' + cfg.damage_risk
            + ' laborers=' + cfg.laborers)
        return false
    }
    if (__building_static_building_size(BUILDING_LAMP_WORKSHOP) != 2
        || __building_static_labor_category(BUILDING_LAMP_WORKSHOP) != LABOR_CATEGORY_INDUSTRY_COMMERCE) {
        test357_fail('size/labor category')
        return false
    }
    __log_marker('test357_model_ok')
    return true
}

function test357_check_warnings() {
    test357_reload()
    var oil_import = city.resources.oil.can_import
    var pottery_import = city.resources.pottery.can_import
    if (oil_import || pottery_import) {
        test357_fail('default.map is expected to have no open oil/pottery route')
        return false
    }

    city.resources.set_produce(RESOURCE_POTTERY, false)
    // Both missing: the oil hint without a route is the overseer text (OG swap).
    if (!test357_expect_warnings('none/no potter', [NEEDS_BOTH, OIL_OVERSEER, POTTERY_OVERSEER])) {
        return false
    }
    city.resources.set_produce(RESOURCE_POTTERY, true)
    if (!test357_expect_warnings('none/potter', [NEEDS_BOTH, OIL_OVERSEER, BUILD_POTTER])) {
        return false
    }
    if (!test357_stock_yard(RESOURCE_POTTERY)) {
        test357_fail('could not stock pottery')
        return false
    }
    if (!test357_expect_warnings('pottery only', [NEEDS_OIL, SETUP_TRADE])) {
        return false
    }
    if (!test357_stock_yard(RESOURCE_OIL)) {
        test357_fail('could not stock oil')
        return false
    }
    if (!test357_expect_warnings('oil and pottery', [])) {
        return false
    }

    test357_reload()
    city.resources.set_produce(RESOURCE_POTTERY, true)
    if (!test357_stock_yard(RESOURCE_OIL) || !test357_expect_warnings('oil only/potter', [NEEDS_POTTERY, BUILD_POTTER])) {
        return false
    }
    city.resources.set_produce(RESOURCE_POTTERY, false)
    if (!test357_expect_warnings('oil only/no potter', [NEEDS_POTTERY, SETUP_TRADE])) {
        return false
    }

    test357_reload()
    if (!test357_stock_yard(RESOURCE_LAMPS) || !test357_expect_warnings('lamps in yards', [])) {
        return false
    }
    __log_marker('test357_warnings_ok')
    return true
}

function test357_stock(bid, resource) {
    return city.get_building(bid).stored_resource(resource)
}

function test357_check_cycle() {
    test357_reload()
    var bid = __test_building_create(BUILDING_LAMP_WORKSHOP, -1, -1)
    if (!bid) {
        test357_fail('create failed')
        return false
    }
    __test_building_force_road_access(bid)
    __test_building_set_houses_covered(bid, 100)
    __test_building_set_workers(bid, 12)
    __test_building_update_day(bid)

    var b = city.get_building(bid)
    b.consume_resource(RESOURCE_OIL, -100)
    __test_city_industry_update_production()
    if (__building_industry_progress(bid) != 0) {
        test357_fail('oil without pottery must hold progress, got ' + __building_industry_progress(bid))
        return false
    }

    b.consume_resource(RESOURCE_POTTERY, -100)
    __test_building_update_day(bid)
    __test_city_industry_update_production()
    if (__building_industry_progress(bid) != 12) {
        test357_fail('one day with 12 workers expected 12 got ' + __building_industry_progress(bid))
        return false
    }

    for (var i = 0; i < 40; i++) {
        __test_city_industry_update_production()
        __test_building_update_day(bid)
    }
    if (__building_industry_progress(bid) != 400 || test357_stock(bid, RESOURCE_OIL) != 100
        || test357_stock(bid, RESOURCE_POTTERY) != 100 || test357_stock(bid, RESOURCE_LAMPS) != 0) {
        test357_fail('done cycle: progress=' + __building_industry_progress(bid) + ' oil=' + test357_stock(bid, RESOURCE_OIL)
            + ' pottery=' + test357_stock(bid, RESOURCE_POTTERY) + ' lamps=' + test357_stock(bid, RESOURCE_LAMPS))
        return false
    }

    __test_building_spawn_figure(bid)
    var cart = city.get_building(bid).get_figure(BUILDING_SLOT_CARTPUSHER)
    if (!cart || !cart.valid) {
        test357_fail('missing cartpusher after the cycle')
        return false
    }
    if (__test_figure_resource(cart.id) != RESOURCE_LAMPS || __test_figure_carrying_amount(cart.id) != 100) {
        test357_fail('expected a 100 lamps cart, got ' + __test_figure_resource(cart.id) + '/' + __test_figure_carrying_amount(cart.id))
        return false
    }
    if (__building_industry_progress(bid) != 0 || test357_stock(bid, RESOURCE_OIL) != 0 || test357_stock(bid, RESOURCE_POTTERY) != 0) {
        test357_fail('cart start must reset progress and take both inputs, progress=' + __building_industry_progress(bid)
            + ' oil=' + test357_stock(bid, RESOURCE_OIL) + ' pottery=' + test357_stock(bid, RESOURCE_POTTERY))
        return false
    }
    __log_marker('test357_cycle_ok')

    b = city.get_building(bid)
    b.consume_resource(RESOURCE_OIL, -50)
    b.consume_resource(RESOURCE_POTTERY, -50)
    __test_building_update_day(bid)
    if (!city.get_building(bid).play_animation) {
        test357_fail('any oil and any pottery must animate')
        return false
    }
    b.consume_resource(RESOURCE_POTTERY, 50)
    __test_building_update_day(bid)
    if (city.get_building(bid).play_animation) {
        test357_fail('no pottery must stop the animation')
        return false
    }
    __log_marker('test357_animation_ok')

    if (__test_sound_city_mark_building(bid, 4) != SOUND_CHANNEL_CITY_LAMP_WORKSHOP) {
        test357_fail('sound channel')
        return false
    }
    __log_marker('test357_sound_ok')
    return true
}

function test357_check_staff_texts() {
    var pcts = [100, 75, 74, 50, 49, 25, 24, 1]
    var want = [6, 7, 8, 8, 9, 9, 10, 10]
    for (var i = 0; i < pcts.length; i++) {
        var got = info_window_lamp_workshop_staff_text(pcts[i])
        if (got != want[i]) {
            test357_fail('staff text for ' + pcts[i] + '% = ' + got + ' expected ' + want[i])
            return false
        }
    }
    __log_marker('test357_staff_texts_ok')
    return true
}

function run_test() {
    __log_info_native('[test:357] lamp workshop OG')
    if (!test357_check_model() || !test357_check_warnings() || !test357_check_cycle() || !test357_check_staff_texts()) {
        return
    }
    __test357_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test357_ok
        && __test_find_inlog('[test-marker] test357_model_ok')
        && __test_find_inlog('[test-marker] test357_warnings_ok')
        && __test_find_inlog('[test-marker] test357_cycle_ok')
        && __test_find_inlog('[test-marker] test357_animation_ok')
        && __test_find_inlog('[test-marker] test357_sound_ok')
        && __test_find_inlog('[test-marker] test357_staff_texts_ok')
}
