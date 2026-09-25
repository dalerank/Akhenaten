// Bug report body always includes Recent errors + Recent log (info+ session tail).

function run_test() {
    __log_info_native('[test:207] bug report diagnostics sections')

    var tag = 'bug_report_diag_marker_207'
    __log_info_native(tag)

    var diag = report_bug_diagnostics()
    if (!diag || diag.indexOf('Recent errors:') < 0) {
        __log_info_native('[test:207] missing Recent errors section')
        __test_signal_ready()
        return
    }
    if (diag.indexOf('Recent log:') < 0) {
        __log_info_native('[test:207] missing Recent log section')
        __test_signal_ready()
        return
    }
    if (diag.indexOf(tag) < 0) {
        __log_info_native('[test:207] Recent log missing marker: ' + tag)
        __test_signal_ready()
        return
    }

    var tail = __game_recent_log_tail(80)
    if (!tail || tail.indexOf(tag) < 0) {
        __log_info_native('[test:207] __game_recent_log_tail missing marker')
        __test_signal_ready()
        return
    }

    __log_marker('bug_report_diagnostics_ok')
    __test_signal_ready()
}

function check_valid() {
    if (!__test_find_inlog('[test-marker] bug_report_diagnostics_ok')) {
        __log_info_native('[test:207] missing marker: bug_report_diagnostics_ok')
        return false
    }
    return true
}
