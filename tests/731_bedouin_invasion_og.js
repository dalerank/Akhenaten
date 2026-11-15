// EVENT_INVADER_BEDOUINS vs OG scenario_events.c invasion_nation (ENEMY_BEDOUIN) and invasion.c
// scenario_invasion_start: every soldier is FIGURE_BEDOUIN (bedouin_types, groups 2 and 3 get 0%), the
// formations are FORMATION_ENEMY_MOB of nation 13, the stats are Figure_model row 99 and the names are
// text group 290. A sea route (9..16) still lands the Bedouins: with an empty sea slot they wrap to the
// land points (invasion_land_point) and no transport is launched. The invasion hangs under a favour master,
// the only events[] invasions the OG cycle runs.
// Markers:
//   [test-marker] bedouin_invasion_spawn_ok
//   [test-marker] bedouin_invasion_stats_ok
//   [test-marker] bedouin_invasion_names_ok
//   [test-marker] bedouin_invasion_sea_route_ok

var T731_NAMES = ['Putasokinhet', 'Xander', 'Ironrod', 'Hat-tubig', 'Reckless Rodent', 'Ancient One', 'Bedu',
    'Trespasser', 'Nomad', 'Wanderer', 'Sandman', 'Conan', 'Shabbaba', 'Rababa', 'Fuqara', 'Petra']

function test731_fail(msg) {
    __log_info_native('[test:731] FAIL: ' + msg)
}

function test731_session() {
    test_reload_city_session('data/default.map')
    __test_clear_enemy_formations()
    __test_set_scenario_enemy_id(ENEMY_0_BARBARIAN)
    __test_invasion_points_clear()
    __test_invasion_land_point_set(0, 0, (__scenario_map.height / 2) | 0)
    __test_kingdom_set_rating(5)
}

// months_initial 1: the event's own month warns, the next month attacks.
function test731_attack(route) {
    var id = __test_invasion_event_add(1, 0, EVENT_INVADER_BEDUINS, 8, 1, route)
    var master = __test_invasion_event_add(0, 0, EVENT_INVADER_BEDUINS, 8, 1, route)
    __test_event_set_trigger(master, EVENT_TRIGGER_BY_FAVOUR)
    __test_event_set_parent(id, master)
    __test_simtime_set(1, 0)
    __test_process_invasions()
    __test_simtime_set(1, 1)
    __test_process_invasions()
    return id
}

function test731_check_army(what) {
    var enemies = __test_count_enemy_figures()
    var bedouins = __test_count_figures(FIGURE_BEDOUIN)
    if (enemies <= 0 || bedouins != enemies) {
        test731_fail(what + ': enemies=' + enemies + ' bedouins=' + bedouins)
        return false
    }
    var ids = __test_enemy_formations()
    if (ids === '') {
        test731_fail(what + ': no enemy formation')
        return false
    }
    var list = ids.split(',')
    for (var i = 0; i < list.length; i++) {
        var want = FORMATION_ENEMY_MOB + ',' + ENEMY_13_BEDOUIN + ',' + FIGURE_BEDOUIN
        var got = __test_formation_kind(+list[i])
        if (got != want) {
            test731_fail(what + ': formation ' + list[i] + ' kind ' + got + ' want ' + want)
            return false
        }
    }
    return true
}

function test731_spawn() {
    test731_session()
    var id = test731_attack(1)
    if (__test_invasion_event_fired(id) != 1) {
        test731_fail('event not fired')
        return
    }
    if (!test731_check_army('land route')) {
        return
    }
    __log_marker('bedouin_invasion_spawn_ok')

    var want = figure_category_hostile + ',70,12,0,0'
    var got = __test_figure_type_combat(FIGURE_BEDOUIN)
    var fid = __test_first_figure_of_type(FIGURE_BEDOUIN)
    if (got != want || __test_figure_is_enemy(fid) != 1) {
        test731_fail('stats ' + got + ' want ' + want + ' is_enemy=' + __test_figure_is_enemy(fid))
        return
    }
    __log_marker('bedouin_invasion_stats_ok')

    var name = city.get_figure(fid).name
    if (T731_NAMES.indexOf('' + name) < 0) {
        test731_fail('name "' + name + '" is not from OG text group 290')
        return
    }
    __log_marker('bedouin_invasion_names_ok')
}

function test731_sea_route() {
    test731_session()
    var id = test731_attack(9)
    if (__test_invasion_event_fired(id) != 1) {
        test731_fail('sea route: event not fired')
        return
    }
    if (__test_count_enemy_transports() != 0) {
        test731_fail('sea route: launched ' + __test_count_enemy_transports() + ' transports')
        return
    }
    if (!test731_check_army('sea route')) {
        return
    }
    __log_marker('bedouin_invasion_sea_route_ok')
}

function run_test() {
    __log_info_native('[test:731] OG Bedouin invasion')
    test731_spawn()
    test731_sea_route()
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'bedouin_invasion_spawn_ok',
        'bedouin_invasion_stats_ok',
        'bedouin_invasion_names_ok',
        'bedouin_invasion_sea_route_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:731] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}
