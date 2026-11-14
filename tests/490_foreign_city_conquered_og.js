// #192 CITY_STATUS_CHANGE / FOREIGN_CITY_CONQUERED vs OG scenario_events.c:371-470:
//   a foreign city becomes Egyptian (a trading one stays trading) and MESSAGE_CITY_CONQUERED (339) is posted
//   with phrases 130 / 131 / 133 (foreign_city_conquered title, announcement, no_reason_A);
//   a city of any other type is left alone and nothing is posted.
// Abu (mission 9): Selima Oasis and Kyrene are foreign, Behdet is Egyptian trading.
// Markers:
//   [test-marker] city_conquered_foreign_ok
//   [test-marker] city_conquered_trading_ok
//   [test-marker] city_conquered_not_foreign_ok

function test490_fail(msg) {
    __log_info_native('[test:490] FAIL: ' + msg)
}

// Empire city slot == lang id of its name (group 195 old names, 21 new names).
function test490_city_id(name) {
    for (var id = 0; id < 80; id++) {
        if (__loc(195, id) == name || __loc(21, id) == name) {
            return id
        }
    }
    return -1
}

function test490_type(name) {
    var id = test490_city_id(name)
    return id < 0 ? -1 : empire.get_city(id).type
}

function test490_event(tag, subtype, name) {
    city.create_chain_event({ tag_id: tag, type: EVENT_TYPE_CITY_STATUS_CHANGE, subtype: subtype, city: name,
        trigger: EVENT_TRIGGER_ONCE }).execute()
}

function test490_last_is_conquered(count_before) {
    var n = __city_message_count()
    if (n != count_before + 1) {
        return false
    }
    var last = n - 1
    return __city_message_mm_text_id(last) == __lang_get_message_uid('message_template_foreign_city_conquered')
        && __city_message_eventmsg_title_id(last) == PHRASE_foreign_city_conquered_title
        && __city_message_eventmsg_body_id(last) == PHRASE_foreign_city_conquered_initial_announcement
        && __test_last_message_eventmsg_phrase_id() == PHRASE_foreign_city_conquered_no_reason_A
}

function test490_describe(name, count_before) {
    var n = __city_message_count()
    var last = n - 1
    return name + ' type=' + test490_type(name) + ' msgs=' + count_before + '->' + n
        + (n > 0 ? ' mm=' + __city_message_mm_text_id(last) + ' title=' + __city_message_eventmsg_title_id(last)
            + ' body=' + __city_message_eventmsg_body_id(last) + ' phrase=' + __test_last_message_eventmsg_phrase_id()
            : '')
        + ' want mm=' + __lang_get_message_uid('message_template_foreign_city_conquered')
}

function test490_foreign() {
    var name = 'Selima Oasis'
    if (test490_type(name) != EMPIRE_CITY_FOREIGN) {
        test490_fail('setup: ' + test490_describe(name, __city_message_count()))
        return
    }
    var before = __city_message_count()
    test490_event(49001, EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED, name)
    if (test490_type(name) != EMPIRE_CITY_EGYPTIAN || !test490_last_is_conquered(before)) {
        test490_fail('foreign: ' + test490_describe(name, before))
        return
    }
    __log_marker('city_conquered_foreign_ok')
}

function test490_trading() {
    var name = 'Kyrene'
    test490_event(49011, EVENT_SUBTYPE_NEW_TRADE_ROUTE, name)
    if (test490_type(name) != EMPIRE_CITY_FOREIGN_TRADING) {
        test490_fail('trading setup: ' + test490_describe(name, __city_message_count()))
        return
    }
    var before = __city_message_count()
    test490_event(49012, EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED, name)
    if (test490_type(name) != EMPIRE_CITY_EGYPTIAN_TRADING || !test490_last_is_conquered(before)) {
        test490_fail('trading: ' + test490_describe(name, before))
        return
    }
    __log_marker('city_conquered_trading_ok')
}

function test490_not_foreign() {
    var names = ['Behdet', 'Selima Oasis']
    for (var i = 0; i < names.length; i++) {
        var type = test490_type(names[i])
        var before = __city_message_count()
        test490_event(49021 + i, EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED, names[i])
        if (test490_type(names[i]) != type || __city_message_count() != before) {
            test490_fail('not foreign: ' + test490_describe(names[i], before) + ' type before=' + type)
            return
        }
    }
    __log_marker('city_conquered_not_foreign_ok')
}

function run_test() {
    __log_info_native('[test:490] OG foreign city conquered')
    __game_load_mission(9, 1)
    test490_foreign()
    test490_trading()
    test490_not_foreign()
    __test_signal_ready()
}

function check_valid() {
    var markers = ['city_conquered_foreign_ok', 'city_conquered_trading_ok', 'city_conquered_not_foreign_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:490] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}
