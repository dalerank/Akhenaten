// Integral tests take the data directory only from the command line: akhenaten.cfg (which usually
// holds the developer's Steam path) and Steam/GOG detection must not leak into a run, so a local
// run without a positional data dir sees exactly what CI sees: no Pharaoh art.

var __test323_ok = false

function test323_fail(msg) {
    __log_info_native('[test:323] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:323] resources hermetic')
    var dir = __test_data_dir()
    var art = __test_pak_loaded('SprMain')
    __log_info_native('[test:323] data_dir=' + dir + ' from_cli=' + __test_data_dir_from_cli()
        + ' paks_loaded=' + __test_paks_loaded() + ' pharaoh_art=' + art)

    if (__test_data_dir_from_cli()) {
        __log_marker('test323_data_dir_from_cli')
    } else {
        if (art) {
            return test323_fail('Pharaoh art loaded without a data dir on the command line: ' + dir)
        }
        if (dir.toLowerCase().indexOf('steamapps') >= 0) {
            return test323_fail('data dir came from Steam/cfg: ' + dir)
        }
        __log_marker('test323_no_data')
    }

    __test323_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test323_ok
        && (__test_find_inlog('[test-marker] test323_no_data')
            || __test_find_inlog('[test-marker] test323_data_dir_from_cli'))
}
