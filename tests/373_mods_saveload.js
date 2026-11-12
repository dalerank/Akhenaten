// Mods: a save records the enabled mods (svx chunk "mods").
// 1) Loading it with another set of mods enabled logs the mismatch and changes nothing.
// 2) The popup's "Yes" (__test_mods_apply_saved, the popup itself is not shown under tests)
//    enables the save's mods and loads the save again, which then matches.
// Markers:
//   [test-marker] mods_saveload_ok
//   [test-marker] mods_saveload_apply_ok

function t373_fail(msg) {
    __log_info_native('[test:373] FAIL: ' + msg)
}

var t373_save = 'test_373_mods.svx'

function run_test() {
    if (!test_reload_city_session('data/default.map')) {
        t373_fail('map load')
        __test_signal_ready()
        return
    }

    mods.toggle('akh_test_mod')
    mods.remount()
    __test_pump_frames(3)
    var written = __game_write_savegame(t373_save)

    mods.toggle('akh_test_mod')
    mods.remount()

    if (!written) {
        t373_fail('save not written')
    } else if (!__game_load_savegame(t373_save)) {
        t373_fail('save not loaded')
    } else if (mods.enabled('akh_test_mod')) {
        t373_fail('loading the save enabled the mod')
    } else if (!__test_find_inlog('[mods] the save was made with mods: akh_test_mod; enabled now: none')) {
        t373_fail('mods mismatch not reported')
    } else {
        __log_marker('mods_saveload_ok')

        if (!__test_mods_apply_saved()) {
            t373_fail('apply saved mods refused')
        } else {
            __test_pump_frames(6)
            if (!mods.enabled('akh_test_mod')) {
                t373_fail('saved mod not enabled')
            } else if (!__test_find_inlog('[mods] switched to the save\'s mods (akh_test_mod), reloading ' + t373_save)) {
                t373_fail('switch not logged')
            } else if (!__test_find_inlog('[mods] the save\'s mods match the enabled ones: akh_test_mod')) {
                t373_fail('save not reloaded with the saved mods')
            } else if (city.get_building_params_by_type(BUILDING_WELL).max_service != 777) {
                t373_fail('saved mod scripts not active after the reload')
            } else {
                __log_marker('mods_saveload_apply_ok')
            }
        }
    }

    if (mods.enabled('akh_test_mod')) {
        mods.toggle('akh_test_mod')
        mods.remount()
    }
    __game_delete_savegame(t373_save)
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] mods_saveload_ok')
        && __test_find_inlog('[test-marker] mods_saveload_apply_ok')
        && !mods.enabled('akh_test_mod')
}
