// OG invasion.c point selection:
//   invasion_land_point (217-235): random1_7bit & 1/3/7 by point count, no RNG step, scan forward.
//   invasion_sea_point (114-126): deterministic forward scan, wrapping.
//   invasion_start_sea landing (182-185): random_generate_next(); random1_15bit % landings.

var __test300_ok = false

function test300_fail(msg) {
    __log_info_native('[test:300] FAIL: ' + msg)
    __test_signal_ready()
}

// OG random_generate_next on iv1 only (31-bit LFSR, tap bits 0 and 4).
function test300_next_iv1(iv1) {
    for (var i = 0; i < 31; i++) {
        var r1 = (((iv1 & 0x10) >> 4) ^ iv1) & 1
        iv1 = iv1 >>> 1
        if (r1) {
            iv1 = iv1 | 0x40000000
        }
    }
    return iv1
}

function test300_expected_land(valid, r) {
    var points = 0
    for (var i = 0; i < 8; i++) {
        if (valid[i]) {
            points++
        }
    }
    var index = (points <= 2) ? (r & 1) : (points <= 4) ? (r & 3) : (r & 7)
    for (var tries = 0; tries < 8; tries++) {
        if (valid[index]) {
            break
        }
        if (++index >= 8) {
            index = 0
        }
    }
    return index
}

function test300_land_case(slots) {
    __test_invasion_points_clear()
    var valid = [false, false, false, false, false, false, false, false]
    for (var i = 0; i < slots.length; i++) {
        __test_invasion_land_point_set(slots[i], 10 + slots[i], 10)
        valid[slots[i]] = true
    }
    for (var iv1 = 0; iv1 < 128; iv1++) {
        __test_rng_set(iv1 + 0x1000, 0x2345)
        var before = __test_rng_short()
        var got = __test_invasion_land_point_index()
        var expected = test300_expected_land(valid, iv1)
        if (got != expected) {
            return 'slots ' + slots.join(',') + ' r=' + iv1 + ' expected ' + expected + ' got ' + got
        }
        if (__test_rng_short() != before) {
            return 'land point pick advanced the RNG (slots ' + slots.join(',') + ')'
        }
    }
    return ''
}

function run_test() {
    __log_info_native('[test:300] invasion point OG')
    test_reload_city_session('data/default.map')

    var cases = [[0, 1], [1, 5, 6], [3], [0, 2, 3, 4, 6, 7], [7]]
    for (var c = 0; c < cases.length; c++) {
        var err = test300_land_case(cases[c])
        if (err) {
            return test300_fail(err)
        }
    }
    __log_marker('test300_land_point_ok')

    __test_invasion_points_clear()
    __test_invasion_sea_point_set(3, 20, 20)
    __test_invasion_sea_point_set(6, 22, 20)
    var sea_expected = [3, 3, 3, 3, 6, 6, 6, 3]
    for (var s = 0; s < 8; s++) {
        __test_rng_set(0x1234 + s, 0x5678)
        var sea_before = __test_rng_short()
        var sea_got = __test_invasion_sea_point_index(s)
        if (sea_got != sea_expected[s]) {
            return test300_fail('sea start ' + s + ' expected ' + sea_expected[s] + ' got ' + sea_got)
        }
        if (__test_rng_short() != sea_before) {
            return test300_fail('sea point pick touched the RNG')
        }
    }
    __log_marker('test300_sea_point_ok')

    __test_invasion_points_clear()
    __test_rng_set(0x1357, 0x2468)
    if (__test_invasion_landing_index() != -1 || __test_rng_short() != 0x1357) {
        return test300_fail('landing roll without disembark points must return -1 and keep the RNG')
    }
    __test_disembark_point_add(10, 10)
    __test_disembark_point_add(-1, -1)
    __test_disembark_point_add(12, 10)
    __test_disembark_point_add(14, 10)
    var valid_slots = [0, 2, 3]
    for (var k = 0; k < 64; k++) {
        var seed = 0x10001 + k * 7919
        __test_rng_set(seed, 0x2468)
        var next = test300_next_iv1(seed)
        var landing_expected = valid_slots[(next & 0x7fff) % 3]
        var landing_got = __test_invasion_landing_index()
        if (landing_got != landing_expected) {
            return test300_fail('landing seed ' + seed + ' expected ' + landing_expected + ' got ' + landing_got)
        }
        if (__test_rng_short() != (next & 0x7fff)) {
            return test300_fail('landing roll must advance the RNG exactly once')
        }
    }
    __log_marker('test300_landing_roll_ok')

    __test_invasion_points_clear()
    var off0 = __test_invasion_land_point_place_open(0)
    var off1 = __test_invasion_land_point_place_open(1)
    __test_rng_set(0x1001, 0x2468)
    var spawn1 = __test_start_land_invasion(ENEMY_0_BARBARIAN, 8)
    __test_rng_set(0x1000, 0x2468)
    var spawn0 = __test_start_land_invasion(ENEMY_0_BARBARIAN, 8)
    if (spawn1 != off1 || spawn0 != off0) {
        return test300_fail('land invasion spawn: expected ' + off1 + '/' + off0 + ' got ' + spawn1 + '/' + spawn0)
    }
    __log_marker('test300_land_invasion_spawn_ok')

    __test300_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test300_ok
        && __test_find_inlog('[test-marker] test300_land_point_ok')
        && __test_find_inlog('[test-marker] test300_sea_point_ok')
        && __test_find_inlog('[test-marker] test300_landing_roll_ok')
        && __test_find_inlog('[test-marker] test300_land_invasion_spawn_ok')
}
