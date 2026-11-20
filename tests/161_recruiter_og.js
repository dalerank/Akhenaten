// Recruiter OG (building_barracks_create_soldier): archers need no stock, infantry needs weapons and
// charioteers need chariots; the highest recruit type wins (charioteers, infantry, archers), and a recruit
// takes 100 of its stock. Legions on a kingdom request (in_distant_battle) or on a transport ship
// (ship_figure_id) are skipped. A recruit averages experience into the legion (no academy -> training 0).
// gameplay_change_recruit_nearest_fort sends the recruit to the nearest fort instead.
// Fort costs come from Pharaoh_Model_*.txt.

var __test161_ok = false
var __test161_feature_prev = false

function test161_finish() {
    game_features.set('gameplay_change_recruit_nearest_fort', __test161_feature_prev)
    __test_signal_ready()
}

function test161_fail(msg) {
    __log_info_native('[test:161] FAIL: ' + msg)
    test_planner_exit_build_mode()
    test161_finish()
}

function test161_place(type) {
    var bid = test_building_place(type, -1, -1)
    test_planner_exit_build_mode()
    return bid
}

function test161_dist(a, b) {
    var ta = __building_tile(a)
    var tb = __building_tile(b)
    return Math.max(Math.abs(ta.x - tb.x), Math.abs(ta.y - tb.y))
}

