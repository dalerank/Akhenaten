// Verifies that window_file_dialog_load_show(FILE_TYPE_SAVED_GAME) opens
// file_dialog_load. The init handler logs
// "[test-marker] window_show:file_dialog_load".

function run_test() {
    __log_info_native('[test:07] opening load savegame file dialog')
    test_ensure_city_session('data/default.map')
    window_file_dialog_load_show(FILE_TYPE_SAVED_GAME)
    __test_pump_frames(10)

    window_go_back()
    __test_pump_frames(2)

    __test_signal_ready()
}

function check_valid() {
    var marker = '[test-marker] window_show:file_dialog_load'
    if (!__test_find_inlog(marker)) {
        __log_info_native('[test:07] missing marker: ' + marker)
        return false
    }
    return true
}
