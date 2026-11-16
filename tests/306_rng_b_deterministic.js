// Bucket-B randomness: no libc rand() in sim choices.
// random_hash is stateless; herd size is the OG climate record's max_figures (scenario_climate.c).
// Markers:
//   [test-marker] rng_b_hash_ok
//   [test-marker] rng_b_herd_asp_ok
//   [test-marker] rng_b_herd_scorpion_ok
//   [test-marker] rng_b_herd_lion_ok

var CLIMATE_CENTRAL = 0
var CLIMATE_NORTHERN = 1
var CLIMATE_DESERT = 2

var __test306_ok = false

function test306_fail(msg) {
    __log_info_native('[test:306] FAIL: ' + msg)
    test_reload_city_session('data/default.map')
    __test_signal_ready()
}

function test306_check_hash() {
    var a = __random_hash(1234, 56, 0x1001)
    var b = __random_hash(1234, 56, 0x1001)
    if (a != b) {
        test306_fail('random_hash not stable: ' + a + ' vs ' + b)
        return false
    }
    if (a < 0) {
        test306_fail('random_hash negative: ' + a)
        return false
    }
    var distinct = 0
    for (var i = 0; i < 16; i++) {
        if (__random_hash(1234, 56, 0x1001 + i) != a) {
            distinct++
        }
    }
    if (distinct < 14) {
        test306_fail('random_hash ignores salt: distinct=' + distinct)
        return false
    }
    var buckets = [0, 0, 0, 0]
    for (var t = 0; t < 400; t++) {
        buckets[__random_hash(t, 7, 0x1002) % 4]++
    }
    for (var k = 0; k < 4; k++) {
        if (buckets[k] < 60) {
            test306_fail('random_hash skewed: bucket ' + k + ' = ' + buckets[k])
            return false
        }
    }
    __log_marker('rng_b_hash_ok')
    return true
}

function test306_unpack_tile(packed) {
    if (packed < 0) {
        return null
    }
    return { x: (packed >> 16) & 0xffff, y: packed & 0xffff }
}

function test306_spawn_count(climate, predator_type) {
    __test_set_scenario_climate(climate)
    scenario.alt_predator_type = true

    city.remove_animals()
    __test_clear_scenario_prey_points()
    __test_clear_scenario_herd_points()

    var land = test306_unpack_tile(__test_find_accessible_herd_tile(predator_type))
    if (!land) {
        return -1
    }
    __test_set_scenario_prey_point(0, land.x, land.y)
    __test_set_scenario_herd_point(0, land.x, land.y)
    __test_create_herds()
    return __test_count_figures(predator_type)
}

function test306_expect_herd(climate, predator_type, want, marker) {
    var first = test306_spawn_count(climate, predator_type)
    var second = test306_spawn_count(climate, predator_type)
    if (first != want || second != want) {
        test306_fail(marker + ': type ' + predator_type + ' want ' + want + ', got ' + first + ' then ' + second)
        return false
    }
    __log_marker(marker)
    return true
}

function run_test() {
    __log_info_native('[test:306] bucket-B deterministic choices')
    test_reload_city_session('data/default.map')

    if (!test306_check_hash()) return
    if (!test306_expect_herd(CLIMATE_NORTHERN, FIGURE_ASP, 6, 'rng_b_herd_asp_ok')) return
    if (!test306_expect_herd(CLIMATE_DESERT, FIGURE_SCORPION, 2, 'rng_b_herd_scorpion_ok')) return
    if (!test306_expect_herd(CLIMATE_CENTRAL, FIGURE_LION, 4, 'rng_b_herd_lion_ok')) return

    city.remove_animals()
    __test_clear_scenario_prey_points()
    __test_clear_scenario_herd_points()
    test_reload_city_session('data/default.map')

    __test306_ok = true
    __log_info_native('[test:306] PASS')
    __test_signal_ready()
}

function check_valid() {
    if (!__test306_ok) {
        __log_info_native('[test:306] run_test did not complete')
        return false
    }
    var markers = ['rng_b_hash_ok', 'rng_b_herd_asp_ok', 'rng_b_herd_scorpion_ok', 'rng_b_herd_lion_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:306] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}
