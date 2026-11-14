// EVENT_TYPE_MESSAGE vs OG scenario_events.c:219-251 (event_message_type, scenario_event_process_message):
//   subtype 0 city saved -> MESSAGE_CITY_SAVED (262), 1 battle won -> MESSAGE_DISTANT_BATTLE_WON (263),
//   2 battle lost and 3 acknowledgement -> MESSAGE_TEMPLATE_GENERAL (131); every template must exist,
//   or the message is dropped. Without reasons the text is the subtype's no_reason_A (149 + 4 * subtype).
// Markers:
//   [test-marker] event_messages_og_battle_won_ok
//   [test-marker] event_messages_og_templates_ok

function test496_fail(msg) {
    __log_info_native('[test:496] FAIL: ' + msg)
}

function test496_post(tag, subtype) {
    var before = __city_message_count()
    city.create_chain_event({ tag_id: tag, type: EVENT_TYPE_MESSAGE, subtype: subtype, trigger: EVENT_TRIGGER_ONCE })
        .execute()
    var n = __city_message_count()
    if (n != before + 1) {
        return { posted: false }
    }
    var last = n - 1
    return { posted: true, mm: __city_message_mm_text_id(last), title: __city_message_eventmsg_title_id(last),
        body: __city_message_eventmsg_body_id(last), phrase: __test_last_message_eventmsg_phrase_id() }
}

function test496_check(what, got, template, title, body, phrase) {
    var mm = __lang_get_message_uid(template)
    if (!mm || !got.posted || got.mm != mm || got.title != title || got.body != body
        || (phrase !== undefined && got.phrase != phrase)) {
        test496_fail(what + ': posted=' + got.posted + ' mm=' + got.mm + '/' + mm + ' title=' + got.title + '/' + title
            + ' body=' + got.body + '/' + body + ' phrase=' + got.phrase + '/' + phrase)
        return false
    }
    return true
}

// MESSAGE subtype 1 is OG EVENT_MESSAGE_BATTLE_WON; the city-status name for 1 stays an alias.
function test496_subtype_names() {
    if (EVENT_SUBTYPE_MSG_BATTLE_WON !== 1 || EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED !== 1) {
        test496_fail('subtype 1 names: battle_won=' + EVENT_SUBTYPE_MSG_BATTLE_WON
            + ' conquered=' + EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED)
        return
    }
    __log_marker('event_messages_og_battle_won_ok')
}

function test496_templates() {
    var ok = test496_check('city saved', test496_post(49601, EVENT_SUBTYPE_MSG_CITY_SAVED), 'message_template_city_saved',
            PHRASE_eg_city_saved_title, PHRASE_eg_city_saved_initial_announcement, PHRASE_eg_city_saved_no_reason_A)
        && test496_check('battle won', test496_post(49604, EVENT_SUBTYPE_MSG_BATTLE_WON), 'message_template_distant_battle_won',
            PHRASE_battle_won_title, PHRASE_battle_won_initial_announcement, PHRASE_battle_won_no_reason_A)
        && test496_check('battle lost', test496_post(49602, EVENT_SUBTYPE_MSG_DISTANT_BATTLE_LOST), 'message_template_general',
            PHRASE_battle_lost_title, PHRASE_battle_lost_initial_announcement, PHRASE_battle_lost_no_reason_A)
        && test496_check('acknowledgement', test496_post(49603, EVENT_SUBTYPE_MSG_ACKNOWLEDGEMENT), 'message_template_general',
            PHRASE_acknowledgement_title, PHRASE_acknowledgement_initial_announcement,
            PHRASE_acknowledgement_no_reason_A)
    if (ok) {
        __log_marker('event_messages_og_templates_ok')
    }
}

function run_test() {
    __log_info_native('[test:496] OG event messages')
    test_reload_city_session('data/default.map')
    test496_subtype_names()
    test496_templates()
    __test_signal_ready()
}

function check_valid() {
    var markers = ['event_messages_og_battle_won_ok', 'event_messages_og_templates_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:496] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}
