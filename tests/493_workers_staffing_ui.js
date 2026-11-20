// WR2 / WR4: staffing display smoke — open info panels that need laborers and
// assert workers_text shows a needed count (pottery/firehouse/dock/granary/temple).
// Plaza/garden use terrain info windows (no city-labor row) — not covered here.
// Markers:
//   [test-marker] staffing_pottery_ok
//   [test-marker] staffing_firehouse_ok
//   [test-marker] staffing_dock_ok
//   [test-marker] staffing_granary_ok
//   [test-marker] staffing_temple_ok

function staffing_check_building(name, type) {
    var bid = __test_building_create(type, -1, -1)
    if (!bid) {
        __log_info_native('[test:493] create failed: ' + name)
        return false
    }
    var b = city.get_building(bid)
    if (!b || !b.max_workers) {
        __log_info_native('[test:493] ' + name + ' has no max_workers')
        return false
    }
    b.num_workers = b.max_workers
    __test_show_tile_info(bid)
    __test_pump_frames(8)

    var text = __test_info_ui_text('workers_text')
    if (!text || text.indexOf(String(b.max_workers)) < 0) {
        __log_info_native('[test:493] ' + name + ' workers_text missing needed count: "'
            + text + '" (max=' + b.max_workers + ')')
        window_go_back()
        __test_pump_frames(2)
        return false
    }
    __log_marker('staffing_' + name + '_ok')
    window_go_back()
    __test_pump_frames(2)
    return true
}

function run_test() {
    __log_info_native('[test:493] workers staffing UI smoke')
    test_ensure_city_session('data/default.map')

    var ok = true
    ok = staffing_check_building('pottery', BUILDING_POTTERY_WORKSHOP) && ok
    ok = staffing_check_building('firehouse', BUILDING_FIREHOUSE) && ok
    ok = staffing_check_building('dock', BUILDING_DOCK) && ok
    ok = staffing_check_building('granary', BUILDING_GRANARY) && ok
    ok = staffing_check_building('temple', BUILDING_TEMPLE_OSIRIS) && ok

    if (!ok) {
        __test_signal_ready()
        return
    }
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'staffing_pottery_ok',
        'staffing_firehouse_ok',
        'staffing_dock_ok',
        'staffing_granary_ok',
        'staffing_temple_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:493] missing marker: ' + marker)
            return false
        }
    }
    return true
}

run_test()
