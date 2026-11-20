// OG temple spawn_temple delays {3,7,10,15,20} and religion coverage people
// (local temple 750 / patron temple 375; shrines 300 / 150).
// Markers:
//   [test-marker] temple_og_spawn_delay_ok
//   [test-marker] temple_og_coverage_local_ok
//   [test-marker] temple_og_coverage_patron_ok

var __test175_spawn_ok = false
var __test175_local_ok = false
var __test175_patron_ok = false

function test175_fail(msg) {
    __log_info_native('[test:175] ' + msg)
}

function test175_spawn(bid) {
    building_temple_osiris_spawn_figure({ bid: bid })
    return __test_count_figures(FIGURE_PRIEST)
}

function test175_check_spawn_delay() {
    var bid = test_building_place(BUILDING_TEMPLE_OSIRIS, -1, -1)
    if (!bid) {
        test175_fail('place temple failed')
        return false
    }

    var zt = __building_tile(bid)
    for (var dx = 0; dx < 5; dx++) {
        terrain.add({ x: zt.x + dx, y: zt.y + 3 }, TERRAIN_ROAD)
    }
    __test_update_road_network()
    __test_check_kingdome_access()

    __test_building_set_workers(bid, 8)
    var b = city.get_building(bid)
    b.has_road_access = true
    b.figure_spawn_delay = 0
    city.figures.remove_figures(FIGURE_PRIEST)

    for (var d = 1; d <= 3; d++) {
        if (test175_spawn(bid) > 0) {
            test175_fail('priest spawned too early at day ' + d)
            return false
        }
    }
    if (test175_spawn(bid) < 1) {
        test175_fail('priest expected on day 4 at 100% workers')
        return false
    }
    if (city.get_building(bid).figure_spawn_delay != 0) {
        test175_fail('day counter must reset after spawn')
        return false
    }
    return true
}

function test175_check_coverage() {
    city.figures.remove_figures(FIGURE_PRIEST)
    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)

    var temple = __test_building_create(BUILDING_TEMPLE_OSIRIS, -1, -1)
    if (!temple) {
        test175_fail('create temple for coverage failed')
        return false
    }
    __test_building_set_workers(temple, 8)

    // GOD_STATUS_KNOWN=1 (OG LOCAL), GOD_STATUS_PATRON=2
    __test_set_god_status(GOD_OSIRIS, 1)
    var local_cov = __test_god_coverage_total(GOD_OSIRIS)
    if (local_cov != 750) {
        test175_fail('local/known temple coverage want 750 got ' + local_cov)
        return false
    }
    __test175_local_ok = true
    __log_marker('temple_og_coverage_local_ok')

    __test_set_god_status(GOD_OSIRIS, 2)
    var patron_cov = __test_god_coverage_total(GOD_OSIRIS)
    if (patron_cov != 375) {
        test175_fail('patron temple coverage want 375 got ' + patron_cov)
        return false
    }
    __test175_patron_ok = true
    __log_marker('temple_og_coverage_patron_ok')
    return true
}

function run_test() {
    __log_info_native('[test:175] temple OG spawn + coverage')
    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)

    if (!test175_check_spawn_delay()) {
        __test_signal_ready()
        return
    }
    __test175_spawn_ok = true
    __log_marker('temple_og_spawn_delay_ok')

    if (!test175_check_coverage()) {
        __test_signal_ready()
        return
    }

    __test_signal_ready()
}

function check_valid() {
    return __test175_spawn_ok
        && __test175_local_ok
        && __test175_patron_ok
        && __test_find_inlog('[test-marker] temple_og_spawn_delay_ok')
        && __test_find_inlog('[test-marker] temple_og_coverage_local_ok')
        && __test_find_inlog('[test-marker] temple_og_coverage_patron_ok')
}
