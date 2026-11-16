// C10 RT2: Small royal tomb — reject clear land; place the OG part layout on Valley cliff;
// finish → monument rating (OG weight 4 → trunc(6.32*sqrt(4)+0.5)=13).

function run_test() {
    __log_info_native('[test:141] small royal tomb cliff place + finish rating')
    test_reload_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_SMALL_ROYAL_TOMB)) {
        __scenario_building_allow(BUILDING_SMALL_ROYAL_TOMB, true)
    }

    __test_set_treasury(500000)

    var cx = 40
    var cy = 40

    // OG Valley cliff: rock + rock-near-monument under the parts, clear land at the entrance.
    function paint_cliff_site(ox, oy) {
        __test_royal_tomb_paint_site(BUILDING_SMALL_ROYAL_TOMB, ox, oy)
    }

    var rejected = test_building_place(BUILDING_SMALL_ROYAL_TOMB, cx, cy)
    if (rejected) {
        __log_info_native('[test:141] unexpected place without cliffs bid=' + rejected)
        __test_signal_ready()
        return
    }
    __log_marker('royal_tomb_reject_no_cliff_ok')

    paint_cliff_site(cx, cy)
    __log_marker('royal_tomb_cliff_painted')

    var bid = test_building_place(BUILDING_SMALL_ROYAL_TOMB, cx, cy)
    if (!bid) {
        __log_info_native('[test:141] failed to place BUILDING_SMALL_ROYAL_TOMB on cliffs')
        __test_signal_ready()
        return
    }

    __test_process_events()
    __test_pump_frames(2)

    var b = city.get_building(bid)
    if (!b || b.type != BUILDING_SMALL_ROYAL_TOMB) {
        __log_info_native('[test:141] placed building type mismatch')
        __test_signal_ready()
        return
    }
    __log_marker('royal_tomb_placed_ok:' + bid)

    paint_cliff_site(cx + 30, cy)
    var second = test_building_place(BUILDING_SMALL_ROYAL_TOMB, cx + 30, cy)
    if (second) {
        __log_info_native('[test:141] unexpected second unfinished place bid=' + second)
        __test_signal_ready()
        return
    }
    __log_marker('royal_tomb_reject_second_ok')

    var mon = city.get_monument(bid)
    if (!mon) {
        __log_info_native('[test:141] city.get_monument failed')
        __test_signal_ready()
        return
    }
    var total = mon.phases_total()
    if (total < 2) {
        __log_info_native('[test:141] phases_total=' + total + ' want >=2')
        __test_signal_ready()
        return
    }
    __log_marker('royal_tomb_schedule_ok:' + total)

    // set_phase(phases_total) → FINISHED
    __test_monument_set_phase(bid, total)
    __test_process_events()
    __test_pump_frames(2)

    var ph = __test_monument_phase(bid)
    if (ph != 255 && ph != -1) {
        __log_info_native('[test:141] not finished after set_phase(' + total + ') ph=' + ph)
        __test_signal_ready()
        return
    }
    __log_marker('royal_tomb_finished_ok')

    test_monument_slots([BUILDING_SMALL_ROYAL_TOMB])
    city_update_monthly_monument_rating({})
    var rating_done = city.rating.monument | 0
    // weight 4 → trunc(13)
    if (rating_done < 13) {
        __log_info_native('[test:141] finished rating want >=13 got ' + rating_done)
        __log_marker('royal_tomb_rating_fail:' + rating_done)
        __test_signal_ready()
        return
    }
    __log_marker('royal_tomb_rating_ok:' + rating_done)
    __log_marker('royal_tomb_ok')
    __test_signal_ready()
}

function check_valid() {
    var required = [
        'royal_tomb_reject_no_cliff_ok',
        'royal_tomb_placed_ok',
        'royal_tomb_reject_second_ok',
        'royal_tomb_schedule_ok',
        'royal_tomb_finished_ok',
        'royal_tomb_rating_ok',
        'royal_tomb_ok'
    ]
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + required[i])
            && !__test_find_inlog(required[i])) {
            __log_info_native('[test:141] missing marker ' + required[i])
            return false
        }
    }
    return true
}
