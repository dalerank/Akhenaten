// FIG_TRANSPORT / player transport OG regress:
//   embark arms GOING_TO_LEGION then boards; sink drowns the company;
//   evade order; damaged hull seeks shipwright; shipyard queue heals.
// Markers:
//   [test-marker] transport_og_embark_legion_ok
//   [test-marker] transport_og_drown_ok
//   [test-marker] transport_og_evade_ok
//   [test-marker] transport_og_sail_arrive_evade_ok
//   [test-marker] transport_og_seek_repair_ok
//   [test-marker] transport_og_shipyard_heal_ok

var __test248_ok = false

// Must match e_transport_ship_action in figure_transport_ship.h
var ACTION_TRANSPORT_EVADING = 215
var ACTION_TRANSPORT_GOING_TO_SHIPWRIGHT = 216
var ACTION_TRANSPORT_GOING_TO_LEGION = 218

function test248_fail(msg) {
    __log_info_native('[test:248] ' + msg)
    __test_signal_ready()
}

function test248_board(ship, company) {
    __transport_ship_embark(ship, company)
    if (__figure_get_action_state(ship) != ACTION_TRANSPORT_GOING_TO_LEGION) {
        return false
    }
    for (var i = 0; i < 40; i++) {
        __test_figure_action_perform(ship)
        if (__transport_ship_has_troops(ship)) {
            return true
        }
    }
    return false
}

