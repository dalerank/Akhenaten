// A window resize during a city session re-lays out the script windows once the size settles. That
// relayout re-runs the ui_* scripts and refreshes the window configs only: it must not run the full
// config refresh and game.reload_objects() of a script hot reload, which reset the city's animals and
// objects (a resize right before 534_birds_hunt made its hunter miss).
// Markers:
//   [test-marker] t565_ok
//   [test-marker] t565_fail:<what>

var __t565_ok = false

function t565_fail(what) {
    __log_info_native('[test-marker] t565_fail:' + what)
    __test_signal_ready()
}

function t565_resize(w, h) {
    emit event_display_options_apply_resolution{ w: w, h: h }
    __test_process_events()
    __test_pump_frames(10)
}

function run_test() {
    if (!test_reload_city_session('data/default.map')) {
        t565_fail('load')
        return
    }
    __test_pump_frames(5)

    t565_resize(1000, 700)
    t565_resize(800, 600)

    for (var i = 0; i < 20 && !__test_find_inlog('script reloaded :ui_'); i++) {
        __test_sleep_ms(50)
        __test_pump_frames(2)
    }
    if (!__test_find_inlog('script reloaded :ui_')) {
        t565_fail('no_relayout')
        return
    }
    if (!__test_find_inlog('refresh=windows')) {
        t565_fail('full_reload')
        return
    }

    __log_info_native('[test-marker] t565_ok')
    __t565_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __t565_ok
}
