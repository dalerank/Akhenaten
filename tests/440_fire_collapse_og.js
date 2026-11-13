// OG building_maintenance.c building_maintenance_check_fire_collapse:
//   one LFSR step picks the day (random1_3bit); every checked building that does not collapse
//   draws another step, factor = random1_15bit % 5 + 1, and on its day fire_risk += increment * factor;
//   desert adds 3, an empty house resets fire_risk; huts and floodplain keep damage at 0;
//   collapse and fire trigger at >= 1000; only the main part is checked.
// A per-difficulty fire_risk table (apothecary) is not scaled again by difficulty_multiply_risk.
// Markers:
//   [test-marker] fire_collapse_factor_ok
//   [test-marker] fire_collapse_desert_ok
//   [test-marker] fire_collapse_empty_house_ok
//   [test-marker] fire_collapse_damage_ok

var __test440_ok = false
var __test440_diff_prev = -1
var __test440_climate_prev = -1

var TEST440_HARD = 3
var TEST440_CLIMATE_CENTRAL = 0
var TEST440_CLIMATE_DESERT = 2
var TEST440_RISK_MULTIPLIER_HARD = 1.2

function test440_set_difficulty(d) {
    var guard = 0
    while (__game_difficulty() < d && guard++ < 10) {
        __game_increase_difficulty()
    }
    while (__game_difficulty() > d && guard++ < 20) {
        __game_decrease_difficulty()
    }
    return __game_difficulty() == d
}

function test440_restore() {
    if (__test440_climate_prev >= 0) {
        __test_set_scenario_climate(__test440_climate_prev)
    }
    if (__test440_diff_prev >= 0) {
        test440_set_difficulty(__test440_diff_prev)
    }
}

function test440_fail(msg) {
    __log_info_native('[test:440] FAIL: ' + msg)
    test440_restore()
    __test_signal_ready()
}

// Seed whose first step gives `day` and whose second step gives `factor` (0 = any factor).
function test440_find_seed(day, factor) {
    var i
    for (i = 1; i < 20000; i++) {
        var iv1 = (0x1234 + i * 7919) | 0
        var iv2 = (0x4321 + i * 104729) | 0
        __test_random_set_state(iv1, iv2)
        __test_random_generate_next()
        var d = __test_random_1_3bit()
        __test_random_generate_next()
        var f = (__test_random_1_15bit() % 5) + 1
        if (d == day && (factor == 0 || f == factor)) {
            return { iv1: iv1, iv2: iv2, factor: f }
        }
    }
    return null
}

function test440_building_day(bid, x, y) {
    return (bid + __test_map_random_at(x, y)) & 7
}

function test440_run_check(seed) {
    __test_random_set_state(seed.iv1, seed.iv2)
    __test_city_check_building_destroying()
}

function test440_session() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __test_set_scenario_climate(TEST440_CLIMATE_CENTRAL)
}

function test440_factor_phase(cx, cy) {
    test440_session()
    var bid = __test_building_create(BUILDING_APOTHECARY, cx, cy)
    if (!bid) {
        return 'create apothecary failed'
    }
    var b = city.get_building(bid)
    b.fire_risk = 0
    b.collapse_risk = 0

    var increment = building_apothecary.fire_risk[TEST440_HARD]
    var day = test440_building_day(bid, cx, cy)
    var factors = [1, 5]
    var k
    for (k = 0; k < factors.length; k++) {
        var seed = test440_find_seed(day, factors[k])
        if (!seed) {
            return 'no seed for factor ' + factors[k]
        }
        b.fire_risk = 0
        test440_run_check(seed)
        if ((b.fire_risk | 0) != increment * factors[k]) {
            return 'factor ' + factors[k] + ': fire_risk want ' + (increment * factors[k]) + ' got ' + b.fire_risk
        }
    }

    var other = test440_find_seed((day + 1) & 7, 0)
    b.fire_risk = 0
    test440_run_check(other)
    if ((b.fire_risk | 0) != 0) {
        return 'off-day must not add fire risk, got ' + b.fire_risk
    }

    var burn = test440_find_seed(day, 3)
    b.fire_risk = 1000 - increment * 3
    test440_run_check(burn)
    if (__building_type(bid) == BUILDING_APOTHECARY) {
        return 'fire_risk reaching exactly 1000 must burn the building'
    }
    __log_marker('fire_collapse_factor_ok')
    return ''
}

function test440_desert_phase(cx, cy) {
    test440_session()
    __test_set_scenario_climate(TEST440_CLIMATE_DESERT)
    var bid = __test_building_create(BUILDING_APOTHECARY, cx, cy)
    if (!bid) {
        return 'create desert apothecary failed'
    }
    var b = city.get_building(bid)
    b.fire_risk = 0
    b.collapse_risk = 0
    var increment = building_apothecary.fire_risk[TEST440_HARD]
    var seed = test440_find_seed(test440_building_day(bid, cx, cy), 2)
    test440_run_check(seed)
    __test_set_scenario_climate(TEST440_CLIMATE_CENTRAL)
    if ((b.fire_risk | 0) != 3 + increment * 2) {
        return 'desert fire_risk want ' + (3 + increment * 2) + ' got ' + b.fire_risk
    }
    __log_marker('fire_collapse_desert_ok')
    return ''
}

