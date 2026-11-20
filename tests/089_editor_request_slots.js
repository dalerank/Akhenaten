// ED4a: editor request slots ↔ EVENT_TYPE_REQUEST (tag 8000+slot) in event_list.
// Markers:
//   [test-marker] editor_request_slots_ok

function run_test() {
    __log_info_native('[test:089] editor request slots')

    if (!game.init_editor()) {
        __log_info_native('[test:089] init_editor failed')
        __test_signal_ready()
        return
    }

    if (!__test_editor_request_roundtrip()) {
        __log_info_native('[test:089] editor_request_roundtrip failed')
        __test_signal_ready()
        return
    }

    __log_marker('editor_request_slots_ok')
    __test_signal_ready()
}

function check_valid() {
    return !!__test_find_inlog('[test-marker] editor_request_slots_ok')
}
