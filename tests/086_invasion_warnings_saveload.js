// B3: invasion_warnings chunk round-trip (months_to_go / handled / pos).
// B4: EVENT_TYPE_MESSAGE uses event.reasons via rand_reason (not hardcoded only).
// Markers:
//   [test-marker] invasion_warning_seed_ok
//   [test-marker] invasion_warning_saveload_ok
//   [test-marker] message_phrase_reason_ok
//   [test-marker] message_phrase_fallback_ok

function run_test() {
    __log_info_native('[test:086] invasion warnings saveload + message phrases')
    test_ensure_city_session('data/default.map')

    var idx = 1
    __test_invasion_warning_force(idx, 17, 2, 1)
    if (__test_invasion_warning_months_to_go(idx) !== 17
        || __test_invasion_warning_handled(idx) !== 1
        || __test_invasion_warning_pos_x(idx) !== 11) {
        __log_info_native('[test:086] seed failed months='
            + __test_invasion_warning_months_to_go(idx)
            + ' handled=' + __test_invasion_warning_handled(idx)
            + ' x=' + __test_invasion_warning_pos_x(idx))
        __test_signal_ready()
        return
    }
    __log_marker('invasion_warning_seed_ok')

    var save_name = 'test_169_invasion_warnings.svx'
    if (!__test_save_memory(save_name)) {
        __log_info_native('[test:086] write_savegame failed')
        __test_signal_ready()
        return
    }
    if (!__test_load_memory(save_name)) {
        __test_drop_memory_save(save_name)
        __log_info_native('[test:086] load_savegame failed')
        __test_signal_ready()
        return
    }
    __test_drop_memory_save(save_name)

    if (__test_invasion_warning_months_to_go(idx) !== 17
        || __test_invasion_warning_handled(idx) !== 1
        || __test_invasion_warning_pos_x(idx) !== 11) {
        __log_info_native('[test:086] after load months='
            + __test_invasion_warning_months_to_go(idx)
            + ' handled=' + __test_invasion_warning_handled(idx)
            + ' x=' + __test_invasion_warning_pos_x(idx))
        __test_signal_ready()
        return
    }
    __log_marker('invasion_warning_saveload_ok')

    // B4: ACK uses message_template_general (present under --no-resource).
    var want = PHRASE_acknowledgement_reason_B
    var ev = city.create_chain_event({
        tag_id: 16940,
        type: EVENT_TYPE_MESSAGE,
        subtype: EVENT_SUBTYPE_MSG_ACKNOWLEDGEMENT,
        trigger: EVENT_TRIGGER_ONCE
    })
    __city_request_set_reasons(16940, want, -1, -1, -1)
    ev.execute()
    var got = __test_last_message_eventmsg_phrase_id()
    if (got !== want) {
        __log_info_native('[test:086] phrase want=' + want + ' got=' + got
            + ' msgs=' + __city_message_count())
        __test_signal_ready()
        return
    }
    __log_marker('message_phrase_reason_ok')

    // B4: empty reasons → subtype default (acknowledgement_no_reason_A)
    city.create_chain_event({
        tag_id: 16941,
        type: EVENT_TYPE_MESSAGE,
        subtype: EVENT_SUBTYPE_MSG_ACKNOWLEDGEMENT,
        trigger: EVENT_TRIGGER_ONCE
    }).execute()
    got = __test_last_message_eventmsg_phrase_id()
    if (got !== PHRASE_acknowledgement_no_reason_A) {
        __log_info_native('[test:086] fallback want=' + PHRASE_acknowledgement_no_reason_A
            + ' got=' + got + ' msgs=' + __city_message_count())
        __test_signal_ready()
        return
    }
    __log_marker('message_phrase_fallback_ok')
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] invasion_warning_seed_ok')
        && __test_find_inlog('[test-marker] invasion_warning_saveload_ok')
        && __test_find_inlog('[test-marker] message_phrase_reason_ok')
        && __test_find_inlog('[test-marker] message_phrase_fallback_ok')
}
