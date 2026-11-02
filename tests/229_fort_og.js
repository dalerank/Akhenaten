// Fort OG placement: the parade ground always sits at x+3, y-1 (rotation is a remake feature),
// a blocked parade ground or a full complement of forts refuses the final placement,
// and each new legion takes the lowest free legion index.

var __test229_ok = false

function test229_fail(msg) {
    __log_info_native('[test:229] FAIL: ' + msg)
    test_planner_exit_build_mode()
    city_planner.global_rotation = 0
    __test_signal_ready()
}

function test229_place_fort() {
    var bid = test_building_place(BUILDING_FORT_CHARIOTEERS, -1, -1)
    test_planner_exit_build_mode()
    return bid
}

function run_test() {
    __log_info_native('[test:229] fort OG placement')
    var flags = ['gameplay_change_fort_rotation', 'gameplay_change_fort_refund_carry_troops']
    for (var i = 0; i < flags.length; i++) {
        if (game_features.default(flags[i])) {
            test229_fail(flags[i] + ' must default OFF')
            return
        }
    }

    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)
    var allow = [BUILDING_FORT_CHARIOTEERS, BUILDING_FORT_GROUND]
    for (var a = 0; a < allow.length; a++) {
        if (!__scenario_building_allowed(allow[a])) {
            __scenario_building_allow(allow[a], true)
        }
    }

    city_planner.global_rotation = 2
    var bid = test229_place_fort()
    city_planner.global_rotation = 0
    if (!bid) {
        test229_fail('first fort place failed')
        return
    }
    var fort = city.get_building(bid)
    var ground = city.get_building(fort.next_part_building_id)
    var ft = __building_tile(bid)
    var gt = __building_tile(ground.id)
    if (gt.x != ft.x + 3 || gt.y != ft.y - 1) {
        test229_fail('parade ground expected at +3,-1 got ' + (gt.x - ft.x) + ',' + (gt.y - ft.y))
        return
    }
    __log_marker('test229_ground_fixed')

    var seen = {}
    var forts = [bid]
    while (city.num_forts < city.max_forts) {
        var next = test229_place_fort()
        if (!next) {
            test229_fail('fort ' + (forts.length + 1) + ' place failed')
            return
        }
        forts.push(next)
    }
    for (var k = 0; k < forts.length; k++) {
        var form = city.get_formation(city.get_building(forts[k]).formation_id)
        var idx = form ? form.batalion_id : -1
        if (idx < 1 || idx > forts.length || seen[idx]) {
            test229_fail('bad legion index ' + idx + ' for fort ' + k)
            return
        }
        seen[idx] = true
    }
    __log_marker('test229_legion_indices:' + forts.length)

    if (test_find_buildable_tile(BUILDING_FORT_CHARIOTEERS)) {
        test229_fail('planner still finds a fort site with a full complement')
        return
    }
    var gtile = test_find_buildable_tile(BUILDING_FORT_GROUND)
    if (!gtile) {
        test229_fail('no clear 4x4 site for the full-complement check')
        return
    }
    var tile = { x: gtile.x - 3, y: gtile.y + 1 }
    city_planner.build_type = BUILDING_FORT_CHARIOTEERS
    city_planner.finalize_check_result = CAN_PLACE
    building_fort_can_place({ start: tile, end: tile, state: CAN_PLACE })
    if (city_planner.finalize_check_result != CAN_NOT_PLACE) {
        test229_fail('full complement must refuse placement')
        return
    }
    __log_marker('test229_full_complement')

    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)
    var t2 = test_find_buildable_tile(BUILDING_FORT_CHARIOTEERS)
    if (!t2) {
        test229_fail('no buildable tile for the ground check')
        return
    }
    city_planner.build_type = BUILDING_FORT_CHARIOTEERS
    building_fort_can_place({ start: t2, end: t2, state: CAN_PLACE })
    if (city_planner.finalize_check_result != CAN_PLACE) {
        test229_fail('clear site must be placeable')
        return
    }
    terrain.add({ x: t2.x + 4, y: t2.y }, TERRAIN_ROAD)
    building_fort_can_place({ start: t2, end: t2, state: CAN_PLACE })
    if (city_planner.finalize_check_result != CAN_NOT_PLACE) {
        test229_fail('blocked parade ground must refuse placement')
        return
    }
    __log_marker('test229_ground_blocked')

    __test229_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test229_ok
        && __test_find_inlog('[test-marker] test229_ground_fixed')
        && __test_find_inlog('[test-marker] test229_legion_indices:')
        && __test_find_inlog('[test-marker] test229_full_complement')
        && __test_find_inlog('[test-marker] test229_ground_blocked')
}
