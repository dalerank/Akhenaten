// Mods: a save records the enabled mods (svx chunk "mods"); loading it with another set of mods
// enabled logs a warning and changes nothing (no mod is switched on or off by the load).
// Markers:
//   [test-marker] mods_saveload_ok

function t373_fail(msg) {
    __log_info_native('[test:373] FAIL: ' + msg)
}

function run_test() {
    if (!test_reload_city_session('data/default.map')) {
        t373_fail('map load')
        __test_signal_ready()
        return
    }

    var save_name = 'test_373_mods.svx'
    mods.toggle('akh_test_mod')
    mods.remount()
    __test_pump_frames(3)
    var written = __game_write_savegame(save_name)

    mods.toggle('akh_test_mod')
    mods.remount()

    if (!written) {
        t373_fail('save not written')
    } else if (!__game_load_savegame(save_name)) {
        t373_fail('save not loaded')
    } else if (mods.enabled('akh_test_mod')) {
        t373_fail('loading the save enabled the mod')
    } else if (!__test_find_inlog('[mods] the save was made with mods: akh_test_mod; enabled now: none')) {
        t373_fail('mods mismatch not reported')
    } else {
        __log_marker('mods_saveload_ok')
    }
    __game_delete_savegame(save_name)
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] mods_saveload_ok')
}
