// image_get caches only what it returns (a miss used to cache image 98 of Pharaoh_General, so the
// second lookup of a missing id returned someone else's sprite), image_id_from_group keeps a missing
// pack missing at any offset, and image_unload_pak drops the handle, the status and the cache range.

var __test362_ok = false

function test362_fail(msg) {
    __log_info_native('[test:362] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:362] image pak unload')
    var art = __test_pak_loaded('Pharaoh_General')

    var missing = 66000
    if (__test_image_exists(missing) || __test_image_exists(missing) || __test_image_cached(missing)) {
        return test362_fail('a missing image id resolved or got cached')
    }
    __log_marker('test362_miss_not_cached')

    var id = __test_image_id_from_group(PACK_GENERAL, 0, 5)
    if (!art) {
        if (id !== -1) {
            return test362_fail('missing pack + offset gave ' + id + ', expected -1')
        }
        __log_marker('test362_missing_group_offset_ok')
        __log_marker('test362_unload_art_skipped:no_resource')
        __test362_ok = true
        return __test_signal_ready()
    }

    if (id <= 0) {
        return test362_fail('Pharaoh_General group 0 + 5 gave ' + id)
    }
    __log_marker('test362_missing_group_offset_ok')

    if (!__test_image_exists(id) || !__test_image_cached(id)) {
        return test362_fail('image ' + id + ' not resolved/cached')
    }
    __test_image_unload_pak('Pharaoh_General')
    if (__test_pak_loaded('Pharaoh_General') || __test_image_cached(id)) {
        return test362_fail('unload left the pack loaded or its cache filled')
    }
    if (!__test_image_exists(id) || !__test_pak_loaded('Pharaoh_General')) {
        return test362_fail('pack did not reload after unload')
    }
    __log_marker('test362_unload_ok')

    __test362_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test362_ok
        && __test_find_inlog('[test-marker] test362_miss_not_cached')
        && __test_find_inlog('[test-marker] test362_missing_group_offset_ok')
        && (__test_find_inlog('[test-marker] test362_unload_ok')
            || __test_find_inlog('[test-marker] test362_unload_art_skipped:no_resource'))
}