function run_test() {
    __log_info_native('[test:161] recruiter OG')
    __test161_feature_prev = game_features.get('gameplay_change_recruit_nearest_fort') === true
    if (game_features.default('gameplay_change_recruit_nearest_fort')) {
        test161_fail('gameplay_change_recruit_nearest_fort must default OFF')
        return
    }
    game_features.set('gameplay_change_recruit_nearest_fort', false)

    var costs = [
        [building_fort_charioteers, [500, 800, 1000, 1200, 1500]],
        [building_fort_archers, [200, 800, 1000, 1200, 1500]],
        [building_fort_infantry, [200, 800, 1000, 1200, 1500]]
    ]
    for (var c = 0; c < costs.length; c++) {
        for (var d = 0; d < 5; d++) {
            if (costs[c][0].cost[d] != costs[c][1][d]) {
                test161_fail('fort ' + c + ' cost[' + d + '] expected ' + costs[c][1][d] + ' got ' + costs[c][0].cost[d])
                return
            }
        }
    }
    __log_marker('test161_fort_costs')

    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)
    var allow = [BUILDING_RECRUITER, BUILDING_FORT_CHARIOTEERS, BUILDING_FORT_ARCHERS, BUILDING_FORT_INFANTRY, BUILDING_FORT_GROUND]
    for (var a = 0; a < allow.length; a++) {
        if (!__scenario_building_allowed(allow[a])) {
            __scenario_building_allow(allow[a], true)
        }
    }

    var rid = test161_place(BUILDING_RECRUITER)
    var archers = test161_place(BUILDING_FORT_ARCHERS)
    var infantry = test161_place(BUILDING_FORT_INFANTRY)
    var chariots = test161_place(BUILDING_FORT_CHARIOTEERS)
    if (!rid || !archers || !infantry || !chariots) {
        test161_fail('place failed r=' + rid + ' a=' + archers + ' i=' + infantry + ' c=' + chariots)
        return
    }
    var forts = [archers, infantry, chariots]
    for (var f = 0; f < forts.length; f++) {
        __test_fort_update_recruit_status(forts[f])
    }
    var fid_archers = city.get_building(archers).formation_id
    var fid_infantry = city.get_building(infantry).formation_id
    var fid_chariots = city.get_building(chariots).formation_id
    var r = city.get_building(rid)

    if (__test_recruiter_pick_batalion(rid) != fid_archers) {
        test161_fail('without stock only archers may recruit, got ' + __test_recruiter_pick_batalion(rid))
        return
    }
    __log_marker('test161_archers_free')

    r.consume_resource(RESOURCE_WEAPONS, -200)
    if (__test_recruiter_pick_batalion(rid) != fid_infantry) {
        test161_fail('with weapons infantry must beat archers, got ' + __test_recruiter_pick_batalion(rid))
        return
    }
    __log_marker('test161_infantry_weapons')

    r.consume_resource(RESOURCE_CHARIOTS, -100)
    if (__test_recruiter_pick_batalion(rid) != fid_chariots) {
        test161_fail('with chariots charioteers must win, got ' + __test_recruiter_pick_batalion(rid))
        return
    }
    if (!__test_recruiter_create_soldier(rid)) {
        test161_fail('create_soldier failed')
        return
    }
    r = city.get_building(rid)
    if (r.stored_resource(RESOURCE_CHARIOTS) != 0 || r.stored_resource(RESOURCE_WEAPONS) != 200) {
        test161_fail('charioteer must take 100 chariots, not weapons: chariots=' + r.stored_resource(RESOURCE_CHARIOTS)
            + ' weapons=' + r.stored_resource(RESOURCE_WEAPONS))
        return
    }
    __log_marker('test161_charioteer_uses_chariots')

    // OG: request_event_id >= 0 (mapped to in_distant_battle) skips the legion.
    __test_formation_set_in_distant_battle(fid_chariots, 1)
    if (__test_recruiter_pick_batalion(rid) != fid_infantry) {
        test161_fail('distant-battle charioteers must yield to infantry, got ' + __test_recruiter_pick_batalion(rid))
        return
    }
    __test_formation_set_in_distant_battle(fid_chariots, 0)
    __log_marker('test161_skip_distant_battle')

    // OG: ship_figure_id != 0 skips the legion.
    __test_formation_set_ship_figure(fid_infantry, 1)
    if (__test_recruiter_pick_batalion(rid) != fid_archers) {
        test161_fail('infantry on a ship must yield to archers, got ' + __test_recruiter_pick_batalion(rid))
        return
    }
    __test_formation_set_ship_figure(fid_infantry, 0)
    __log_marker('test161_skip_ship')

    __test_formation_set_experience(fid_infantry, 40)
    if (__test_recruiter_pick_batalion(rid) != fid_infantry) {
        test161_fail('infantry should win with weapons for experience check, got ' + __test_recruiter_pick_batalion(rid))
        return
    }
    if (!__test_recruiter_create_soldier(rid)) {
        test161_fail('infantry create_soldier for experience failed')
        return
    }
    var form_inf = city.get_formation(fid_infantry)
    if (!form_inf || form_inf.experience != 20) {
        test161_fail('OG no-academy experience want 20 got ' + (form_inf ? form_inf.experience : 'null'))
        return
    }
    __log_marker('test161_experience')

    game_features.set('gameplay_change_recruit_nearest_fort', true)
    var eligible = [[archers, fid_archers], [infantry, fid_infantry]]
    var nearest = eligible[0]
    if (test161_dist(rid, eligible[1][0]) < test161_dist(rid, nearest[0])) {
        nearest = eligible[1]
    }
    if (__test_recruiter_pick_batalion(rid) != nearest[1]) {
        test161_fail('remake must pick the nearest fort, got ' + __test_recruiter_pick_batalion(rid) + ' expected ' + nearest[1])
        return
    }
    __log_marker('test161_remake_nearest')

    __test161_ok = true
    test161_finish()
}

function check_valid() {
    return __test161_ok
        && __test_find_inlog('[test-marker] test161_fort_costs')
        && __test_find_inlog('[test-marker] test161_archers_free')
        && __test_find_inlog('[test-marker] test161_infantry_weapons')
        && __test_find_inlog('[test-marker] test161_charioteer_uses_chariots')
        && __test_find_inlog('[test-marker] test161_skip_distant_battle')
        && __test_find_inlog('[test-marker] test161_skip_ship')
        && __test_find_inlog('[test-marker] test161_experience')
        && __test_find_inlog('[test-marker] test161_remake_nearest')
}
