// Alexandria's Library — place 13×14 clear land; reject second unfinished; finish → rating.

function run_test() {
    __log_info_native('[test:121] alexandria library place + finish rating')
    test_reload_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_ALEXANDRIA_LIBRARY)) {
        __scenario_building_allow(BUILDING_ALEXANDRIA_LIBRARY, true)
    }

    __test_set_treasury(500000)

    var cx = 40
    var cy = 40

    var bid = test_building_place(BUILDING_ALEXANDRIA_LIBRARY, cx, cy)
    if (!bid) {
        bid = test_building_place(BUILDING_ALEXANDRIA_LIBRARY, 30, 30)
    }
    if (!bid) {
        __log_info_native('[test:121] failed to place BUILDING_ALEXANDRIA_LIBRARY')
        __test_signal_ready()
        return
    }

    __test_process_events()
    __test_pump_frames(2)

    var b = city.get_building(bid)
    if (!b || b.type != BUILDING_ALEXANDRIA_LIBRARY) {
        __log_info_native('[test:121] placed building type mismatch')
        __test_signal_ready()
        return
    }
    __log_marker('alex_library_placed_ok:' + bid)

    // Second unfinished must be rejected.
    var second = test_building_place(BUILDING_ALEXANDRIA_LIBRARY, cx + 20, cy)
    if (second) {
        __log_info_native('[test:121] unexpected second unfinished place bid=' + second)
        __test_signal_ready()
        return
    }
    __log_marker('alex_library_reject_second_ok')

    var parts = __test_alexandria_library_part_count(bid)
    if (parts != 25) {
        __log_info_native('[test:121] expected 25 parts, got ' + parts)
        __test_signal_ready()
        return
    }
    __log_marker('alex_library_25_parts')

    __test_alexandria_library_finish(bid)
    __test_process_events()
    __test_pump_frames(2)

    var ph = __test_monument_phase(bid)
    if (ph != 255 && ph != -1) {
        __log_info_native('[test:121] not finished after finish helper ph=' + ph)
        __test_signal_ready()
        return
    }
    __log_marker('alex_library_finished_ok')

    test_monument_slots([BUILDING_ALEXANDRIA_LIBRARY])
    city_update_monthly_monument_rating({})
    var rating_done = city.rating.monument | 0
    // OG weight 12 → trunc(6.32*sqrt(12)+0.5)=22
    if (rating_done < 22) {
        __log_info_native('[test:121] finished rating want >=22 got ' + rating_done)
        __log_marker('alex_library_rating_fail:' + rating_done)
        __test_signal_ready()
        return
    }
    __log_marker('alex_library_rating_ok:' + rating_done)

    __log_info_native('[test:121] PASS')
    __log_marker('alex_library_ok')
    __test_signal_ready()
}

function check_valid() {
    var required = [
        'alex_library_placed_ok',
        'alex_library_reject_second_ok',
        'alex_library_25_parts',
        'alex_library_finished_ok',
        'alex_library_rating_ok',
        'alex_library_ok'
    ]
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + required[i])
            && !__test_find_inlog(required[i])) {
            __log_info_native('[test:121] missing marker ' + required[i])
            return false
        }
    }
    return true
}
