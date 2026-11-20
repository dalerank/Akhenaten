// ED6: editor entry + map write/load round-trip (slice A–B).
// Hermetic: blank scenario → write Maps/_editor_rt.map → load → assert active.

var EDITOR_RT_MAP = "Maps/_editor_rt.map"

function run_test() {
    if (!game.init_editor()) {
        __log_info_native("[test:085] game.init_editor failed")
        __test_signal_ready()
        return
    }

    if (!game.editor_is_active()) {
        __log_info_native("[test:085] editor_is_active false after init")
        __test_signal_ready()
        return
    }

    var wid = __game_window_get_id()
    if (wid !== "window_editor_map" && wid !== "window_editor_top_menu") {
        __log_info_native("[test:085] unexpected window: " + wid)
        __test_signal_ready()
        return
    }

    if (!game.editor_write_scenario(EDITOR_RT_MAP)) {
        __log_info_native("[test:085] editor_write_scenario failed")
        __test_signal_ready()
        return
    }

    if (!game.file_exists(EDITOR_RT_MAP)) {
        __log_info_native("[test:085] written map missing on disk")
        __test_signal_ready()
        return
    }

    if (!game.editor_load_scenario(EDITOR_RT_MAP)) {
        __log_info_native("[test:085] editor_load_scenario failed")
        __test_signal_ready()
        return
    }

    if (!game.editor_is_active()) {
        __log_info_native("[test:085] editor inactive after load")
        __test_signal_ready()
        return
    }

    __log_marker("editor_map_roundtrip_ok")
    game.delete_map("_editor_rt.map")
    __test_signal_ready()
}

function check_valid() {
    if (__test_find_inlog("editor_map_roundtrip_ok")) {
        return true
    }
    __log_info_native("[test:085] missing editor_map_roundtrip_ok marker")
    return false
}
