// EXPORT_SURPLUS exports only above trade_export_keep; IMPORT_AS_NEEDED imports up to it
// (OG empire_can_export_resource_to_city / empire_can_import_resource_from_city).
// Markers:
//   [test-marker] trade_surplus_export_ok
//   [test-marker] trade_export_amount_ok
//   [test-marker] trade_import_as_needed_ok

var __test461_surplus_ok = false
var __test461_export_ok = false
var __test461_import_ok = false

function test461_fail(msg) {
    __log_info_native('[test:461] ' + msg)
}

function test461_find_city(resource) {
    for (var id = 1; id < 80; id++) {
        if (__test_empire_city_trade_only(id, resource, 1500) >= 0) {
            return id
        }
    }
    return -1
}

function test461_set_stock(resource, amount) {
    __test_city_set_yards_stored(resource, amount)
    return __test_yards_stored(resource) == amount
}

function test461_check_surplus(trade_city) {
    var r = RESOURCE_POTTERY
    __test_set_city_population(500)
    __test_trade_update_export_keep()
    var keep = __test_trade_export_keep(r)
    if (keep != 400) {
        test461_fail('pottery keep want 400 got ' + keep)
        return false
    }
    __test_city_set_trade(r, TRADE_STATUS_EXPORT_SURPLUS, 0)
    if (!test461_set_stock(r, 400)) {
        test461_fail('stock 400 failed, have ' + __test_yards_stored(r))
        return false
    }
    if (__test_empire_can_export_to(trade_city, r) || __test_empire_can_export_to(0, r)) {
        test461_fail('surplus exported at the keep (400)')
        return false
    }
    test461_set_stock(r, 500)
    if (!__test_empire_can_export_to(trade_city, r) || !__test_empire_can_export_to(0, r)) {
        test461_fail('surplus not exported above the keep (500)')
        return false
    }
    // A bigger city keeps more: 500 is no longer a surplus.
    __test_set_city_population(3000)
    __test_trade_update_export_keep()
    if (__test_empire_can_export_to(trade_city, r)) {
        test461_fail('surplus exported below the pop-3000 keep (1600)')
        return false
    }
    return true
}

function test461_check_export_amount(trade_city) {
    var r = RESOURCE_POTTERY
    test461_set_stock(r, 500)
    __test_city_set_trade(r, TRADE_STATUS_EXPORT, 500)
    if (__test_empire_can_export_to(trade_city, r)) {
        test461_fail('EXPORT sold at the trading amount')
        return false
    }
    __test_city_set_trade(r, TRADE_STATUS_EXPORT, 400)
    if (!__test_empire_can_export_to(trade_city, r)) {
        test461_fail('EXPORT did not sell above the trading amount')
        return false
    }
    return true
}

function test461_check_import(trade_city) {
    var r = RESOURCE_POTTERY
    __test_set_city_population(500)
    __test_trade_update_export_keep()
    __test_city_set_trade(r, TRADE_STATUS_IMPORT_AS_NEEDED, 0)
    var limit = __test_empire_import_stock_limit(r)
    if (limit != 400) {
        test461_fail('import as needed limit want 400 got ' + limit)
        return false
    }
    test461_set_stock(r, 400)
    if (__test_empire_can_import_from(trade_city, r)) {
        test461_fail('imported at the keep (400)')
        return false
    }
    test461_set_stock(r, 300)
    if (!__test_empire_can_import_from(trade_city, r)) {
        test461_fail('did not import below the keep (300)')
        return false
    }
    __test_city_set_trade(r, TRADE_STATUS_IMPORT, 200)
    if (__test_empire_import_stock_limit(r) != 200 || __test_empire_can_import_from(trade_city, r)) {
        test461_fail('IMPORT should stop at the trading amount 200')
        return false
    }
    return true
}

function run_test() {
    __log_info_native('[test:461] trade surplus / import as needed')
    test_reload_city_session('data/default.map')
    __test_set_treasury(500000)

    var trade_city = test461_find_city(RESOURCE_POTTERY)
    if (trade_city < 0) {
        test461_fail('no empire city')
        __test_signal_ready()
        return
    }

    if (test461_check_surplus(trade_city)) {
        __log_marker('trade_surplus_export_ok')
        __test461_surplus_ok = true
    }
    if (test461_check_export_amount(trade_city)) {
        __log_marker('trade_export_amount_ok')
        __test461_export_ok = true
    }
    if (test461_check_import(trade_city)) {
        __log_marker('trade_import_as_needed_ok')
        __test461_import_ok = true
    }
    __test_signal_ready()
}

function check_valid() {
    return __test461_surplus_ok && __test461_export_ok && __test461_import_ok
}
