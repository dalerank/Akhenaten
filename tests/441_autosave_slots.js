// AS4: autosave slot helper — format names + pick missing/oldest (no .svx IO).
// Related: REMAKE_AUTOSAVE_SLOTS_PLAN.md
//
// Markers:
//   [test-marker] autosave_format_ok
//   [test-marker] autosave_pick_ok

function run_test() {
    __log_info_native('[test:441] autosave slots helper')

    if (__test_autosave_format(1, 1) !== 'autosave_month.svx') {
        __log_info_native('[test:441] N=1 format fail: ' + __test_autosave_format(1, 1))
        __test_signal_ready()
        return
    }
    if (__test_autosave_format(1, 9) !== 'autosave_month.svx') {
        __log_info_native('[test:441] N=1 ignore slot fail')
        __test_signal_ready()
        return
    }
    if (__test_autosave_format(3, 1) !== 'autosave_month_1.svx'
        || __test_autosave_format(3, 2) !== 'autosave_month_2.svx'
        || __test_autosave_format(3, 3) !== 'autosave_month_3.svx') {
        __log_info_native('[test:441] N=3 format fail')
        __test_signal_ready()
        return
    }
    __log_marker('autosave_format_ok')

    if (__test_autosave_pick(3, 0, 0, 0, 0) !== 1) {
        __log_info_native('[test:441] all missing pick fail')
        __test_signal_ready()
        return
    }
    if (__test_autosave_pick(3, 1, 10, 0, 0) !== 2) {
        __log_info_native('[test:441] prefer missing pick fail')
        __test_signal_ready()
        return
    }
    if (__test_autosave_pick(3, 3, 10, 20, 0) !== 3) {
        __log_info_native('[test:441] third missing pick fail')
        __test_signal_ready()
        return
    }
    if (__test_autosave_pick(3, 7, 10, 5, 20) !== 2) {
        __log_info_native('[test:441] oldest mtime pick fail')
        __test_signal_ready()
        return
    }
    if (__test_autosave_pick(3, 7, 5, 5, 20) !== 1) {
        __log_info_native('[test:441] mtime tie pick fail')
        __test_signal_ready()
        return
    }
    __log_marker('autosave_pick_ok')

    __test_signal_ready()
}

function check_valid() {
    var markers = ['autosave_format_ok', 'autosave_pick_ok']
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:441] missing marker: ' + marker)
            return false
        }
    }
    return true
}
