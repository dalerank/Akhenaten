// Hunting lodge default hunter type by climate / prey points (AH3).
// Markers:
//   [test-marker] hunter_climate_resolve_ok

var __test74_ok = false

// e_climate: CENTRAL=0, NORTHERN=1, DESERT=2
var CLIMATE_CENTRAL = 0
var CLIMATE_NORTHERN = 1
var CLIMATE_DESERT = 2

function test74_fail(msg) {
    __log_info_native('[test:74] FAIL: ' + msg)
    // Always reload — climate/prey mutations must not leak into later tests.
    test_reload_city_session('data/default.map')
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:74] hunting lodge climate → hunter type')
    test_ensure_city_session('data/default.map')

    // Prey points present: climate prey → hunter.
    __test_set_scenario_prey_point(0, 20, 20)

    __test_set_scenario_climate(CLIMATE_CENTRAL)
    if (hunting_lodge_resolve_hunter_type() != FIGURE_ANTELOPE_HUNTER) {
        test74_fail('Central+prey → antelope hunter, got '
            + hunting_lodge_resolve_hunter_type())
        return
    }

    __test_set_scenario_climate(CLIMATE_DESERT)
    if (hunting_lodge_resolve_hunter_type() != FIGURE_OSTRICH_HUNTER) {
        test74_fail('Desert+prey → ostrich hunter, got '
            + hunting_lodge_resolve_hunter_type())
        return
    }

    __test_set_scenario_climate(CLIMATE_NORTHERN)
    // Birds hunter leaf: Northern+prey → birds hunter.
    if (hunting_lodge_resolve_hunter_type() != FIGURE_BIRDS_HUNTER) {
        test74_fail('Northern+prey → birds hunter, got '
            + hunting_lodge_resolve_hunter_type())
        return
    }

    // Legacy (no prey points): Central → antelope; Northern crocodile → ostrich interim.
    __test_clear_scenario_prey_points()

    __test_set_scenario_climate(CLIMATE_CENTRAL)
    if (hunting_lodge_resolve_hunter_type() != FIGURE_ANTELOPE_HUNTER) {
        test74_fail('Central+legacy → antelope hunter, got '
            + hunting_lodge_resolve_hunter_type())
        return
    }

    __test_set_scenario_climate(CLIMATE_NORTHERN)
    if (hunting_lodge_resolve_hunter_type() != FIGURE_OSTRICH_HUNTER) {
        test74_fail('Northern+legacy → ostrich interim, got '
            + hunting_lodge_resolve_hunter_type())
        return
    }

    // Reload so prey-point / climate mutations do not leak into later tests.
    test_reload_city_session('data/default.map')
    __log_marker('hunter_climate_resolve_ok')
    __test74_ok = true
    __log_info_native('[test:74] PASS')
    __test_signal_ready()
}

function check_valid() {
    if (!__test74_ok) {
        __log_info_native('[test:74] run_test did not complete')
        return false
    }
    if (!__test_find_inlog('[test-marker] hunter_climate_resolve_ok')) {
        __log_info_native('[test:74] missing marker: hunter_climate_resolve_ok')
        return false
    }
    return true
}
