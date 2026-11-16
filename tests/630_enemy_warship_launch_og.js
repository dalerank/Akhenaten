// OG scenario/invasion.c invasion_start_sea (:170): the event's phrase_var warships (mission key `warships`) are
// launched before the transports, each WAITING (8) 25*i + 10 ticks and hidden until it sails; an invasion of 0
// soldiers still sends its warships. Egyptian warships start on the sea point itself, the others on the nearest
// free water tile around it.
// Markers:
//   [test-marker] warship_launch_stagger_ok
//   [test-marker] warship_launch_no_soldiers_ok
//   [test-marker] warship_launch_egyptian_point_ok

var __test630_ok = false

function test630_fail(msg) {
    __log_info_native('[test:630] FAIL: ' + msg)
    __test_signal_ready()
}

function test630_session() {
    test_reload_city_session('data/default.map')
    __test_clear_enemy_formations()
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    __test_make_lake(cx - 10, cy, 20, 8)
    __test_invasion_points_clear()
    __test_invasion_sea_point_set(0, cx + 4, cy + 4)
    __test_disembark_point_add(cx - 8, cy - 1)
    return { sx: cx + 4, sy: cy + 4 }
}

function test630_ships(type) {
    var ids = []
    for (var i = 1; i < 2000; i++) {
        if (__figure_get_type(i) == type && __test_figure_is_alive(i)) {
            ids.push(i)
        }
    }
    return ids
}

function test630_invade(enemy, size, warships) {
    return city.start_foreign_army_invasion({
        mode: ATTACK_TYPE_ENEMIES,
        enemy: enemy,
        size: size,
        invasion_id: 23,
        via_sea: 1,
        sea_point: 0,
        warships: warships
    })
}

function run_test() {
    __log_info_native('[test:630] enemy warship launch (OG invasion_start_sea)')

    test630_session()
    if (!test630_invade(ENEMY_4_HITTITE, 16, 3)) {
        return test630_fail('sea invasion of 16 with 3 warships did not start')
    }
    var ships = test630_ships(FIGURE_ENEMY_HITTITE_WAR_SHIP)
    if (ships.length != 3) {
        return test630_fail('warships=' + ships.length + ' want 3')
    }
    for (var i = 0; i < ships.length; i++) {
        var wait = __test_figure_get_wait_ticks(ships[i])
        var action = __test_figure_get_action(ships[i])
        if (wait != 25 * i + 10 || action != 8 || __test_figure_is_visible(ships[i]) != 0) {
            return test630_fail('warship ' + i + ': wait=' + wait + ' action=' + action + ' visible='
                + __test_figure_is_visible(ships[i]))
        }
    }
    __log_marker('warship_launch_stagger_ok')

    test630_session()
    if (!test630_invade(ENEMY_4_HITTITE, 0, 2)) {
        return test630_fail('sea invasion of 0 soldiers with 2 warships did not start')
    }
    ships = test630_ships(FIGURE_ENEMY_HITTITE_WAR_SHIP)
    if (ships.length != 2 || __test_count_enemy_transports() != 0) {
        return test630_fail('0 soldiers: warships=' + ships.length + ' transports=' + __test_count_enemy_transports())
    }
    __log_marker('warship_launch_no_soldiers_ok')

    var p = test630_session()
    if (!test630_invade(ENEMY_3_EGYPTIAN, 0, 2)) {
        return test630_fail('egyptian sea invasion did not start')
    }
    var egypt = test630_ships(FIGURE_ENEMY_EGYPTIAN_WARSHIP)
    if (egypt.length != 2) {
        return test630_fail('egyptian warships=' + egypt.length)
    }
    for (var e = 0; e < egypt.length; e++) {
        if (__test_figure_tile_x(egypt[e]) != p.sx || __test_figure_tile_y(egypt[e]) != p.sy) {
            return test630_fail('egyptian warship ' + e + ' at ' + __test_figure_tile_x(egypt[e]) + ','
                + __test_figure_tile_y(egypt[e]) + ' want the sea point ' + p.sx + ',' + p.sy)
        }
    }
    __log_marker('warship_launch_egyptian_point_ok')

    __test630_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test630_ok
        && __test_find_inlog('[test-marker] warship_launch_stagger_ok')
        && __test_find_inlog('[test-marker] warship_launch_no_soldiers_ok')
        && __test_find_inlog('[test-marker] warship_launch_egyptian_point_ok')
}
