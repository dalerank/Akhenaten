// Mods: two enabled mods ship the same speech.js; the one later in id order (akh_test_mod_b)
// wins no matter which was enabled first, and the clash is logged.
// Markers:
//   [test-marker] mods_order_ok

function t331_fail(msg) {
    __log_info_native('[test:331] FAIL: ' + msg)
}

function t331_enable(id) {
    if (!mods.enabled(id)) {
        mods.toggle(id)
    }
    mods.remount()
    __test_pump_frames(3)
}

function run_test() {
    // Enable the winner first: the order must not depend on toggle history.
    t331_enable('akh_test_mod_b')
    t331_enable('akh_test_mod')

    var speech = __js_global('akh_test_mod_speech')
    if (!mods.enabled('akh_test_mod') || !mods.enabled('akh_test_mod_b')) {
        t331_fail('mods not enabled')
    } else if (speech !== 'mod_b') {
        t331_fail('speech.js from the wrong mod: ' + speech)
    } else if (!__test_find_inlog('[mods] conflict speech.js: akh_test_mod_b overrides akh_test_mod')) {
        t331_fail('conflict not logged')
    } else {
        __log_marker('mods_order_ok')
    }

    mods.toggle('akh_test_mod')
    mods.toggle('akh_test_mod_b')
    mods.remount()
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] mods_order_ok')
        && !mods.enabled('akh_test_mod') && !mods.enabled('akh_test_mod_b')
        && __js_global('akh_test_mod_speech') === undefined
}
