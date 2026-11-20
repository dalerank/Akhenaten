// Kingdom army at favour 0, vs OG city/kingdom.c:69-91 (city_emperor_update): at Kingdom rating 0 the
// first BY_FAVOUR invasion that is not in use is chained to now, warns with the low-kingdom text and
// rests 12 months (scenario_events_rearm); a second favour invasion is never pulled while the first rests.
// Its army is called off at rating >= 15.
// Markers:
//   [test-marker] favour_rating_gate_ok
//   [test-marker] favour_pull_ok
//   [test-marker] favour_second_not_pulled_ok
//   [test-marker] favour_attack_ok
//   [test-marker] favour_rearm_ok
//   [test-marker] favour_called_off_ok
//   [test-marker] favour_mission_abu_ok

var test418_failed = false

function test418_fail(msg) {
    test418_failed = true
    __log_info_native('[test:418] FAIL: ' + msg)
}

function test418_session() {
    test_reload_city_session('data/default.map')
    __test_clear_enemy_formations()
    __test_set_scenario_enemy_id(ENEMY_0_BARBARIAN)
    __test_invasion_points_clear()
    __test_invasion_land_point_set(0, 0, (__scenario_map.height / 2) | 0)
    __test_simtime_set(1, 0)
}

function test418_favour_event(invader, amount, months_initial) {
    var id = __test_invasion_event_add(0, 0, invader, amount, months_initial, 1)
    __test_event_set_trigger(id, EVENT_TRIGGER_BY_FAVOUR)
    return id
}

function test418_run_months(y, m0, m1) {
    for (var m = m0; m <= m1; m++) {
        __test_simtime_set(y, m)
        __test_process_invasions()
    }
}

function test418_pull_and_rearm() {
    test418_session()
    var first = test418_favour_event(EVENT_INVADER_PHARAOH, 12, 9)
    var second = test418_favour_event(EVENT_INVADER_EGYPT, 20, 9)

    __test_kingdom_set_rating(1)
    var count = __test_events_count()
    __test_kingdom_favour_update()
    if (__test_events_count() != count || __test_event_trigger(first) != EVENT_TRIGGER_BY_FAVOUR) {
        test418_fail('rating 1 pulled an army: events=' + __test_events_count() + ' trigger=' + __test_event_trigger(first))
        return
    }
    __log_marker('favour_rating_gate_ok')

    __test_kingdom_set_rating(0)
    __test_kingdom_favour_update()
    var army = count
    if (__test_events_count() != count + 1 || __test_event_parent(army) != first
        || __test_invasion_event_amount(army) != 12 || __test_event_trigger(first) != EVENT_TRIGGER_BY_FAVOUR_IN_USE) {
        test418_fail('pull: events=' + __test_events_count() + ' parent=' + __test_event_parent(army)
            + ' amount=' + __test_invasion_event_amount(army) + ' trigger=' + __test_event_trigger(first))
        return
    }
    var phrase = __test_last_message_eventmsg_phrase_id()
    if (__test_invasion_event_warnings(army) != 1 || phrase != __test_invasion_low_kingdom_phrase(EVENT_INVADER_PHARAOH)) {
        test418_fail('pull message: warnings=' + __test_invasion_event_warnings(army) + ' phrase=' + phrase
            + ' want ' + __test_invasion_low_kingdom_phrase(EVENT_INVADER_PHARAOH))
        return
    }
    __log_marker('favour_pull_ok')

    __test_kingdom_favour_update()
    if (__test_events_count() != count + 1 || __test_event_trigger(second) != EVENT_TRIGGER_BY_FAVOUR) {
        test418_fail('second pull: events=' + __test_events_count() + ' second trigger=' + __test_event_trigger(second))
        return
    }
    __log_marker('favour_second_not_pulled_ok')

    test418_run_months(1, 1, 8)
    if (__test_invasion_event_fired(army) != 0 || __test_count_enemy_figures() != 0) {
        test418_fail('attacked before its 9 months: fired=' + __test_invasion_event_fired(army))
        return
    }
    test418_run_months(1, 9, 9)
    if (__test_invasion_event_fired(army) != 1 || __test_count_enemy_figures() <= 0) {
        test418_fail('attack: fired=' + __test_invasion_event_fired(army) + ' enemies=' + __test_count_enemy_figures())
        return
    }
    __log_marker('favour_attack_ok')

    for (var i = 0; i < 11; i++) {
        __test_process_scenario_events()
    }
    if (__test_event_trigger(first) != EVENT_TRIGGER_BY_FAVOUR_IN_USE) {
        test418_fail('rested less than 12 months: trigger=' + __test_event_trigger(first))
        return
    }
    __test_process_scenario_events()
    if (__test_event_trigger(first) != EVENT_TRIGGER_BY_FAVOUR) {
        test418_fail('not rearmed after 12 months: trigger=' + __test_event_trigger(first))
        return
    }
    count = __test_events_count()
    __test_kingdom_favour_update()
    if (__test_events_count() != count + 1 || __test_event_parent(count) != first) {
        test418_fail('rearmed event not sent again: events=' + __test_events_count())
        return
    }
    __log_marker('favour_rearm_ok')
}

