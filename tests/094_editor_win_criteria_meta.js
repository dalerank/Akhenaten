// ED5: win_criteria persist in map scenario_info and mirror/override via Maps/*.meta.js.
// Markers:
//   [test-marker] editor_win_criteria_meta_ok

function run_test() {
    __log_info_native('[test:094] editor win_criteria meta')

    if (!game.init_editor()) {
        __log_info_native('[test:094] init_editor failed')
        __test_signal_ready()
        return
    }

    if (!__test_editor_win_criteria_meta()) {
        __log_info_native('[test:094] editor_win_criteria_meta failed')
        __test_signal_ready()
        return
    }

    __log_marker('editor_win_criteria_meta_ok')
    __test_signal_ready()
}

function check_valid() {
    return !!__test_find_inlog('[test-marker] editor_win_criteria_meta_ok')
}