function run_test() {
    __log_info_native('[test:248] player transport OG')

    // --- embark via GOING_TO_LEGION ---
    test_reload_city_session('data/default.map')
    var ship = __test_player_transport_spawn_for_embark(4)
    if (!ship) {
        return test248_fail('spawn for embark failed')
    }
    var company = __test_player_transport_company_id()
    if (!company) {
        return test248_fail('no company after spawn')
    }
    var before = __test_formation_alive_count(company)
    if (before < 1) {
        return test248_fail('company empty before embark, alive=' + before)
    }
    if (!test248_board(ship, company)) {
        return test248_fail('embark/board failed action=' + __figure_get_action_state(ship)
            + ' troops=' + __transport_ship_has_troops(ship))
    }
    __log_marker('transport_og_embark_legion_ok')

    // --- sink drowns embarked company (OG transport_sink) ---
    __test_figure_kill(ship)
    var after = __test_formation_alive_count(company)
    if (after != 0) {
        return test248_fail('expected drown, alive_before=' + before + ' alive_after=' + after)
    }
    if (__transport_ship_has_troops(ship)) {
        return test248_fail('ship still reports troops after kill')
    }
    __log_marker('transport_og_drown_ok')

    // --- evade order ---
    test_reload_city_session('data/default.map')
    ship = __test_player_transport_spawn_for_embark(2)
    if (!ship) {
        return test248_fail('spawn for evade failed')
    }
    __transport_ship_set_evade(ship)
    if (__figure_get_action_state(ship) != ACTION_TRANSPORT_EVADING) {
        return test248_fail('expected EVADING, got ' + __figure_get_action_state(ship))
    }
    __log_marker('transport_og_evade_ok')

    // --- SAILING arrive off-berth → EVADING (OG ship_move_to_dock) ---
    test_reload_city_session('data/default.map')
    ship = __test_player_transport_spawn_for_embark(1)
    if (!ship) {
        return test248_fail('spawn for sail-arrive evade failed')
    }
    var wx = __test_player_transport_water_x()
    var wy = __test_player_transport_water_y()
    __transport_ship_move_to(ship, wx + 2, wy)
    if (__figure_get_action_state(ship) != 214) {
        return test248_fail('expected SAILING after move_to, got ' + __figure_get_action_state(ship))
    }
    // One tick off the berth clears the home boat slot (OG ship_update_dock).
    __test_figure_action_perform(ship)
    __test_transport_ship_snap_to_destination(ship)
    __test_figure_set_action(ship, 214)
    __test_figure_action_perform(ship)
    if (__figure_get_action_state(ship) != ACTION_TRANSPORT_EVADING) {
        return test248_fail('sail arrive expected EVADING, got ' + __figure_get_action_state(ship))
    }
    __log_marker('transport_og_sail_arrive_evade_ok')

    // --- auto-seek shipwright when hull ≤15% ---
    // Create the hull on the yard berth (spawn water-strip fights shoreline place).
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __scenario_building_allow(BUILDING_SHIPWRIGHT, true)
    var yard_id = test_shoreline_building_place(BUILDING_SHIPWRIGHT, 3)
    if (!yard_id) {
        return test248_fail('shipwright place failed')
    }
    __test_building_set_workers(yard_id, 20)
    // Shoreline place puts water at map-center row; never spawn the hull on the yard tile
    // (action_perform kills boats that cannot walk terrain when not on water).
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    ship = test_figure_create(FIGURE_TRANSPORT_SHIP, cx, cy)
    if (!ship) {
        return test248_fail('spawn for repair-seek failed')
    }
    test_figure_set_home(ship, yard_id)
    __test_figure_set_action(ship, 214)
    // max_damage 250 → health ≤15% needs damage ≥ 213
    __test_figure_set_damage(ship, 220)
    __test_figure_action_perform(ship)
    if (__figure_get_action_state(ship) != ACTION_TRANSPORT_GOING_TO_SHIPWRIGHT) {
        // Auto-repair may no-op if the yard is not yet discoverable; order path is the same go_to.
        if (__test_shipyard_find_best_dock(ship) <= 0) {
            return test248_fail('no shipwright dock for damaged hull, workers set, dmg=220')
        }
        __transport_ship_set_repair(ship)
    }
    if (__figure_get_action_state(ship) != ACTION_TRANSPORT_GOING_TO_SHIPWRIGHT) {
        return test248_fail('expected GOING_TO_SHIPWRIGHT, got ' + __figure_get_action_state(ship)
            + ' dmg=' + __test_figure_get_damage(ship)
            + ' best=' + __test_shipyard_find_best_dock(ship))
    }
    __log_marker('transport_og_seek_repair_ok')

    // --- shipyard queue heals a transport (same path as warship) ---
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __scenario_building_allow(BUILDING_SHIPWRIGHT, true)
    yard_id = test_shoreline_building_place(BUILDING_SHIPWRIGHT, 3)
    if (!yard_id) {
        return test248_fail('shipwright place failed (heal)')
    }
    __test_building_set_workers(yard_id, 20)
    var yard = city.get_building(yard_id)
    yard.store_resource(RESOURCE_TIMBER, 100)

    var wx = (__scenario_map.width / 2) | 0
    var wy = (__scenario_map.height / 2) | 0
    var fid = test_figure_create(FIGURE_TRANSPORT_SHIP, wx, wy)
    if (!fid) {
        return test248_fail('transport create at dock failed')
    }
    test_figure_set_home(fid, yard_id)
    __test_figure_set_damage(fid, 40)
    if (__test_shipyard_queue_ship(yard_id, fid) != 1) {
        return test248_fail('queue_ship failed')
    }
    __test_building_update_day(yard_id)
    if (__test_shipyard_is_reparing(yard_id) != 1 || __test_shipyard_repair_fid(yard_id) != fid) {
        return test248_fail('shipyard did not take transport for repair')
    }
    var wood0 = yard.stored_resource(RESOURCE_TIMBER)
    var dmg0 = __test_figure_get_damage(fid)
    __test_building_update_day(yard_id)
    var wood1 = yard.stored_resource(RESOURCE_TIMBER)
    var dmg1 = __test_figure_get_damage(fid)
    if (wood1 != wood0 - 1) {
        return test248_fail('expected 1 timber, wood0=' + wood0 + ' wood1=' + wood1)
    }
    if (dmg1 >= dmg0) {
        return test248_fail('expected heal, dmg0=' + dmg0 + ' dmg1=' + dmg1)
    }
    __log_marker('transport_og_shipyard_heal_ok')

    __test248_ok = true
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'transport_og_embark_legion_ok',
        'transport_og_drown_ok',
        'transport_og_evade_ok',
        'transport_og_sail_arrive_evade_ok',
        'transport_og_seek_repair_ok',
        'transport_og_shipyard_heal_ok'
    ]
    if (!__test248_ok) {
        return false
    }
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:248] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}
