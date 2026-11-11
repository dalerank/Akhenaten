// Mods: the folder mod tests/fixtures/mods/akh_test_mod is listed, and enabling it applies
// 1) a config override from a new file (building_well.max_service = 777),
// 2) a script override of a built-in path (speech.js defines akh_test_mod_speech).
// Disabling it rebuilds the VM without the mod, so check_valid (reloaded by the runner) sees the
// built-in values again.
// Under --integraltests mods come only from --mods (default tests/fixtures/mods), so the
// user's own mods and enabled list never reach the suite.
// Markers:
//   [test-marker] mods_fixture_listed
//   [test-marker] mods_fixture_overrides_ok

var t330_mod = 'akh_test_mod'

function t330_fail(msg) {
    __log_info_native('[test:330] FAIL: ' + msg)
}

function t330_listed(id) {
    for (var i = 0; i < mods.count(); i++) {
        if (mods.name(i) == id) {
            return true
        }
    }
    return false
}

function t330_well_max_service() {
    return city.get_building_params_by_type(BUILDING_WELL).max_service
}

function run_test() {
    if (!t330_listed(t330_mod)) {
        t330_fail('fixture mod is not listed')
        __test_signal_ready()
        return
    }
    __log_marker('mods_fixture_listed')

    if (mods.enabled(t330_mod)) {
        t330_fail('fixture mod is enabled before the test enabled it')
    }

    var before = t330_well_max_service()
    mods.toggle(t330_mod)
    mods.remount()
    __test_pump_frames(3)

    var after = t330_well_max_service()
    if (!mods.enabled(t330_mod)) {
        t330_fail('mod not enabled after toggle')
    } else if (!__test_find_inlog('[test-marker] akh_test_mod loaded')) {
        t330_fail('mod script did not run')
    } else if (after != 777) {
        t330_fail('config override not applied: max_service ' + before + ' -> ' + after)
    } else if (__js_global('akh_test_mod_speech') !== 'mod'
               || !__test_find_inlog('[test-marker] akh_test_mod speech.js override')) {
        t330_fail('speech.js override did not run')
    } else {
        __log_marker('mods_fixture_overrides_ok')
    }

    mods.toggle(t330_mod)
    mods.remount()
    __test_signal_ready()
}

function check_valid() {
    if (!__test_find_inlog('[test-marker] mods_fixture_listed')
        || !__test_find_inlog('[test-marker] mods_fixture_overrides_ok')) {
        return false
    }
    if (mods.enabled(t330_mod)) {
        t330_fail('mod still enabled after the second toggle')
        return false
    }
    if (t330_well_max_service() == 777 || __js_global('akh_test_mod_speech') !== undefined) {
        t330_fail('mod overrides survived disabling: max_service ' + t330_well_max_service())
        return false
    }
    return true
}
