// Mods: a mod whose script throws is reported broken, and the error does not stop the rest of
// the JS (the next mod queued in the same sync still runs, calls into JS keep working).
// Markers:
//   [test-marker] mods_broken_ok

function t372_fail(msg) {
    __log_info_native('[test:372] FAIL: ' + msg)
}

function run_test() {
    mods.toggle('akh_test_broken_mod')
    mods.toggle('akh_test_mod')
    mods.remount()
    __test_pump_frames(3)

    if (!__test_find_inlog('[test-marker] akh_test_broken_mod start')) {
        t372_fail('broken mod did not run')
    } else if (!mods.broken('akh_test_broken_mod')) {
        t372_fail('broken mod not reported')
    } else if (mods.broken('akh_test_mod')) {
        t372_fail('working mod reported broken')
    } else if (__js_global('akh_test_mod_speech') !== 'mod'
               || city.get_building_params_by_type(BUILDING_WELL).max_service != 777) {
        t372_fail('scripts after the failing one did not run')
    } else {
        __log_marker('mods_broken_ok')
    }

    mods.toggle('akh_test_broken_mod')
    mods.toggle('akh_test_mod')
    mods.remount()
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] mods_broken_ok')
        && __test_find_inlog('[mods] akh_test_broken_mod is broken')
        && !mods.enabled('akh_test_broken_mod') && !mods.enabled('akh_test_mod')
        && city.get_building_params_by_type(BUILDING_WELL).max_service != 777
}
