// OG royal tomb lamps (royal_tomb_check_work_for_figure, laborer sled_to_tomb): the stock starts
// at 0, laborers are asked while it is below 400 and the main chamber has no worker, every guild
// worker sent costs 100 lamps, and an empty tomb with nobody working is idle (dark chambers).

function t150_fail(msg) {
    __log_info_native('[test:150] ' + msg)
    __log_marker('rt_lamp_fail')
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:150] royal tomb lamp stock')
    test_reload_city_session('data/default.map')
    if (!__scenario_building_allowed(BUILDING_SMALL_ROYAL_TOMB)) {
        __scenario_building_allow(BUILDING_SMALL_ROYAL_TOMB, true)
    }

    var cx = 40
    var cy = 40
    __test_royal_tomb_paint_site(BUILDING_SMALL_ROYAL_TOMB, cx, cy)
    var bid = test_building_place(BUILDING_SMALL_ROYAL_TOMB, cx, cy)
    if (!bid) {
        return t150_fail('place failed')
    }

    if (__test_royal_tomb_lamp_stock(bid) != 0 || !__test_royal_tomb_wants_lamps(bid) || !__test_royal_tomb_idle(bid)) {
        return t150_fail('fresh tomb stock=' + __test_royal_tomb_lamp_stock(bid) + ' wants=' + __test_royal_tomb_wants_lamps(bid)
            + ' idle=' + __test_royal_tomb_idle(bid))
    }
    if (__test_royal_tomb_find_work(FIGURE_STONEMASON, -1) != -1) {
        return t150_fail('stonemason sent without lamps')
    }
    __log_marker('rt_lamp_empty_ok')

    // A laborer sled brings 400.
    __test_monument_add_resource(bid, RESOURCE_LAMPS, 400)
    if (__test_royal_tomb_lamp_stock(bid) != 400 || __test_royal_tomb_wants_lamps(bid) || __test_royal_tomb_idle(bid)) {
        return t150_fail('after sled stock=' + __test_royal_tomb_lamp_stock(bid) + ' wants=' + __test_royal_tomb_wants_lamps(bid))
    }
    if (__test_royal_tomb_find_work(FIGURE_STONEMASON, -1) != 0 || __test_royal_tomb_find_work(FIGURE_TOMB_ARTISAN, -1) != -1) {
        return t150_fail('want mason on part 0 only, mason=' + __test_royal_tomb_find_work(FIGURE_STONEMASON, -1)
            + ' artisan=' + __test_royal_tomb_find_work(FIGURE_TOMB_ARTISAN, -1))
    }
    __log_marker('rt_lamp_sled_ok')

    var mason = __test_royal_tomb_attach_worker(bid, FIGURE_STONEMASON)
    if (!mason || __test_royal_tomb_part_worker(bid, 0) != mason) {
        return t150_fail('mason not assigned to part 0')
    }
    if (__test_royal_tomb_lamp_stock(bid) != 300) {
        return t150_fail('dispatch cost want stock 300 got ' + __test_royal_tomb_lamp_stock(bid))
    }
    // OG: the main chamber's worker blocks the lamp request and a second worker.
    if (__test_royal_tomb_wants_lamps(bid) || __test_royal_tomb_find_work(FIGURE_STONEMASON, -1) != -1) {
        return t150_fail('busy main chamber should block lamps and masons')
    }
    __log_marker('rt_lamp_dispatch_cost_ok')

    var ticks = __test_royal_tomb_work(mason, 5000)
    if (ticks != 400 || __test_royal_tomb_part_stage(bid, 0) != 2) {
        return t150_fail('stage 1 work ticks=' + ticks + ' stage=' + __test_royal_tomb_part_stage(bid, 0))
    }
    if (!__test_royal_tomb_wants_lamps(bid)) {
        return t150_fail('stock 300 with no worker should ask for lamps')
    }
    __log_marker('rt_lamp_refill_ask_ok')

    __test_royal_tomb_set_lamp_stock(bid, 99)
    if (__test_royal_tomb_find_work(FIGURE_TOMB_ARTISAN, 2) != -1) {
        return t150_fail('artisan sent with 99 lamps')
    }
    __log_marker('rt_lamp_ok')
    __test_signal_ready()
}

function check_valid() {
    var required = ['rt_lamp_empty_ok', 'rt_lamp_sled_ok', 'rt_lamp_dispatch_cost_ok', 'rt_lamp_refill_ask_ok', 'rt_lamp_ok']
    if (__test_find_inlog('[test-marker] rt_lamp_fail')) {
        return false
    }
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + required[i])) {
            __log_info_native('[test:150] missing marker ' + required[i])
            return false
        }
    }
    return true
}
