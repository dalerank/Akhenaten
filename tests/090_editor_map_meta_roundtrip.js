// ED4b/ED5: editor map write strips scenario_events; requests/invasions/price/demand in Maps/*.meta.js.
// Markers:
//   [test-marker] editor_map_meta_roundtrip_ok

function run_test() {
    __log_info_native('[test:090] editor map meta roundtrip')

    if (!game.init_editor()) {
        __log_info_native('[test:090] init_editor failed')
        __test_signal_ready()
        return
    }

    if (!__test_editor_map_meta_roundtrip()) {
        __log_info_native('[test:090] editor_map_meta_roundtrip failed')
        __test_signal_ready()
        return
    }

    __log_marker('editor_map_meta_roundtrip_ok')
    __test_signal_ready()
}

function check_valid() {
    return !!__test_find_inlog('[test-marker] editor_map_meta_roundtrip_ok')
}
