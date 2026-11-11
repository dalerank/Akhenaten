// Burning ruins and house image variants vs OG (no crt rand(), all from map_grids.random):
// - ruin burn length: OG fire_duration = (map_random_7bit & 7) + 1, ++ per update, rubble past 32
//   (building_maintenance.c:120,537-541); here fire_duration counts down: 33 - og_duration
// - ruin image variant = map_random & 3 (building_maintenance.c:105) -> anim "fire<variant>"
// - spread check: random_generate_next() only when og_duration & (desert ? 3 : 7) == 0
//   (building_maintenance.c:553-557)
// - house image variant = map_random & (variants - 1) (house_size.c:368-371)
// Markers:
//   [test-marker] ruin_initial_duration_ok
//   [test-marker] ruin_variant_ok
//   [test-marker] ruin_burn_rng_ok
//   [test-marker] house_variant_ok

var RUIN_BURN_DAYS = 32

var __test301_ok = {
    duration: false,
    variant: false,
    burn_rng: false,
    house_variant: false
}

function test301_fail(msg) {
    __log_info_native('[test:301] FAIL: ' + msg)
}

function test301_check_ruins(cx, cy) {
    var duration_ok = true
    var variant_ok = true
    var ruins = []
    for (var i = 0; i < 8; i++) {
        var x = cx - 12 + i * 3
        var y = cy + 10
        var bid = __test_burning_ruin_create(x, y)
        if (!bid) {
            test301_fail('ruin create failed at ' + x + ',' + y)
            return []
        }
        var r = __test_map_random_at(x, y)
        var want_duration = RUIN_BURN_DAYS + 1 - (((r & 0x7f) & 7) + 1)
        var got_duration = __test_building_fire_duration(bid)
        if (got_duration != want_duration) {
            duration_ok = false
            test301_fail('ruin ' + bid + ' random=' + r + ' fire_duration=' + got_duration + ' want=' + want_duration)
        }
        var want_key = 'fire' + (r & 3)
        var got_key = __test_building_anim_key(bid)
        if (got_key != want_key) {
            variant_ok = false
            test301_fail('ruin ' + bid + ' random=' + r + ' anim=' + got_key + ' want=' + want_key)
        }
        ruins.push(bid)
    }

    if (duration_ok) {
        __test301_ok.duration = true
        __log_info_native('[test-marker] ruin_initial_duration_ok')
    }
    if (variant_ok) {
        __test301_ok.variant = true
        __log_info_native('[test-marker] ruin_variant_ok')
    }
    return ruins
}

// Climate-independent: og_duration % 8 == 0 consumes in both climates; % 4 != 0 in neither.
function test301_check_burn(bid) {
    var og_duration = RUIN_BURN_DAYS + 1 - __test_building_fire_duration(bid)
    var updates = 0
    while (og_duration <= RUIN_BURN_DAYS) {
        __test_random_set_state(0x1234567, 0x7654321)
        var iv_before = __test_random_iv1()
        __test_burning_ruin_update(bid)
        updates++
        og_duration++
        var consumed = __test_random_iv1() != iv_before
        if (og_duration > RUIN_BURN_DAYS) {
            if (consumed) {
                test301_fail('rubble step consumed RNG')
                return false
            }
            break
        }
        if (__test_building_fire_duration(bid) != RUIN_BURN_DAYS + 1 - og_duration) {
            test301_fail('fire_duration=' + __test_building_fire_duration(bid) + ' at og_duration=' + og_duration)
            return false
        }
        if ((og_duration & 7) == 0 && !consumed) {
            test301_fail('og_duration=' + og_duration + ' must call random_generate_next')
            return false
        }
        if ((og_duration & 3) != 0 && consumed) {
            test301_fail('og_duration=' + og_duration + ' must not touch RNG')
            return false
        }
        if (updates > 64) {
            test301_fail('ruin never turned to rubble')
            return false
        }
    }
    if (!__test_building_is_rubble(bid) || __test_building_fire_duration(bid) > 0) {
        test301_fail('ruin ' + bid + ' not rubble after ' + updates + ' updates')
        return false
    }
    return true
}

function test301_check_houses(cx, cy) {
    var ok = true
    for (var i = 0; i < 8; i++) {
        var x = cx - 12 + i * 3
        var y = cy - 14
        var bid = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, x, y)
        if (!bid || !__test_house_change_to(bid, BUILDING_HOUSE_STURDY_HUT)) {
            test301_fail('house create/change failed at ' + x + ',' + y)
            return false
        }
        var r = __test_map_random_at(x, y)
        var idx = r & 1
        // Without art both variants have image 0 and change_to falls through to the other one.
        if (__test_house_image_id(bid) <= 0) {
            idx = 1 - idx
        }
        var want_key = '_' + (idx + 1)
        var got_key = __test_house_image_key(bid)
        if (got_key != want_key) {
            ok = false
            test301_fail('house ' + bid + ' random=' + r + ' image_key=' + got_key + ' want=' + want_key)
        }
    }
    return ok
}

function run_test() {
    __log_info_native('[test:301] ruins fire / image variants OG')
    test_reload_city_session('data/default.map')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    var ruins = test301_check_ruins(cx, cy)
    if (ruins.length > 0) {
        var burn_ok = true
        for (var i = 0; i < ruins.length && burn_ok; i++) {
            burn_ok = test301_check_burn(ruins[i])
        }
        if (burn_ok) {
            __test301_ok.burn_rng = true
            __log_info_native('[test-marker] ruin_burn_rng_ok')
        }
    }

    if (test301_check_houses(cx, cy)) {
        __test301_ok.house_variant = true
        __log_info_native('[test-marker] house_variant_ok')
    }

    __test_signal_ready()
}

function check_valid() {
    return __test301_ok.duration
        && __test301_ok.variant
        && __test301_ok.burn_rng
        && __test301_ok.house_variant
}
