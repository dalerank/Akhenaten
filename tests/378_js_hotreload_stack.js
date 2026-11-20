// Regression: MuJS value-stack leak across script hot-reload.
//
// js_register_game_handlers re-binds every [console_command=…] modifier. The
// registry helper used to js_getglobal() the function and never pop it, so each
// sync leaked ~30 slots. With JS_STACKSIZE=256 that overflowed after ~10
// mixed-folder saves during config::refresh / UI widget load (stackoverflow →
// Fatal program exit).
//
// This test re-registers handlers and reloads a real script far past that
// threshold and asserts the stack depth is unchanged.
// Markers:
//   [test-marker] hotreload_handlers_ok
//   [test-marker] hotreload_file_ok
//   [test-marker] hotreload_handlers_stack …
//   [test-marker] hotreload_file_stack …

function run_test() {
    __log_info_native('[test:378] js hotreload stack stability')

    // Well past the old crash threshold (~8–10 reloads).
    var iterations = 20

    if (!__test_js_hotreload_handlers_stack_ok(iterations)) {
        __log_info_native('[test:378] handlers stack grew across re-register')
        __test_signal_ready()
        return
    }
    __log_marker('hotreload_handlers_ok')

    // Full path: queue + exec + register handlers + config::refresh (UI reload).
    // console_commands.js is the file that defines the leaking modifiers.
    if (!__test_js_hotreload_file_stack_ok(':console_commands.js', iterations)) {
        __log_info_native('[test:378] file hotreload stack grew')
        __test_signal_ready()
        return
    }
    __log_marker('hotreload_file_ok')

    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'hotreload_handlers_ok',
        'hotreload_file_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:378] missing marker: ' + marker)
            return false
        }
    }
    return true
}
