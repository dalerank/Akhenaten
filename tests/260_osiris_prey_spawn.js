// OG formation_herd_update: Osiris temple complex + oracle halves prey respawn delay (4 → 2).
// Markers:
//   [test-marker] prey_spawn_delay_base
//   [test-marker] prey_spawn_delay_osiris

var __test260_ok = false

function test260_fail(msg) {
    __log_info_native('[test:260] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:260] Osiris prey spawn delay')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    if (__test_prey_respawn_delay() != 4) {
        return test260_fail('base delay want 4, got ' + __test_prey_respawn_delay())
    }
    __log_marker('prey_spawn_delay_base')

    __scenario_building_allow(BUILDING_TEMPLE_COMPLEX_OSIRIS, true)
    var cid = test_building_place(BUILDING_TEMPLE_COMPLEX_OSIRIS, -1, -1)
    if (!cid) {
        var cx = (__scenario_map.width / 2) | 0
        var cy = (__scenario_map.height / 2) | 0
        cid = __test_building_create(BUILDING_TEMPLE_COMPLEX_OSIRIS, cx + 12, cy + 12)
    }
    var complex = city.get_temple_complex()
    if (!complex && cid) {
        complex = new TempleComplex(cid)
    }
    if (!cid || !complex || complex.type != BUILDING_TEMPLE_COMPLEX_OSIRIS) {
        return test260_fail('osiris complex place failed id=' + cid)
    }
    if (__test_prey_respawn_delay() != 4) {
        return test260_fail('complex without oracle must keep delay 4, got ' + __test_prey_respawn_delay())
    }

    complex.temple_complex_upgrades = TEMPLE_COMPLEX_UPGRADE_ORACLE
    if (__test_prey_respawn_delay() != 2) {
        return test260_fail('osiris oracle delay want 2, got ' + __test_prey_respawn_delay())
    }
    __log_marker('prey_spawn_delay_osiris')

    __test260_ok = true
    __log_info_native('[test:260] PASS')
    __test_signal_ready()
}

function check_valid() {
    if (!__test260_ok) {
        __log_info_native('[test:260] run_test did not complete')
        return false
    }
    if (!__test_find_inlog('[test-marker] prey_spawn_delay_base')
        || !__test_find_inlog('[test-marker] prey_spawn_delay_osiris')) {
        __log_info_native('[test:260] missing marker')
        return false
    }
    return true
}
