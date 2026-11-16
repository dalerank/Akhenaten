// OG figure_type.h: FIGURE_ENEMY_EGYPTIAN_WARSHIP = 100, FIGURE_ENEMY_EGYPTIAN_TRANSPORT_SHIP = 101 (51 is the
// barbarian archer). A sea invasion of Egypt launches its ships with exactly those type ids.
// Markers:
//   [test-marker] egyptian_ship_ids_ok
//   [test-marker] egyptian_sea_invasion_types_ok

var __test643_ok = false

function test643_fail(msg) {
    __log_info_native('[test:643] FAIL: ' + msg)
    __test_signal_ready()
}

function test643_count(type) {
    var n = 0
    for (var i = 1; i < 2000; i++) {
        if (__figure_get_type(i) == type && __test_figure_is_alive(i)) {
            n++
        }
    }
    return n
}

function run_test() {
    __log_info_native('[test:643] egyptian ship figure ids match OG')

    if (FIGURE_ENEMY_EGYPTIAN_WARSHIP !== 100 || FIGURE_ENEMY_EGYPTIAN_TRANSPORT_SHIP !== 101) {
        return test643_fail('warship=' + FIGURE_ENEMY_EGYPTIAN_WARSHIP + ' transport=' + FIGURE_ENEMY_EGYPTIAN_TRANSPORT_SHIP)
    }
    __log_marker('egyptian_ship_ids_ok')

    var nations = [enemy_barbarian, enemy_assyrian, enemy_canaanite, enemy_egyptian, enemy_hittite, enemy_hyksos,
        enemy_kushite, enemy_libian, enemy_nubian, enemy_persian, enemy_phoenician, enemy_roman, enemy_seapeople]
    for (var n = 0; n < nations.length; n++) {
        if (nations[n].type != n || !nations[n].warship || !nations[n].transport) {
            return test643_fail('enemy config ' + n + ' type=' + nations[n].type + ' warship=' + nations[n].warship
                + ' transport=' + nations[n].transport)
        }
    }
    if (enemy_egyptian.warship != 100 || enemy_egyptian.transport != 101) {
        return test643_fail('enemy_egyptian ships ' + enemy_egyptian.warship + '/' + enemy_egyptian.transport)
    }

    test_reload_city_session('data/default.map')
    __test_clear_enemy_formations()
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    __test_make_lake(cx - 10, cy, 20, 8)
    __test_invasion_points_clear()
    __test_invasion_sea_point_set(0, cx + 4, cy + 4)
    __test_disembark_point_add(cx - 8, cy - 1)

    var started = city.start_foreign_army_invasion({
        mode: ATTACK_TYPE_ENEMIES,
        enemy: ENEMY_3_EGYPTIAN,
        size: 32,
        invasion_id: 23,
        via_sea: 1,
        sea_point: 0,
        warships: 2
    })
    if (!started) {
        return test643_fail('egyptian sea invasion did not start')
    }
    var warships = test643_count(100)
    var transports = test643_count(101)
    if (warships != 2 || transports != 2 || test643_count(51) != 0 || test643_count(141) != 0) {
        return test643_fail('type 100=' + warships + ' type 101=' + transports + ' type 51=' + test643_count(51)
            + ' type 141=' + test643_count(141))
    }
    __log_marker('egyptian_sea_invasion_types_ok')

    __test643_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test643_ok
        && __test_find_inlog('[test-marker] egyptian_ship_ids_ok')
        && __test_find_inlog('[test-marker] egyptian_sea_invasion_types_ok')
}
