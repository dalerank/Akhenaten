// OG trader_size / free_trader_slot: traders a city may have at once, from its route limits
// (>2500 -> 3, >1500 -> 2, >0 -> 1, averaged over the goods and rounded up), capped by
// empire_trade_rules.max_traders_per_city, none while trader_blocked.
// Markers:
//   [test-marker] trader_count_default_cap_ok
//   [test-marker] trader_count_by_limits_ok
//   [test-marker] trader_count_config_cap_ok
//   [test-marker] trader_count_blocked_ok

var __test371_ok = {}

function test371_fail(msg) {
    __log_info_native('[test:371] ' + msg)
}

function test371_find_city() {
    for (var id = 1; id < 80; id++) {
        if (__test_empire_city_trade_only(id, RESOURCE_POTTERY, 1500) >= 0) {
            return id
        }
    }
    return -1
}

function test371_clear_slots(cid) {
    for (var s = 0; s < 3; s++) {
        __test_empire_city_set_trader_figure(cid, s, 0)
    }
}

// How many traders the city accepts: fill free slots one by one until none is left.
function test371_slots(cid) {
    test371_clear_slots(cid)
    var n = 0
    for (; n < 4; n++) {
        var slot = __test_empire_city_free_trader_slot(cid)
        if (slot < 0) {
            break
        }
        __test_empire_city_set_trader_figure(cid, slot, 9000 + n)
    }
    test371_clear_slots(cid)
    return n
}

function test371_expect(cid, label, size, slots) {
    var got_size = __test_empire_city_trader_size(cid)
    var got_slots = test371_slots(cid)
    if (got_size != size || got_slots != slots) {
        test371_fail(label + ' want size ' + size + ' slots ' + slots + ' got ' + got_size + '/' + got_slots)
        return false
    }
    return true
}

function test371_by_limits(cid) {
    var cases = [
        [0, 0, 0], [1500, 1, 1], [2500, 2, 2], [4000, 3, 3]
    ]
    for (var i = 0; i < cases.length; i++) {
        __test_empire_city_trade_only(cid, RESOURCE_POTTERY, cases[i][0])
        if (!test371_expect(cid, 'limit ' + cases[i][0], cases[i][1], cases[i][2])) {
            return false
        }
    }
    // Two goods: (3 + 1) / 2 = 2; (3 + 2) / 2 rounds up to 3.
    __test_empire_city_trade_only(cid, RESOURCE_POTTERY, 4000)
    __test_empire_city_add_trade(cid, RESOURCE_BEER, 1500)
    if (!test371_expect(cid, '4000+1500', 2, 2)) {
        return false
    }
    __test_empire_city_trade_only(cid, RESOURCE_POTTERY, 4000)
    __test_empire_city_add_trade(cid, RESOURCE_BEER, 2500)
    return test371_expect(cid, '4000+2500', 3, 3)
}

function run_test() {
    __log_info_native('[test:371] trader count')
    test_reload_city_session('data/default.map')

    var cid = test371_find_city()
    if (cid < 0) {
        test371_fail('no empire city')
        __test_signal_ready()
        return
    }

    var prev = __test_empire_set_max_traders_per_city(3)
    if (prev != 3) {
        test371_fail('empire.js max_traders_per_city want 3 got ' + prev)
    } else {
        __log_marker('trader_count_default_cap_ok')
        __test371_ok.cap = true
    }

    if (test371_by_limits(cid)) {
        __log_marker('trader_count_by_limits_ok')
        __test371_ok.limits = true
    }

    __test_empire_city_trade_only(cid, RESOURCE_POTTERY, 4000)
    __test_empire_set_max_traders_per_city(2)
    var two = test371_slots(cid)
    __test_empire_set_max_traders_per_city(1)
    var one = test371_slots(cid)
    __test_empire_set_max_traders_per_city(5)
    var five = test371_slots(cid)
    __test_empire_set_max_traders_per_city(prev)
    if (two != 2 || one != 1 || five != 3) {
        test371_fail('config cap want 2/1/3 got ' + two + '/' + one + '/' + five)
    } else {
        __log_marker('trader_count_config_cap_ok')
        __test371_ok.config = true
    }

    __test_empire_city_set_trader_blocked(cid, 1)
    var blocked = test371_slots(cid)
    __test_empire_city_set_trader_blocked(cid, 0)
    var unblocked = test371_slots(cid)
    if (blocked != 0 || unblocked != 3) {
        test371_fail('blocked want 0 then 3 got ' + blocked + '/' + unblocked)
    } else {
        __log_marker('trader_count_blocked_ok')
        __test371_ok.blocked = true
    }

    __test_signal_ready()
}

function check_valid() {
    return __test371_ok.cap && __test371_ok.limits && __test371_ok.config && __test371_ok.blocked
}
