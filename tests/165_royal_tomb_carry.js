// C10 RT5: Valley royal tomb monument carry —
// set Small in store → cliff site → apply preexisting + funeral_done.

function find_preexisting_small_royal() {
    for (var i = 1; i < 2000; i++) {
        var b = city.get_building(i)
        if (!b || b.type != BUILDING_SMALL_ROYAL_TOMB) {
            continue
        }
        if (!__test_monument_is_preexisting(i)) {
            continue
        }
        return i
    }
    return 0
}

function paint_cliff_site(cx, cy) {
    __test_royal_tomb_paint_site(BUILDING_SMALL_ROYAL_TOMB, cx, cy)
}

function run_test() {
    __log_info_native('[test:165] royal tomb valley carry')
    test_reload_city_session('data/default.map')
    city.finance.treasury = 50000

    if (!__scenario_building_allowed(BUILDING_SMALL_ROYAL_TOMB)) {
        __scenario_building_allow(BUILDING_SMALL_ROYAL_TOMB, true)
    }

    var cx = 40
    var cy = 40
    paint_cliff_site(cx, cy)

    __campaign_carry_clear()
    // Bad preferred tile (1,1) → cliff scan fallback.
    __campaign_carry_set_monument(0, BUILDING_SMALL_ROYAL_TOMB, 1, 1, 0, 0)
    if (__campaign_carry_monument_type(0) != BUILDING_SMALL_ROYAL_TOMB) {
        __log_info_native('[test:165] set_monument failed')
        __test_signal_ready()
        return
    }
    __log_marker('rt_carry_set_ok')

    __campaign_carry_apply_monuments()
    __test_pump_frames(2)

    var bid = find_preexisting_small_royal()
    if (!bid) {
        __log_info_native('[test:165] apply did not place preexisting small royal')
        __test_signal_ready()
        return
    }
    __log_marker('rt_carry_apply_ok:' + bid)

    if (!__test_monument_funeral_done(bid)) {
        __log_info_native('[test:165] carried tomb should have funeral_done')
        __test_signal_ready()
        return
    }
    __log_marker('rt_carry_funeral_done_ok')

    var ph = __test_monument_phase(bid)
    if (ph != 255 && ph != -1) {
        __log_info_native('[test:165] carried tomb not finished ph=' + ph)
        __test_signal_ready()
        return
    }
    __log_marker('rt_carry_finished_ok')
    __log_marker('rt_carry_all_ok')
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'rt_carry_set_ok',
        'rt_carry_apply_ok',
        'rt_carry_funeral_done_ok',
        'rt_carry_finished_ok',
        'rt_carry_all_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])
            && !__test_find_inlog(markers[i])) {
            __log_info_native('[test:165] missing marker ' + markers[i])
            return false
        }
    }
    return true
}
