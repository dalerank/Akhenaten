// Register figure_birds_hunter METAINFO (BH2).
// Markers:
//   [test-marker] birds_hunter_registered_ok

var __test531_ok = false

function run_test() {
    __log_info_native('[test:531] birds hunter registration')
    test_ensure_city_session('data/default.map')

    var bid = test_building_place(BUILDING_HUNTING_LODGE, -1, -1)
    if (!bid) {
        __log_info_native('[test:531] FAIL: lodge place failed')
        __test_signal_ready()
        return
    }
    var t = __building_tile(bid)
    if (!t) {
        __log_info_native('[test:531] FAIL: lodge tile missing')
        __test_signal_ready()
        return
    }

    var hunter = test_figure_create(FIGURE_BIRDS_HUNTER, t.x + 2, t.y)
    if (!hunter || !__figure_is_valid(hunter) || __figure_get_type(hunter) != FIGURE_BIRDS_HUNTER) {
        __log_info_native('[test:531] FAIL: FIGURE_BIRDS_HUNTER create failed')
        __test_signal_ready()
        return
    }
    test_figure_set_home(hunter, bid)
    __test_figure_set_action(hunter, ACTION_8_RECALCULATE)
    var mid_no_target = __test_hunter_force_shot(hunter)
    if (mid_no_target) {
        __log_info_native('[test:531] FAIL: force_shot without target should return 0')
        __test_signal_ready()
        return
    }
    __log_marker('birds_hunter_registered_ok')

    __test531_ok = true
    __log_info_native('[test:531] PASS')
    __test_signal_ready()
}

function check_valid() {
    if (!__test531_ok) {
        __log_info_native('[test:531] run_test did not complete')
        return false
    }
    if (!__test_find_inlog('[test-marker] birds_hunter_registered_ok')) {
        __log_info_native('[test:531] missing marker: birds_hunter_registered_ok')
        return false
    }
    return true
}
