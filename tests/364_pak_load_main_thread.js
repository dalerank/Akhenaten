// Packs load only on the main thread: a render worker that hits an unloaded pack queues it and draws
// without it; the next frame's image_paks_pump loads it on the main thread.

var __test364_ok = false

function test364_fail(msg) {
    __log_info_native('[test:364] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:364] pak load main thread')
    var art = __test_pak_loaded('Pharaoh_General')

    if (!__test_pak_ensure_from_worker('Pharaoh_General')) {
        return test364_fail('a worker thread loaded the pack or did not queue it')
    }
    __log_marker('test364_worker_queued')

    __test_pump_frames(2)
    if (art && !__test_pak_loaded('Pharaoh_General')) {
        return test364_fail('the main thread did not load the queued pack')
    }
    __log_marker(art ? 'test364_main_loaded' : 'test364_main_loaded_skipped:no_resource')

    __test364_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test364_ok
        && __test_find_inlog('[test-marker] test364_worker_queued')
        && (__test_find_inlog('[test-marker] test364_main_loaded')
            || __test_find_inlog('[test-marker] test364_main_loaded_skipped:no_resource'))
}
