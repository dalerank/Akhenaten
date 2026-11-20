// ED5: custom-map play loads Maps/*.meta.js invasions before g_invasions.init().
// Markers:
//   [test-marker] editor_invasion_meta_play_ok

function run_test() {
    __log_info_native('[test:091] editor invasion meta play')

    if (!game.init_editor()) {
        __log_info_native('[test:091] init_editor failed')
        __test_signal_ready()
        return
    }

    if (!__test_editor_invasion_meta_play()) {
        __log_info_native('[test:091] editor_invasion_meta_play failed')
        __test_signal_ready()
        return
    }

    __log_marker('editor_invasion_meta_play_ok')
    __test_signal_ready()
}

function check_valid() {
    return !!__test_find_inlog('[test-marker] editor_invasion_meta_play_ok')
}