function test440_empty_house_phase(cx, cy) {
    test440_session()
    var hut = __test_building_create(BUILDING_HOUSE_MEAGER_SHANTY, cx, cy)
    if (!hut) {
        return 'create shanty failed'
    }
    __test_house_set_population(hut, 0)
    var b = city.get_building(hut)
    b.fire_risk = 300
    var seed = test440_find_seed(test440_building_day(hut, cx, cy), 0)
    test440_run_check(seed)
    if ((b.fire_risk | 0) != 0) {
        return 'empty house fire_risk want 0 got ' + b.fire_risk
    }
    __log_marker('fire_collapse_empty_house_ok')
    return ''
}

function test440_bazaar(x, y, collapse_risk) {
    var bid = __test_building_create(BUILDING_BAZAAR, x, y)
    if (!bid) {
        return 0
    }
    var b = city.get_building(bid)
    b.fire_risk = 0
    b.collapse_risk = collapse_risk
    return bid
}

function test440_damage_phase(cx, cy) {
    test440_session()
    var increment = Math.floor(TEST440_RISK_MULTIPLIER_HARD * building_bazaar.damage_risk[0])
    if (increment <= 0) {
        return 'bazaar damage increment is 0 on hard'
    }

    var at_max = test440_bazaar(cx, cy, 1000 - increment)
    var below = test440_bazaar(cx + 4, cy, 999 - increment)
    var plain = test440_bazaar(cx + 8, cy, 500)
    var flood = test440_bazaar(cx, cy + 4, 500)
    var part = test440_bazaar(cx + 4, cy + 4, 999)
    var crude = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, cx + 8, cy + 4)
    var sturdy = __test_building_create(BUILDING_HOUSE_STURDY_HUT, cx + 9, cy + 4)
    if (!at_max || !below || !plain || !flood || !part || !crude || !sturdy) {
        return 'create damage buildings failed'
    }
    terrain.add({ x: cx, y: cy + 4 }, TERRAIN_FLOODPLAIN)
    city.get_building(part).prev_part_building_id = below
    city.get_building(crude).collapse_risk = 500
    city.get_building(sturdy).collapse_risk = 500

    __test_random_set_state(0x1357, 0x2468)
    __test_city_check_building_destroying()
    city.get_building(part).prev_part_building_id = 0
    terrain.remove({ x: cx, y: cy + 4 }, TERRAIN_FLOODPLAIN)

    if (!__test_building_is_rubble(at_max)) {
        return 'collapse_risk reaching exactly 1000 must collapse'
    }
    if (__test_building_is_rubble(below) || (city.get_building(below).collapse_risk | 0) != 999) {
        return 'collapse_risk 999 must stand, got ' + city.get_building(below).collapse_risk
    }
    if ((city.get_building(plain).collapse_risk | 0) != 500 + increment) {
        return 'plain damage want ' + (500 + increment) + ' got ' + city.get_building(plain).collapse_risk
    }
    if ((city.get_building(flood).collapse_risk | 0) != 0) {
        return 'floodplain damage want 0 got ' + city.get_building(flood).collapse_risk
    }
    if (__test_building_is_rubble(part) || (city.get_building(part).collapse_risk | 0) != 999) {
        return 'non-main part must not be checked, collapse_risk ' + city.get_building(part).collapse_risk
    }
    if ((city.get_building(crude).collapse_risk | 0) != 0 || (city.get_building(sturdy).collapse_risk | 0) != 0) {
        return 'huts damage want 0 got crude=' + city.get_building(crude).collapse_risk
            + ' sturdy=' + city.get_building(sturdy).collapse_risk
    }
    __log_marker('fire_collapse_damage_ok')
    return ''
}

function run_test() {
    __log_info_native('[test:440] OG fire and collapse risk')
    test_reload_city_session('data/default.map')
    __test440_diff_prev = __game_difficulty()
    __test440_climate_prev = __test_get_scenario_climate()
    if (!test440_set_difficulty(TEST440_HARD)) {
        return test440_fail('cannot switch to hard difficulty')
    }

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var phases = [test440_factor_phase, test440_desert_phase, test440_empty_house_phase, test440_damage_phase]
    var i
    for (i = 0; i < phases.length; i++) {
        var err = phases[i](cx, cy)
        if (err) {
            return test440_fail(err)
        }
    }

    test440_restore()
    __test440_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test440_ok
        && __test_find_inlog('[test-marker] fire_collapse_factor_ok')
        && __test_find_inlog('[test-marker] fire_collapse_desert_ok')
        && __test_find_inlog('[test-marker] fire_collapse_empty_house_ok')
        && __test_find_inlog('[test-marker] fire_collapse_damage_ok')
}