function test418_called_off() {
    test418_session()
    var master = test418_favour_event(EVENT_INVADER_PHARAOH, 12, 3)
    __test_kingdom_set_rating(0)
    var army = __test_events_count()
    __test_kingdom_favour_update()
    __test_kingdom_set_rating(15)
    test418_run_months(1, 1, 1)
    if (__test_event_parent(army) != master || __test_invasion_event_fired(army) != 1
        || __test_count_enemy_figures() != 0) {
        test418_fail('called off: parent=' + __test_event_parent(army) + ' fired=' + __test_invasion_event_fired(army)
            + ' enemies=' + __test_count_enemy_figures())
        return
    }
    __log_marker('favour_called_off_ok')
}

// Abu (9): pak i=15 Pharaoh x40 FOOD, 9 months, chains i=18 x20 and i=19 x20 at its attack.
function test418_mission_abu() {
    __game_load_mission(9, 1)
    __test_clear_enemy_formations()
    __test_simtime_set(0, 0)
    var master = __test_event_id_by_tag(7015)
    if (master < 0 || __test_event_trigger(master) != EVENT_TRIGGER_BY_FAVOUR) {
        test418_fail('abu: no favour event, id=' + master + ' trigger=' + __test_event_trigger(master))
        return
    }
    __test_kingdom_set_rating(0)
    var army = __test_events_count()
    __test_kingdom_favour_update()
    if (__test_event_parent(army) != master || __test_invasion_event_amount(army) != 40) {
        test418_fail('abu pull: parent=' + __test_event_parent(army) + ' amount=' + __test_invasion_event_amount(army))
        return
    }
    __test_kingdom_set_rating(5)
    test418_run_months(0, 1, 9)
    var waves = __test_events_count() - army
    if (__test_invasion_event_fired(army) != 1 || waves != 3 || __test_count_enemy_figures() <= 0
        || __test_invasion_event_amount(army + 1) != 20 || __test_invasion_event_amount(army + 2) != 20) {
        test418_fail('abu attack: fired=' + __test_invasion_event_fired(army) + ' waves=' + waves
            + ' enemies=' + __test_count_enemy_figures())
        return
    }
    __log_marker('favour_mission_abu_ok')
}

function run_test() {
    __log_info_native('[test:418] kingdom army at favour 0')
    test418_pull_and_rearm()
    test418_called_off()
    test418_mission_abu()
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'favour_rating_gate_ok',
        'favour_pull_ok',
        'favour_second_not_pulled_ok',
        'favour_attack_ok',
        'favour_rearm_ok',
        'favour_called_off_ok',
        'favour_mission_abu_ok'
    ]
    if (test418_failed) {
        return false
    }
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:418] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}
