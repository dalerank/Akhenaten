// Packs load only on the main thread: a render worker that hits an unloaded pack queues it and draws
// without it; the next frame's image_paks_pump loads it on the main thread.

var __test327_ok = false

function test327_fail(msg) {
    __log_info_native('[test:327] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:327] pak load main thread')
    var art = __test_pak_loaded('Pharaoh_General')

    if (!__test_pak_ensure_from_worker('Pharaoh_General')) {
        return test327_fail('a worker thread loaded the pack or did not queue it')
    }
    __log_marker('test327_worker_queued')

    __test_pump_frames(2)
    if (art && !__test_pak_loaded('Pharaoh_General')) {
        return test327_fail('the main thread did not load the queued pack')
    }
    __log_marker(art ? 'test327_main_loaded' : 'test327_main_loaded_skipped:no_resource')

    __test327_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test327_ok
        && __test_find_inlog('[test-marker] test327_worker_queued')
        && (__test_find_inlog('[test-marker] test327_main_loaded')
            || __test_find_inlog('[test-marker] test327_main_loaded_skipped:no_resource'))
}
