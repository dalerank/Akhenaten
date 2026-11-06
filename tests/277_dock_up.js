// BUILDING_DOCK_UP (OG BUILD_DOCK2): same dock class / dcast as BUILDING_DOCK.
// Markers:
//   [test-marker] dock_up_create_ok
//   [test-marker] dock_up_dcast_ok
//   [test-marker] dock_up_place_ok

var __test277_ok = {
    create: false,
    dcast: false,
    place: false
}

function run_test() {
    __log_info_native('[test:277] dock_up')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    // OG: Dock 2 shares the dock allow flag.
    __scenario_building_allow(BUILDING_DOCK, true)
    if (!__scenario_building_allowed(BUILDING_DOCK_UP)) {
        __log_info_native('[test:277] DOCK_UP should be allowed when DOCK is')
        __test_signal_ready()
        return
    }

    var bid = __test_building_create(BUILDING_DOCK_UP, -1, -1)
    if (!bid) {
        __log_info_native('[test:277] create failed')
        __test_signal_ready()
        return
    }
    var b = city.get_building(bid)
    if (!b || b.type != BUILDING_DOCK_UP) {
        __log_info_native('[test:277] type want DOCK_UP, got ' + (b ? b.type : 'null'))
        __test_signal_ready()
        return
    }
    __log_marker('dock_up_create_ok')
    __test277_ok.create = true

    var dock = city.get_dock(bid)
    if (!dock) {
        __log_info_native('[test:277] get_dock / dcast failed')
        __test_signal_ready()
        return
    }
    __log_marker('dock_up_dcast_ok')
    __test277_ok.dcast = true

    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __scenario_building_allow(BUILDING_DOCK, true)
    var place_bid = test_shoreline_building_place(BUILDING_DOCK_UP, 3)
    if (!place_bid) {
        __log_info_native('[test:277] shoreline place failed')
        __test_signal_ready()
        return
    }
    if (!test_assert_building_placed(place_bid, BUILDING_DOCK_UP, 'test:277')) {
        __test_signal_ready()
        return
    }
    if (!city.get_dock(place_bid)) {
        __log_info_native('[test:277] placed dock_up not dcastable')
        __test_signal_ready()
        return
    }
    __log_marker('dock_up_place_ok')
    __test277_ok.place = true

    __test_signal_ready()
}

function check_valid() {
    return __test277_ok.create
        && __test277_ok.dcast
        && __test277_ok.place
        && __test_find_inlog('[test-marker] dock_up_create_ok')
        && __test_find_inlog('[test-marker] dock_up_dcast_ok')
        && __test_find_inlog('[test-marker] dock_up_place_ok')
}
