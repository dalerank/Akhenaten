// EVENT_TYPE_INVASION under the mission flag og_invasions, vs OG scenario_events.c:665
// (scenario_event_process_invasion): announcement in the event's month, reminders at
// 24 / 12 / 6 / 1 months left, the attack when months_initial has run out, and a favour
// child called off at Kingdom rating >= 15. Without the flag the events stay inert.
// Markers:
//   [test-marker] invasion_events_flag_off_ok
//   [test-marker] invasion_events_warnings_ok
//   [test-marker] invasion_events_attack_ok
//   [test-marker] invasion_events_called_off_ok
//   [test-marker] invasion_events_create_ok

function test390_fail(msg) {
    __log_info_native('[test:390] FAIL: ' + msg)
}

function test390_session() {
    test_reload_city_session('data/default.map')
    __test_clear_enemy_formations()
    __test_set_scenario_enemy_id(ENEMY_0_BARBARIAN)
    __test_invasion_points_clear()
    __test_invasion_land_point_set(0, 0, (__scenario_map.height / 2) | 0)
}

// Runs the monthly invasion pass for every month from (y0,m0) to (y1,m1) inclusive.
function test390_run_months(y0, m0, y1, m1) {
    for (var y = y0; y <= y1; y++) {
        for (var m = (y == y0 ? m0 : 0); m <= (y == y1 ? m1 : 11); m++) {
            __test_simtime_set(y, m)
            __test_process_invasions()
        }
    }
}

function test390_flag_off() {
    test390_session()
    __test_og_invasions_set(0)
    var id = __test_invasion_event_add(1, 0, EVENT_INVADER_ENEMY, 12, 2, 1)
    test390_run_months(1, 0, 1, 3)
    if (__test_invasion_event_warnings(id) != 0 || __test_invasion_event_fired(id) != 0) {
        test390_fail('flag off: warnings=' + __test_invasion_event_warnings(id) + ' fired=' + __test_invasion_event_fired(id))
        return
    }
    __log_marker('invasion_events_flag_off_ok')
}

function test390_warnings_and_attack() {
    test390_session()
    __test_og_invasions_set(1)
    // months_initial 25: the attack falls in year 3 month 1, so every reminder fits in.
    var id = __test_invasion_event_add(1, 0, EVENT_INVADER_ENEMY, 12, 25, 1)

    test390_run_months(1, 0, 3, 0)
    var mask = __test_invasion_event_warnings(id)
    if (mask != 31 || __test_invasion_event_fired(id) != 0) {
        test390_fail('before the attack: warnings mask=' + mask + ' (want 31) fired=' + __test_invasion_event_fired(id))
        return
    }
    __log_marker('invasion_events_warnings_ok')

    test390_run_months(3, 1, 3, 1)
    var enemies = __test_count_enemy_figures()
    if (__test_invasion_event_fired(id) != 1 || enemies <= 0) {
        test390_fail('attack month: fired=' + __test_invasion_event_fired(id) + ' enemies=' + enemies)
        return
    }
    __log_marker('invasion_events_attack_ok')
    __test_og_invasions_set(0)
}

function test390_called_off() {
    test390_session()
    __test_og_invasions_set(1)
    __test_kingdom_set_rating(20)
    var parent = __test_invasion_event_add(0, 0, EVENT_INVADER_PHARAOH, 30, 1, 1)
    __test_event_set_trigger(parent, EVENT_TRIGGER_BY_FAVOUR)
    var child = __test_invasion_event_add(1, 0, EVENT_INVADER_PHARAOH, 30, 6, 1)
    __test_event_set_parent(child, parent)

    test390_run_months(1, 0, 1, 0)
    if (__test_invasion_event_fired(child) != 1 || __test_invasion_event_warnings(child) != 0
        || __test_count_enemy_figures() != 0) {
        test390_fail('called off: fired=' + __test_invasion_event_fired(child)
            + ' warnings=' + __test_invasion_event_warnings(child) + ' enemies=' + __test_count_enemy_figures())
        return
    }
    __log_marker('invasion_events_called_off_ok')
    __test_og_invasions_set(0)
}

// city.create_invasion: an event made at run time runs the same cycle.
// months_initial 1 -> the event's own month is the 1-month warning (slot 4), the next month attacks.
function test390_create_invasion() {
    test390_session()
    __test_og_invasions_set(1)
    __test_simtime_set(2, 0)
    var inv = city.create_invasion({ tag_id: 38701, invader: EVENT_INVADER_ENEMY, amount: 8,
        months_initial: 1, route: 1, delay: 0 })
    if (inv.event_id < 0) {
        test390_fail('create_invasion returned ' + inv.event_id)
        return
    }
    __test_process_invasions()
    if (__test_invasion_event_warnings(inv.event_id) != 16) {
        test390_fail('create_invasion: warnings=' + __test_invasion_event_warnings(inv.event_id) + ' want 16')
        return
    }
    test390_run_months(2, 1, 2, 1)
    if (__test_invasion_event_fired(inv.event_id) != 1 || __test_count_enemy_figures() <= 0) {
        test390_fail('create_invasion attack: fired=' + __test_invasion_event_fired(inv.event_id)
            + ' enemies=' + __test_count_enemy_figures())
        return
    }
    __log_marker('invasion_events_create_ok')
    __test_og_invasions_set(0)
}

function run_test() {
    __log_info_native('[test:390] OG invasion events')
    test390_flag_off()
    test390_warnings_and_attack()
    test390_called_off()
    test390_create_invasion()
    __test_og_invasions_set(0)
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'invasion_events_flag_off_ok',
        'invasion_events_warnings_ok',
        'invasion_events_attack_ok',
        'invasion_events_called_off_ok',
        'invasion_events_create_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:390] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}
