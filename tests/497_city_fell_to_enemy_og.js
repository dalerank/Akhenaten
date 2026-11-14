// CITY_STATUS_CHANGE / CITY_FELL_TO_ENEMY vs OG scenario_events.c:371-470:
//   an Egyptian city becomes foreign (a trading one stays trading, its route stays open) and
//   MESSAGE_CITY_FELL_TO_ENEMY (338) is posted with phrases 126 / 127 (eg_city_falls title, announcement);
//   a city of any other type is left alone and nothing is posted.
// Abu (mission 9): Abedju is Egyptian trading, Nubt is Egyptian, Byblos is foreign.
// Markers:
//   [test-marker] city_fell_trading_ok
//   [test-marker] city_fell_egyptian_ok
//   [test-marker] city_fell_not_egyptian_ok

function test497_fail(msg) {
    __log_info_native('[test:497] FAIL: ' + msg)
}

// Empire city slot == lang id of its name (group 195 old names, 21 new names).
function test497_city(name) {
    for (var id = 0; id < 80; id++) {
        if (__loc(195, id) == name || __loc(21, id) == name) {
            return empire.get_city(id)
        }
    }
    return null
}

function test497_event(tag, subtype, name) {
    city.create_chain_event({ tag_id: tag, type: EVENT_TYPE_CITY_STATUS_CHANGE, subtype: subtype, city: name,
        trigger: EVENT_TRIGGER_ONCE }).execute()
}

function test497_last_is_fall(count_before) {
    var n = __city_message_count()
    if (n != count_before + 1) {
        return false
    }
    var last = n - 1
    return __city_message_mm_text_id(last) == __lang_get_message_uid('message_template_city_fell_to_enemy')
        && __city_message_eventmsg_title_id(last) == PHRASE_eg_city_falls_title
        && __city_message_eventmsg_body_id(last) == PHRASE_eg_city_falls_initial_announcement
}

function test497_describe(name, count_before) {
    var c = test497_city(name)
    var n = __city_message_count()
    var last = n - 1
    return name + ' type=' + (c ? c.type : -1) + ' open=' + (c ? c.is_open : -1) + ' msgs=' + count_before + '->' + n
        + (n > 0 ? ' mm=' + __city_message_mm_text_id(last) + ' title=' + __city_message_eventmsg_title_id(last)
            + ' body=' + __city_message_eventmsg_body_id(last) + ' phrase=' + __test_last_message_eventmsg_phrase_id()
            : '')
        + ' want mm=' + __lang_get_message_uid('message_template_city_fell_to_enemy')
}

function test497_trading() {
    var name = 'Abedju'
    test497_event(49701, EVENT_SUBTYPE_NEW_TRADE_ROUTE, name)
    var c = test497_city(name)
    if (!c || c.type != EMPIRE_CITY_EGYPTIAN_TRADING || !c.is_open) {
        test497_fail('trading setup: ' + test497_describe(name, __city_message_count()))
        return
    }
    var before = __city_message_count()
    test497_event(49702, EVENT_SUBTYPE_CITY_FELL_TO_ENEMY, name)
    c = test497_city(name)
    if (c.type != EMPIRE_CITY_FOREIGN_TRADING || !c.is_open || !test497_last_is_fall(before)) {
        test497_fail('trading: ' + test497_describe(name, before))
        return
    }
    __log_marker('city_fell_trading_ok')
}

function test497_egyptian() {
    var name = 'Nubt'
    var c = test497_city(name)
    if (!c || c.type != EMPIRE_CITY_EGYPTIAN) {
        test497_fail('egyptian setup: ' + test497_describe(name, __city_message_count()))
        return
    }
    var before = __city_message_count()
    test497_event(49711, EVENT_SUBTYPE_CITY_FELL_TO_ENEMY, name)
    if (test497_city(name).type != EMPIRE_CITY_FOREIGN || !test497_last_is_fall(before)) {
        test497_fail('egyptian: ' + test497_describe(name, before))
        return
    }
    __log_marker('city_fell_egyptian_ok')
}

function test497_not_egyptian() {
    var names = ['Byblos', 'Nubt']
    for (var i = 0; i < names.length; i++) {
        var type = test497_city(names[i]).type
        var before = __city_message_count()
        test497_event(49721 + i, EVENT_SUBTYPE_CITY_FELL_TO_ENEMY, names[i])
        if (test497_city(names[i]).type != type || __city_message_count() != before) {
            test497_fail('not egyptian: ' + test497_describe(names[i], before) + ' type before=' + type)
            return
        }
    }
    __log_marker('city_fell_not_egyptian_ok')
}

function run_test() {
    __log_info_native('[test:497] OG city fell to enemy')
    __game_load_mission(9, 1)
    test497_trading()
    test497_egyptian()
    test497_not_egyptian()
    __test_signal_ready()
}

function check_valid() {
    var markers = ['city_fell_trading_ok', 'city_fell_egyptian_ok', 'city_fell_not_egyptian_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:497] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}
