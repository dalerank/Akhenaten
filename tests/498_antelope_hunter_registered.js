// Register figure_antelope_hunter / javelin METAINFO (AH2).
// Markers:
//   [test-marker] antelope_hunter_registered_ok
//   [test-marker] antelope_javelin_registered_ok

var __test498_ok = false

function run_test() {
    __log_info_native('[test:498] antelope hunter registration')
    test_ensure_city_session('data/default.map')

    var bid = test_building_place(BUILDING_HUNTING_LODGE, -1, -1)
    if (!bid) {
        __log_info_native('[test:498] FAIL: lodge place failed')
        __test_signal_ready()
        return
    }
    var t = __building_tile(bid)
    if (!t) {
        __log_info_native('[test:498] FAIL: lodge tile missing')
        __test_signal_ready()
        return
    }

    var hunter = test_figure_create(FIGURE_ANTELOPE_HUNTER, t.x + 2, t.y)
    if (!hunter || !__figure_is_valid(hunter) || __figure_get_type(hunter) != FIGURE_ANTELOPE_HUNTER) {
        __log_info_native('[test:498] FAIL: FIGURE_ANTELOPE_HUNTER create failed')
        __test_signal_ready()
        return
    }
    // Registered hunter class: force_shot rejects only when no target (not wrong type).
    test_figure_set_home(hunter, bid)
    __test_figure_set_action(hunter, ACTION_8_RECALCULATE)
    var mid_no_target = __test_hunter_force_shot(hunter)
    if (mid_no_target) {
        __log_info_native('[test:498] FAIL: force_shot without target should return 0')
        __test_signal_ready()
        return
    }
    __log_marker('antelope_hunter_registered_ok')

    var jav = test_figure_create(FIGURE_ANTELOPE_HUNTER_JAVELIN, t.x + 3, t.y)
    if (!jav || !__figure_is_valid(jav) || __figure_get_type(jav) != FIGURE_ANTELOPE_HUNTER_JAVELIN) {
        __log_info_native('[test:498] FAIL: FIGURE_ANTELOPE_HUNTER_JAVELIN create failed')
        __test_signal_ready()
        return
    }
    __log_marker('antelope_javelin_registered_ok')

    __test498_ok = true
    __log_info_native('[test:498] PASS')
    __test_signal_ready()
}

function check_valid() {
    if (!__test498_ok) {
        __log_info_native('[test:498] run_test did not complete')
        return false
    }
    var markers = [
        '[test-marker] antelope_hunter_registered_ok',
        '[test-marker] antelope_javelin_registered_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog(markers[i])) {
            __log_info_native('[test:70] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}
