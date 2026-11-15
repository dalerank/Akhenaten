// EVENT_TYPE_INVASION message phrases come from the invader's config entry (enemies.js invader_*):
// announcement and 2-year reminder, the transport landing alert (none for Pharaoh's army) and the
// city-attacked alert, for a foreign army, Pharaoh's army and the Bedouins.
// Markers:
//   [test-marker] invasion_phrases_enemy_ok
//   [test-marker] invasion_phrases_pharaoh_ok
//   [test-marker] invasion_phrases_bedouins_ok

function test638_fail(msg) {
    __log_info_native('[test:638] FAIL: ' + msg)
}

function test638_session() {
    test_reload_city_session('data/default.map')
    __test_clear_enemy_formations()
    __test_set_scenario_enemy_id(ENEMY_0_BARBARIAN)
    __test_invasion_points_clear()
    __test_invasion_land_point_set(0, 0, (__scenario_map.height / 2) | 0)
    __test_og_invasions_set(1)
}

function test638_last() {
    var n = __city_message_count()
    if (n <= 0) {
        return { count: n }
    }
    return { count: n, title: __city_message_eventmsg_title_id(n - 1), body: __city_message_eventmsg_body_id(n - 1),
        phrase: __test_last_message_eventmsg_phrase_id() }
}

function test638_expect(what, got, title, body, phrase) {
    if (got.title != title || got.body != body || got.phrase != phrase) {
        test638_fail(what + ': title=' + got.title + '/' + title + ' body=' + got.body + '/' + body
            + ' phrase=' + got.phrase + '/' + phrase)
        return false
    }
    return true
}

function test638_run(name, invader, p) {
    test638_session()
    var id = __test_invasion_event_add(1, 0, invader, 8, 25, 1)

    __test_simtime_set(1, 0)
    __test_process_invasions()
    if (!test638_expect(name + ' announcement', test638_last(), p.title, p.warnings[0], p.no_reason)) {
        return
    }
    __test_simtime_set(1, 1)
    __test_process_invasions()
    if (!test638_expect(name + ' 2-year reminder', test638_last(), p.title, p.warnings[1], p.no_reason)) {
        return
    }

    var before = __city_message_count()
    __test_invasion_landing_message(id)
    if (p.disembarked < 0) {
        if (__city_message_count() != before) {
            test638_fail(name + ' landing: posted a message, want none')
            return
        }
    } else if (__city_message_count() != before + 1
        || !test638_expect(name + ' landing', test638_last(), p.title, p.disembarked, p.no_reason)) {
        return
    }

    __test_simtime_set(3, 1)
    __test_process_invasions()
    if (__test_invasion_event_fired(id) != 1
        || !test638_expect(name + ' attack', test638_last(), p.title, p.city_attacked, p.no_reason)) {
        test638_fail(name + ' attack: fired=' + __test_invasion_event_fired(id))
        return
    }
    __log_marker('invasion_phrases_' + name + '_ok')
}

function run_test() {
    __log_info_native('[test:638] invasion phrases by invader')
    test638_run('enemy', EVENT_INVADER_ENEMY, {
        title: PHRASE_foreign_army_attacks_you_title,
        warnings: [PHRASE_foreign_army_attacks_you_initial_announcement, PHRASE_foreign_army_attacks_you_2year_reminder],
        city_attacked: PHRASE_foreign_army_attacks_you_city_attacked_alert,
        no_reason: PHRASE_foreign_army_attacks_you_no_reason_A,
        disembarked: PHRASE_foreign_army_attacks_you_disembarked_alert })
    test638_run('pharaoh', EVENT_INVADER_PHARAOH, {
        title: PHRASE_pharaoh_attacks_you_title,
        warnings: [PHRASE_pharaoh_attacks_you_initial_announcement, PHRASE_pharaoh_attacks_you_2year_reminder],
        city_attacked: PHRASE_pharaoh_attacks_you_city_attacked_alert,
        no_reason: PHRASE_pharaoh_attacks_you_no_reason_A,
        disembarked: -1 })
    test638_run('bedouins', EVENT_INVADER_BEDUINS, {
        title: PHRASE_bedouin_attacks_you_title,
        warnings: [PHRASE_bedouin_attacks_you_initial_announcement, PHRASE_bedouin_attacks_you_2year_reminder],
        city_attacked: PHRASE_bedouin_attacks_you_city_attacked_alert,
        no_reason: PHRASE_bedouin_attacks_you_no_reason_A,
        disembarked: PHRASE_bedouin_attacks_you_disembarked_alert })
    __test_og_invasions_set(0)
    __test_signal_ready()
}

function check_valid() {
    var markers = ['invasion_phrases_enemy_ok', 'invasion_phrases_pharaoh_ok', 'invasion_phrases_bedouins_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:638] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}
