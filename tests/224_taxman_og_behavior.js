// Tax collector OG fidelity: palace gate + house-only coverage count.
// Markers:
//   [test-marker] taxman_palace_gate_blocks_ok
//   [test-marker] taxman_palace_gate_allows_ok
//   [test-marker] taxman_spawn_blocked_ok
//   [test-marker] taxman_spawn_allowed_ok
//   [test-marker] taxman_coverage_ignores_nonhouse_ok
//   [test-marker] taxman_coverage_counts_house_ok

function run_test() {
    __log_info_native('[test:224] taxman OG behavior')
    test_ensure_city_session('data/default.map')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    __scenario_building_allow(BUILDING_TAX_COLLECTOR, true)
    __scenario_building_allow(BUILDING_VILLAGE_PALACE, true)
    __scenario_building_allow(BUILDING_POTTERY_WORKSHOP, true)
    __scenario_building_allow(BUILDING_HOUSE_CRUDE_HUT, true)

    if (__city_palace_allows_tax_collectors()) {
        __log_info_native('[test:224] unexpected palace already allows taxmen')
        __test_signal_ready()
        return
    }
    __log_marker('taxman_palace_gate_blocks_ok')

    var palace_id = __test_building_create(BUILDING_VILLAGE_PALACE, cx - 12, cy)
    if (!palace_id) {
        __log_info_native('[test:224] palace create failed')
        __test_signal_ready()
        return
    }
    __test_city_buildings_update_tick()
    var palace = city.get_building(palace_id)
    var need = palace.max_workers > 0 ? palace.max_workers : 20
    __test_building_set_workers(palace_id, need)
    __test_city_buildings_update_tick()

    if (__city_get_palace_id() != palace_id) {
        __log_info_native('[test:224] palace_id want ' + palace_id + ' got ' + __city_get_palace_id())
        __test_signal_ready()
        return
    }
    if (!__city_palace_allows_tax_collectors()) {
        __log_info_native('[test:224] staffed palace should allow taxmen')
        __test_signal_ready()
        return
    }
    __log_marker('taxman_palace_gate_allows_ok')

    var office_id = __test_building_create(BUILDING_TAX_COLLECTOR, cx, cy)
    if (!office_id) {
        __log_info_native('[test:224] tax office create failed')
        __test_signal_ready()
        return
    }
    var office = city.get_building(office_id)
    office.houses_covered = 100
    office.has_road_access = true
    __test_building_set_workers(office_id, office.max_workers > 0 ? office.max_workers : 6)

    // Unstaff palace: spawn path must not create a taxman (delay may still reset).
    __test_building_set_workers(palace_id, 0)
    __test_city_buildings_update_tick()
    if (__city_palace_allows_tax_collectors()) {
        __log_info_native('[test:224] unstaffed palace still allows')
        __test_signal_ready()
        return
    }

    office.figure_spawn_delay = 99
    building_tax_office_spawn_taxman(office)
    if (office.has_figure(BUILDING_SLOT_SERVICE)) {
        __log_info_native('[test:224] taxman spawned without palace workers')
        __test_signal_ready()
        return
    }
    __log_marker('taxman_spawn_blocked_ok')

    __test_building_set_workers(palace_id, need)
    __test_city_buildings_update_tick()
    office.figure_spawn_delay = 99
    building_tax_office_spawn_taxman(office)
    if (!office.has_figure(BUILDING_SLOT_SERVICE)) {
        __log_info_native('[test:224] taxman did not spawn with staffed palace')
        __test_signal_ready()
        return
    }
    __log_marker('taxman_spawn_allowed_ok')

    var pot_id = __test_building_create(BUILDING_POTTERY_WORKSHOP, cx + 8, cy)
    var hut_id = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, cx + 8, cy + 8)
    if (!pot_id || !hut_id || __test_house_set_population(hut_id, 20) < 1) {
        __log_info_native('[test:224] pot/hut setup failed')
        __test_signal_ready()
        return
    }

    var tax_at_pot = test_figure_create(FIGURE_TAX_COLLECTOR, cx + 8, cy)
    __test_figure_set_home(tax_at_pot, office_id)
    var only_nonhouse = __test_figure_provide_service(tax_at_pot)
    if (only_nonhouse !== 0) {
        __log_info_native('[test:224] non-house tiles counted as ' + only_nonhouse)
        __test_signal_ready()
        return
    }
    __log_marker('taxman_coverage_ignores_nonhouse_ok')

    var tax_at_hut = test_figure_create(FIGURE_TAX_COLLECTOR, cx + 8, cy + 8)
    __test_figure_set_home(tax_at_hut, office_id)
    var with_house = __test_figure_provide_service(tax_at_hut)
    if (with_house < 1) {
        __log_info_native('[test:224] inhabited hut not counted, got ' + with_house)
        __test_signal_ready()
        return
    }
    __log_marker('taxman_coverage_counts_house_ok')

    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] taxman_palace_gate_blocks_ok')
        && __test_find_inlog('[test-marker] taxman_palace_gate_allows_ok')
        && __test_find_inlog('[test-marker] taxman_spawn_blocked_ok')
        && __test_find_inlog('[test-marker] taxman_spawn_allowed_ok')
        && __test_find_inlog('[test-marker] taxman_coverage_ignores_nonhouse_ok')
        && __test_find_inlog('[test-marker] taxman_coverage_counts_house_ok')
}
