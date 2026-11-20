// CF3a-smoke: climate_predator_type mapping + create_herds on killer points.
// Markers:
//   [test-marker] alt_predator_map_ok
//   [test-marker] alt_predator_humid_asp_ok
//   [test-marker] alt_predator_arid_scorpion_ok
//   [test-marker] alt_predator_central_lion_ok

var CLIMATE_CENTRAL = 0
var CLIMATE_NORTHERN = 1
var CLIMATE_DESERT = 2

var __test052_ok = false

function test052_fail(msg) {
    __log_info_native('[test:052] FAIL: ' + msg)
    test_reload_city_session('data/default.map')
    __test_signal_ready()
}

function test052_unpack_tile(packed) {
    if (packed < 0) {
        return null
    }
    return { x: (packed >> 16) & 0xffff, y: packed & 0xffff }
}

function test052_expect_predator(climate, alt, want_type, label) {
    __test_set_scenario_climate(climate)
    scenario.alt_predator_type = !!alt
    var got = __test_climate_predator_type()
    if (got != want_type) {
        test052_fail(label + ': want type ' + want_type + ', got ' + got)
        return false
    }
    return true
}

function test052_spawn_predator(climate, alt, predator_type, marker) {
    __test_set_scenario_climate(climate)
    scenario.alt_predator_type = !!alt

    city.remove_animals()
    __test_clear_scenario_prey_points()
    __test_clear_scenario_herd_points()

    var packed = __test_find_accessible_herd_tile(predator_type)
    var land = test052_unpack_tile(packed)
    if (!land) {
        test052_fail(marker + ': no accessible herd tile for type ' + predator_type)
        return false
    }

    // Prey points gate Cleopatra split path (prey on prey pts, predator on killer pts).
    __test_set_scenario_prey_point(0, land.x, land.y)
    __test_set_scenario_herd_point(0, land.x, land.y)
    __test_create_herds()

    var n = __test_count_figures(predator_type)
    if (n <= 0) {
        test052_fail(marker + ': create_herds spawned 0 of type ' + predator_type
            + ' at (' + land.x + ',' + land.y + ')')
        return false
    }
    __log_marker(marker)
    return true
}

function run_test() {
    __log_info_native('[test:052] alt_predator climate pairs + create_herds (CF3a-smoke)')
    test_reload_city_session('data/default.map')

    // Mapping table (deterministic; no terrain).
    if (!test052_expect_predator(CLIMATE_NORTHERN, true, FIGURE_ASP, 'humid+alt')) return
    if (!test052_expect_predator(CLIMATE_NORTHERN, false, FIGURE_HIPPO, 'humid+base')) return
    if (!test052_expect_predator(CLIMATE_DESERT, true, FIGURE_SCORPION, 'arid+alt')) return
    if (!test052_expect_predator(CLIMATE_DESERT, false, FIGURE_HYENA, 'arid+base')) return
    if (!test052_expect_predator(CLIMATE_CENTRAL, true, FIGURE_LION, 'central+alt')) return
    if (!test052_expect_predator(CLIMATE_CENTRAL, false, FIGURE_CROCODILE, 'central+base')) return
    __log_marker('alt_predator_map_ok')

    // Integration: create_herds puts alt predators on killer points.
    if (!test052_spawn_predator(CLIMATE_NORTHERN, true, FIGURE_ASP, 'alt_predator_humid_asp_ok')) return
    if (!test052_spawn_predator(CLIMATE_DESERT, true, FIGURE_SCORPION, 'alt_predator_arid_scorpion_ok')) return
    if (!test052_spawn_predator(CLIMATE_CENTRAL, true, FIGURE_LION, 'alt_predator_central_lion_ok')) return

    city.remove_animals()
    __test_clear_scenario_prey_points()
    __test_clear_scenario_herd_points()
    test_reload_city_session('data/default.map')

    __test052_ok = true
    __log_info_native('[test:052] PASS')
    __test_signal_ready()
}

function check_valid() {
    if (!__test052_ok) {
        __log_info_native('[test:052] run_test did not complete')
        return false
    }
    var markers = [
        'alt_predator_map_ok',
        'alt_predator_humid_asp_ok',
        'alt_predator_arid_scorpion_ok',
        'alt_predator_central_lion_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:052] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}
