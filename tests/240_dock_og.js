// BUILDING_DOCK: native Dock proto, trade_ship_moored, workers→play_animation,
// wait/work ambient switch (OG draw_dock_anim).
// Markers:
//   [test-marker] dock_og_proto_ok
//   [test-marker] dock_og_moored_ok
//   [test-marker] dock_og_anim_workers_ok
//   [test-marker] dock_og_anim_wait_work_ok

var __test240_ok = false

function test240_fail(msg) {
    __log_info_native('[test:240] ' + msg)
    __test_signal_ready()
}

function test240_anim_kind(key) {
    if (!key) {
        return ''
    }
    if (key.indexOf('wait') == 0) {
        return 'wait'
    }
    if (key.indexOf('work') == 0) {
        return 'work'
    }
    if (key == 'none') {
        return 'none'
    }
    return key
}

function run_test() {
    __log_info_native('[test:240] dock og proto / moored / ambient')
    test_ensure_city_session('data/default.map')
    __test_set_treasury(500000)

    if (!__scenario_building_allowed(BUILDING_DOCK)) {
        __scenario_building_allow(BUILDING_DOCK, true)
    }

    var bid = __test_building_create(BUILDING_DOCK, -1, -1)
    if (!bid) {
        return test240_fail('dock create failed')
    }

    var dock = city.get_dock(bid)
    if (!dock) {
        return test240_fail('get_dock failed')
    }
    if (('' + dock).indexOf('Dock') < 0) {
        return test240_fail('toString want Dock(...), got ' + dock)
    }
    if (city.get_dock(0) != null) {
        return test240_fail('get_dock(0) should be null')
    }
    __log_marker('dock_og_proto_ok')

    if (dock.trade_ship || dock.has_trade_ship() || dock.trade_ship_moored()) {
        return test240_fail('fresh dock should have no trade ship')
    }

    var ship = test_figure_create(FIGURE_TRADE_SHIP)
    if (!ship) {
        return test240_fail('trade ship create failed')
    }
    dock.trade_ship = ship
    if (!dock.has_trade_ship() || dock.trade_ship != ship) {
        return test240_fail('trade_ship assign failed got ' + dock.trade_ship)
    }

    __test_figure_set_action(ship, ACTION_112_TRADE_SHIP_MOORED)
    dock = city.get_dock(bid)
    if (!dock.trade_ship_moored()) {
        return test240_fail('moored ship should report trade_ship_moored')
    }

    __test_figure_set_action(ship, ACTION_115_TRADE_SHIP_LEAVING)
    dock = city.get_dock(bid)
    if (dock.trade_ship_moored()) {
        return test240_fail('leaving ship must not be moored')
    }
    __log_marker('dock_og_moored_ok')

    var ev = { bid: bid }
    __test_building_set_workers(bid, 0)
    dock = city.get_dock(bid)
    dock.play_animation = true
    building_dock_on_update_animation(ev)
    dock = city.get_dock(bid)
    if (dock.play_animation) {
        return test240_fail('0 workers should clear play_animation')
    }

    __test_building_set_workers(bid, 12)
    dock = city.get_dock(bid)
    dock.play_animation = false
    building_dock_on_update_animation(ev)
    dock = city.get_dock(bid)
    if (!dock.play_animation) {
        return test240_fail('staffed dock should set play_animation')
    }
    __log_marker('dock_og_anim_workers_ok')

    // Ambient: no moored ship → wait_*; moored → work_*
    __test_figure_set_action(ship, ACTION_111_TRADE_SHIP_GOING_TO_DOCK)
    dock = city.get_dock(bid)
    building_dock_on_update_graphic(ev)
    var wait_key = __test_building_anim_key(bid)
    if (test240_anim_kind(wait_key) != 'wait') {
        return test240_fail('unmoored ambient want wait_*, got ' + wait_key)
    }

    __test_figure_set_action(ship, ACTION_112_TRADE_SHIP_MOORED)
    dock = city.get_dock(bid)
    building_dock_on_update_graphic(ev)
    var work_key = __test_building_anim_key(bid)
    if (test240_anim_kind(work_key) != 'work') {
        return test240_fail('moored ambient want work_*, got ' + work_key)
    }
    __log_marker('dock_og_anim_wait_work_ok')

    __test240_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test240_ok
        && __test_find_inlog('[test-marker] dock_og_proto_ok')
        && __test_find_inlog('[test-marker] dock_og_moored_ok')
        && __test_find_inlog('[test-marker] dock_og_anim_workers_ok')
        && __test_find_inlog('[test-marker] dock_og_anim_wait_work_ok')
}
