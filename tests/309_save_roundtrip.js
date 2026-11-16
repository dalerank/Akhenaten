// Save fidelity:
// 1) a running city written as .svx, loaded back and written again must give the same chunks;
//    differing chunks are logged as "[roundtrip] ... diff <chunk>" with the first differing offsets.
// Original .sav loading is covered by tests/49*_og_save_*.js.
// Markers:
//   [test-marker] save_roundtrip_ok

var __t309_ticks = 2000

function t309_fail(msg) {
    __log_info_native('[test:309] FAIL: ' + msg)
}

function t309_build_city() {
    var types = [BUILDING_STORAGE_YARD, BUILDING_GRANARY, BUILDING_BAZAAR, BUILDING_FIREHOUSE, BUILDING_GRAIN_FARM]
    for (var i = 0; i < types.length; i++) {
        if (!test_building_place(types[i], -1, -1)) {
            __log_info_native('[test:309] place failed type=' + types[i])
        }
    }
}

function run_test() {
    __log_info_native('[test:309] save roundtrip')

    __test_crt_srand(1)
    if (!test_reload_city_session('data/default.map')) {
        t309_fail('map load')
        __test_signal_ready()
        return
    }
    __test_set_treasury(100000)
    t309_build_city()
    __test_run_ticks(__t309_ticks)
    __test_process_events()

    var bx = 60
    var by = 61
    __city_bookmark_set(1, { x: bx, y: by })

    var diff = __test_save_roundtrip('test_309_roundtrip.svx')
    var mark = __city_bookmark_get(1)
    if (diff !== '') {
        t309_fail('svx roundtrip: ' + diff)
    } else if (mark.x != bx || mark.y != by) {
        t309_fail('bookmark after load ' + mark.x + ',' + mark.y + ' want ' + bx + ',' + by)
    } else {
        __log_marker('save_roundtrip_ok')
    }

    test_reload_city_session('data/default.map')
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('save_roundtrip_ok')
}
