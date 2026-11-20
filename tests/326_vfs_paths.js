// Paths: a UTF-8 (Cyrillic) user dir must reach the file system as UTF-8 (Windows: activeCodePage
// manifest), "data/sprmain.sg3" finds "Data/Sub/SprMain.SG3" on case-sensitive file systems, and
// vfs::path reports instead of silently cutting a path at its length limit.

var __test326_ok = false

function test326_fail(msg) {
    __log_info_native('[test:326] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:326] vfs paths')

    if (!__test_vfs_utf8_roundtrip()) {
        return test326_fail('a file with a UTF-8 name was not created under that name')
    }
    __log_marker('test326_utf8_ok')

    if (!__test_vfs_case_probe()) {
        return test326_fail('case-insensitive lookup of data/sub/sprmain.sg3 failed')
    }
    __log_marker('test326_case_ok')

    var len = __test_vfs_path_len(300)
    if (!__test_find_inlog('probably truncated')) {
        return test326_fail('a 300-char path was cut to ' + len + ' without an error in the log')
    }
    __log_marker('test326_truncation_reported')

    __test326_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test326_ok
        && __test_find_inlog('[test-marker] test326_utf8_ok')
        && __test_find_inlog('[test-marker] test326_case_ok')
        && __test_find_inlog('[test-marker] test326_truncation_reported')
}
