// Fireman at a burning ruin vs OG (walkers.c:905-913): each FIREMAN_AT_FIRE tick next to the ruin sets
// og fire_duration = walker_rules[FIRE_OUT_DURATION] (32), no RNG; the next ruin update does ++ -> 33 > 32
// and rubbles it (building_maintenance.c:537-541). Here fire_duration counts down (33 - og_duration),
// so an extinguished ruin holds fire_duration == 1 and turns to rubble on the next update.
// Markers:
//   [test-marker] fireman_extinguish_pins_duration_ok
//   [test-marker] fireman_extinguish_rubble_next_update_ok

var RUIN_BURN_DAYS = 32
var FIRE_OUT_DURATION = 32
var EXTINGUISHED = RUIN_BURN_DAYS + 1 - FIRE_OUT_DURATION

var __test305_ok = {
    pinned: false,
    rubble: false
}

function test305_fail(msg) {
    __log_info_native('[test:305] FAIL: ' + msg)
}

function test305_check_ruin(bid, pre_updates) {
    for (var i = 0; i < pre_updates; i++) {
        __test_burning_ruin_update(bid)
    }
    if (__test_building_is_rubble(bid) || __test_building_fire_duration(bid) <= EXTINGUISHED) {
        test305_fail('ruin ' + bid + ' not burning before extinguish, fire_duration=' + __test_building_fire_duration(bid))
        return false
    }

    __test_random_set_state(0x1234567, 0x7654321)
    var iv_before = __test_random_iv1()
    for (var t = 0; t < 3; t++) {
        var got = __test_fireman_extinguish_tick(bid)
        if (got != EXTINGUISHED) {
            test305_fail('ruin ' + bid + ' tick ' + t + ' fire_duration=' + got + ' want=' + EXTINGUISHED)
            return false
        }
    }
    if (__test_random_iv1() != iv_before) {
        test305_fail('extinguish consumed RNG')
        return false
    }
    if (__test_building_is_rubble(bid)) {
        test305_fail('ruin ' + bid + ' rubbled before its next update')
        return false
    }
    return true
}

function run_test() {
    __log_info_native('[test:305] fireman extinguish OG')
    test_reload_city_session('data/default.map')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    var pinned_ok = true
    var rubble_ok = true
    for (var i = 0; i < 4 && pinned_ok; i++) {
        var x = cx - 6 + i * 4
        var y = cy + 10
        var bid = __test_burning_ruin_create(x, y)
        if (!bid) {
            test305_fail('ruin create failed at ' + x + ',' + y)
            pinned_ok = false
            break
        }

        pinned_ok = test305_check_ruin(bid, i * 5)
        if (!pinned_ok) {
            break
        }

        __test_burning_ruin_update(bid)
        if (!__test_building_is_rubble(bid) || __test_building_fire_duration(bid) > 0) {
            test305_fail('ruin ' + bid + ' not rubble after next update, fire_duration=' + __test_building_fire_duration(bid))
            rubble_ok = false
        }
    }

    if (pinned_ok) {
        __test305_ok.pinned = true
        __log_info_native('[test-marker] fireman_extinguish_pins_duration_ok')
    }
    if (pinned_ok && rubble_ok) {
        __test305_ok.rubble = true
        __log_info_native('[test-marker] fireman_extinguish_rubble_next_update_ok')
    }

    __test_signal_ready()
}

function check_valid() {
    return __test305_ok.pinned && __test305_ok.rubble
}
