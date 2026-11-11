// Land invasion start vs OG scenario_invasion_start (invasion.c:74, 259, 275):
// - the army faces into the map from the edge it enters by (left edge -> right, bottom edge -> up);
// - a tree, rock or cliff at the invasion point cancels the invasion.
// Markers:
//   [test-marker] invasion_orientation_left_ok
//   [test-marker] invasion_orientation_bottom_ok
//   [test-marker] invasion_blocked_point_ok

var DIR_0_TOP_RIGHT = 0
var DIR_2_BOTTOM_RIGHT = 2

function test316_fail(msg) {
    __log_info_native('[test:316] FAIL: ' + msg)
}

function test316_invade(x, y) {
    return city.start_foreign_army_invasion({
        mode: ATTACK_TYPE_ENEMIES,
        enemy: ENEMY_0_BARBARIAN,
        size: 8,
        invasion_id: 1,
        tilex: x,
        tiley: y,
        want_destroy_buildings: 0,
        invasion_attack_target: EVENT_ATTACK_TARGET_RANDOM
    })
}

function test316_first_orientation() {
    var ids = __test_enemy_formations()
    if (ids === '') {
        return -1
    }
    return +__test_enemy_formation_state(+ids.split(',')[0]).split(',')[7]
}

// edge: 'left' or 'bottom'; the map is loaded first so its size is known.
function test316_check_orientation(edge, want, marker) {
    test_reload_city_session('data/default.map')
    var w = __scenario_map.width
    var h = __scenario_map.height
    var x = edge == 'left' ? 0 : (w / 2) | 0
    var y = edge == 'left' ? (h / 2) | 0 : h - 1
    test316_invade(x, y)
    var got = test316_first_orientation()
    if (got == want) {
        __log_marker(marker)
    } else {
        test316_fail(edge + ' edge: orientation ' + got + ' at ' + x + ',' + y + ', want ' + want)
    }
}

function run_test() {
    __log_info_native('[test:316] invasion start OG')
    test316_check_orientation('left', DIR_2_BOTTOM_RIGHT, 'invasion_orientation_left_ok')
    test316_check_orientation('bottom', DIR_0_TOP_RIGHT, 'invasion_orientation_bottom_ok')

    test_reload_city_session('data/default.map')
    var h = __scenario_map.height
    var bx = 2
    var by = (h / 2) | 0
    terrain.add({ x: bx, y: by }, TERRAIN_TREE)
    var seq = test316_invade(bx, by)
    if (!seq && __test_enemy_formations() === '') {
        __log_marker('invasion_blocked_point_ok')
    } else {
        test316_fail('invasion started on a tree: seq=' + seq + ' formations=' + __test_enemy_formations())
    }

    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('invasion_orientation_left_ok') && __test_find_inlog('invasion_orientation_bottom_ok')
        && __test_find_inlog('invasion_blocked_point_ok')
}
