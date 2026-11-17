// A file in data/ next to the executable resolves even when neither the game data folder nor the working directory
// has it (flatpak menu launch: the working directory is the home folder, the engine data is in /app/bin/data).
// Markers:
//   [test-marker] engine_data_next_to_exe_ok

var t770_rel = 'data/akh_test_770_engine_data.txt'

function t770_fail(msg) {
    __log_info_native('[test:770] FAIL: ' + msg)
}

function t770_same_file(a, b) {
    return a.replace(/\\/g, '/').replace(/\/+/g, '/').toLowerCase() == b.replace(/\\/g, '/').replace(/\/+/g, '/').toLowerCase()
}

function run_test() {
    var exe_file = __test_exe_dir_path(t770_rel)
    if (!exe_file || !__test_file_write_text(exe_file, 'akhenaten')) {
        t770_fail('cannot write ' + exe_file)
        __test_signal_ready()
        return
    }

    var resolved = __test_vfs_resolve(t770_rel)
    __log_info_native('[test:770] exe file ' + exe_file + ' resolved ' + resolved)
    if (!t770_same_file(resolved, exe_file)) {
        t770_fail('resolved ' + resolved + ', want ' + exe_file)
    } else if (__test_file_size(resolved) != 9) {
        t770_fail('size ' + __test_file_size(resolved))
    } else {
        __log_marker('engine_data_next_to_exe_ok')
    }

    __test_file_remove(exe_file)
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] engine_data_next_to_exe_ok')
}
