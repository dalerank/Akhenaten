// OG figure/enemy_ships.c enemy_warship_wait / enemy_warship_patrol: after its wait the warship PATROLS (17) to the
// river entry, from there to the free water at the first landing point and back to the entry (on arrival that free
// tile is another one, as the ship itself stands on it); with no landing point it sails entry <-> river exit.
// Every 75 + rand(30) ticks of patrol it turns ATTACKING (10), and with no target back to patrolling.
// Markers:
//   [test-marker] warship_patrol_entry_ok
//   [test-marker] warship_patrol_route_ok
//   [test-marker] warship_patrol_no_landing_ok
//   [test-marker] warship_patrol_attack_interval_ok

var __test631_ok = false
var __test631_tick = 0

function test631_fail(msg) {
    __log_info_native('[test:631] FAIL: ' + msg)
    __test_signal_ready()
}

function test631_dest(id) {
    var d = __figure_get_destination_tile(id)
    return d ? { x: d.x, y: d.y } : { x: -1, y: -1 }
}

function test631_legs(ship, count, legs, attacks) {
    var last = test631_dest(ship)
    for (var t = 0; t < 6000 && legs.length < count; t++, __test631_tick++) {
        __test_figure_action_perform(ship)
        var action = __test_figure_get_action(ship)
        if (action == 10) {
            attacks.push(__test631_tick)
        } else if (action != 17) {
            return 'tick ' + __test631_tick + ': action=' + action
        }
        var now = test631_dest(ship)
        if (now.x != last.x || now.y != last.y) {
            legs.push({ x: __test_figure_tile_x(ship), y: __test_figure_tile_y(ship), dx: now.x, dy: now.y })
            last = now
        }
    }
    return legs.length < count ? 'patrol legs=' + JSON.stringify(legs) : ''
}

function run_test() {
    __log_info_native('[test:631] enemy warship patrol (OG enemy_warship_patrol)')

    test_reload_city_session('data/default.map')
    __test_clear_enemy_formations()
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    __test_make_lake(cx - 10, cy, 20, 8)
    __test_invasion_points_clear()
    __test_disembark_point_add(cx, cy - 1)
    var entry = { x: cx + 7, y: cy + 4 }
    var exit = { x: cx - 7, y: cy + 4 }
    __test_set_scenario_river_points(entry.x, entry.y, exit.x, exit.y)

    var ship = __test_figure_create(FIGURE_ENEMY_HITTITE_WAR_SHIP, cx + 2, cy + 5)
    if (!ship) {
        return test631_fail('could not create the warship')
    }
    __test_figure_set_wait_ticks(ship, 1)
    __test_figure_action_perform(ship)
    var d = test631_dest(ship)
    if (__test_figure_get_action(ship) != 17 || d.x != entry.x || d.y != entry.y) {
        return test631_fail('after the wait: action=' + __test_figure_get_action(ship) + ' dest=' + d.x + ',' + d.y)
    }
    __log_marker('warship_patrol_entry_ok')

    var legs = []
    var attacks = []
    var err = test631_legs(ship, 3, legs, attacks)
    if (err) {
        return test631_fail(err)
    }
    function near_landing(x, y) {
        return Math.abs(x - cx) <= 3 && y >= cy && y <= cy + 2
    }
    if (legs[0].x != entry.x || legs[0].y != entry.y || !near_landing(legs[0].dx, legs[0].dy)
        || !near_landing(legs[1].x, legs[1].y) || legs[1].dx != entry.x || legs[1].dy != entry.y
        || legs[2].x != entry.x || legs[2].y != entry.y || !near_landing(legs[2].dx, legs[2].dy)) {
        return test631_fail('legs=' + JSON.stringify(legs))
    }
    __log_marker('warship_patrol_route_ok')

    __test_invasion_points_clear()
    var plain = []
    err = test631_legs(ship, 3, plain, attacks)
    if (err) {
        return test631_fail('no landing: ' + err)
    }
    // The engine's boat movement may report arrival one tile past a westward destination.
    function at(leg, p) {
        return Math.abs(leg.x - p.x) <= 1 && Math.abs(leg.y - p.y) <= 1
    }
    if (!at(plain[1], entry) || plain[1].dx != exit.x || plain[1].dy != exit.y
        || !at(plain[2], exit) || plain[2].dx != entry.x || plain[2].dy != entry.y) {
        return test631_fail('no landing legs=' + JSON.stringify(plain))
    }
    __log_marker('warship_patrol_no_landing_ok')

    if (attacks.length < 3) {
        return test631_fail('attack turns=' + attacks.length)
    }
    for (var a = 1; a < attacks.length; a++) {
        var gap = attacks[a] - attacks[a - 1]
        if (gap < 76 || gap > 211) {
            return test631_fail('attack interval ' + gap + ' in ' + JSON.stringify(attacks))
        }
    }
    __log_marker('warship_patrol_attack_interval_ok')

    __test631_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test631_ok
        && __test_find_inlog('[test-marker] warship_patrol_entry_ok')
        && __test_find_inlog('[test-marker] warship_patrol_route_ok')
        && __test_find_inlog('[test-marker] warship_patrol_no_landing_ok')
        && __test_find_inlog('[test-marker] warship_patrol_attack_interval_ok')
}
