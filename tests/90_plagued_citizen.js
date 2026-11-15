// FIGURE_PLAGUED_CITIZEN register + spawn + Bast/plague_start + herbalist cure (OG same-tile meeting).
// Markers:
//   [test-marker] plagued_registered_ok
//   [test-marker] plagued_outbreak_spawn_ok
//   [test-marker] plagued_bast_curse_spawn_ok
//   [test-marker] plagued_herbalist_cure_ok
//   [test-marker] plagued_plague_no_clears_ok

var GOD_BAST = 4

function test90_count_plagued() {
    return __test_count_figures(FIGURE_PLAGUED_CITIZEN)
}

function test90_remove_plagued() {
    city.figures.remove_figures(FIGURE_PLAGUED_CITIZEN)
}

function test90_setup_sick_house() {
    var bid = test_building_place(BUILDING_HOUSE_CRUDE_HUT, -1, -1)
    if (!bid) {
        bid = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, -1, -1)
    }
    if (!bid) {
        return 0
    }
    var pop = __test_house_set_population(bid, 40)
    if (pop < 1) {
        __log_info_native('[test:90] house population set failed, got ' + pop)
        return 0
    }
    var b = city.get_building(bid)
    if (b) {
        b.common_health = 5
    }
    // OG: the carrier leaves the house tile for a road within 2 tiles.
    var ht = __building_tile(bid)
    for (var dx = 0; dx < 2; dx++) {
        terrain.add({ x: ht.x + dx, y: ht.y + 1 }, TERRAIN_ROAD)
    }
    __test_update_road_network()
    __test_check_kingdome_access()
    return bid
}

function run_test() {
    __log_info_native('[test:90] plagued citizen CF4')
    test_ensure_city_session('data/default.map')
    __test_set_treasury(50000)
    game.paused = false
    test90_remove_plagued()

    // --- Register ---
    var probe = test_figure_create(FIGURE_PLAGUED_CITIZEN, -1, -1)
    if (!probe || !__figure_is_valid(probe) || __figure_get_type(probe) != FIGURE_PLAGUED_CITIZEN) {
        __log_info_native('[test:90] FIGURE_PLAGUED_CITIZEN not registered')
        __test_signal_ready()
        return
    }
    __test_figure_kill(probe)
    __log_marker('plagued_registered_ok')

    // --- create_at_house (same helper start_disease uses) ---
    test90_remove_plagued()
    var hid = test90_setup_sick_house()
    if (!hid) {
        __log_info_native('[test:90] failed to create sick house')
        __test_signal_ready()
        return
    }
    var fid = __test_plagued_create_at_house(hid)
    if (!fid || !__figure_is_valid(fid) || __figure_get_type(fid) != FIGURE_PLAGUED_CITIZEN) {
        __log_info_native('[test:90] create_at_house failed, fid=' + fid)
        __test_signal_ready()
        return
    }
    if (test90_count_plagued() < 1) {
        __log_info_native('[test:90] no live plagued after create_at_house')
        __test_signal_ready()
        return
    }
    __log_marker('plagued_outbreak_spawn_ok')

    // --- Bast minor curse / plague_start ---
    test_reload_city_session('data/default.map')
    __test_set_treasury(50000)
    game.paused = false
    test90_remove_plagued()
    hid = test90_setup_sick_house()
    if (!hid) {
        __log_info_native('[test:90] bast setup house failed')
        __test_signal_ready()
        return
    }
    __test_run_console_command('god_minor_curse ' + GOD_BAST)
    if (test90_count_plagued() < 1) {
        __test_run_console_command('plague_start 40')
    }
    if (test90_count_plagued() < 1) {
        __log_info_native('[test:90] Bast/plague_start expected plagued walkers, got ' + test90_count_plagued())
        __test_signal_ready()
        return
    }
    __log_marker('plagued_bast_curse_spawn_ok')

    // --- Herbalist stepping on the carrier's tile removes it ---
    test90_remove_plagued()
    var land = test_find_buildable_tile(BUILDING_HOUSE_CRUDE_HUT)
    if (!land) {
        land = { x: 40, y: 40 }
    }
    var plagued = test_figure_create(FIGURE_PLAGUED_CITIZEN, land.x, land.y)
    var herbalist = test_figure_create(FIGURE_HERBALIST, land.x, land.y)
    if (!plagued || !herbalist) {
        __log_info_native('[test:90] herbalist/plagued spawn failed')
        __test_signal_ready()
        return
    }
    __test_figure_combat_attack_at(herbalist, land.x, land.y)
    if (test90_count_plagued() != 0) {
        __log_info_native('[test:90] herbalist meeting failed, left ' + test90_count_plagued())
        __test_signal_ready()
        return
    }
    __log_marker('plagued_herbalist_cure_ok')

    // --- plague_no clears walkers ---
    test_figure_create(FIGURE_PLAGUED_CITIZEN, land.x, land.y)
    if (test90_count_plagued() < 1) {
        __log_info_native('[test:90] pre plague_no spawn failed')
        __test_signal_ready()
        return
    }
    __test_run_console_command('plague_no')
    if (test90_count_plagued() != 0) {
        __log_info_native('[test:90] plague_no should remove walkers, got ' + test90_count_plagued())
        __test_signal_ready()
        return
    }
    __log_marker('plagued_plague_no_clears_ok')

    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'plagued_registered_ok',
        'plagued_outbreak_spawn_ok',
        'plagued_bast_curse_spawn_ok',
        'plagued_herbalist_cure_ok',
        'plagued_plague_no_clears_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            return false
        }
    }
    return true
}
