// Firehouse update_month (JS in firehouse.js):
// 1) A served month bumps months_active / year / total and clears the month count.
// 2) An idle month leaves months_active unchanged and still clears the month count.

var __test198_ok = false

function run_test() {
    __log_info_native('[test:198] firehouse update_month stats')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test_building_place(BUILDING_FIREHOUSE, -1, -1)
    if (!bid) {
        __log_info_native('[test:198] place failed')
        __test_signal_ready()
        return
    }

    var ev = { bid: bid }
    var f = city.get_firehouse(bid)
    if (!f) {
        __log_info_native('[test:198] get_firehouse failed')
        __test_signal_ready()
        return
    }

    var b = city.get_building(bid)
    if (b.overlay != OVERLAY_FIRE) {
        __log_info_native('[test:198] FAIL: overlay=' + b.overlay + ' expected OVERLAY_FIRE=' + OVERLAY_FIRE)
        __test_signal_ready()
        return
    }
    __log_marker('test198_overlay_fire')

    f.buildings_served_this_month = 3
    building_firehouse_update_month(ev)
    f = city.get_firehouse(bid)
    if (f.buildings_served_this_month != 0
        || f.months_active != 1
        || f.buildings_served_this_year != 3
        || f.total_buildings_served != 3) {
        __log_info_native('[test:198] FAIL: served month stats'
            + ' month=' + f.buildings_served_this_month
            + ' active=' + f.months_active
            + ' year=' + f.buildings_served_this_year
            + ' total=' + f.total_buildings_served)
        __test_signal_ready()
        return
    }
    __log_marker('test198_served_month_accumulates')

    building_firehouse_update_month(ev)
    f = city.get_firehouse(bid)
    if (f.months_active != 1
        || f.buildings_served_this_year != 3
        || f.total_buildings_served != 3
        || f.buildings_served_this_month != 0) {
        __log_info_native('[test:198] FAIL: idle month changed stats'
            + ' month=' + f.buildings_served_this_month
            + ' active=' + f.months_active
            + ' year=' + f.buildings_served_this_year
            + ' total=' + f.total_buildings_served)
        __test_signal_ready()
        return
    }
    __log_marker('test198_idle_month_unchanged')

    building_firehouse_update_year(ev)
    f = city.get_firehouse(bid)
    if (f.buildings_served_this_year != 0
        || f.total_buildings_served != 3
        || f.months_active != 1) {
        __log_info_native('[test:198] FAIL: year reset stats'
            + ' year=' + f.buildings_served_this_year
            + ' total=' + f.total_buildings_served
            + ' active=' + f.months_active)
        __test_signal_ready()
        return
    }
    __log_marker('test198_year_resets_served')

    __test198_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test198_ok
        && __test_find_inlog('[test-marker] test198_overlay_fire')
        && __test_find_inlog('[test-marker] test198_served_month_accumulates')
        && __test_find_inlog('[test-marker] test198_idle_month_unchanged')
        && __test_find_inlog('[test-marker] test198_year_resets_served')
}
