// Fleet advisor (OG advisors_fleet.c): OG advisor numbering (advisors.h), the portrait strip
// skipping the fleet slot, the fleet window opening, and the per-warship kingdom-service
// toggle refusing service while no troop request waits (OG default: not in service).
// Markers:
//   [test-marker] fleet_advisor_numbering_ok
//   [test-marker] fleet_advisor_window_ok
//   [test-marker] fleet_advisor_service_ok

function test489_fail(msg) {
    __log_info_native('[test:489] ' + msg)
    __test_signal_ready()
}

function test489_check_numbering() {
    var expected = [
        ['ADVISOR_NONE', ADVISOR_NONE, 0], ['ADVISOR_LABOR', ADVISOR_LABOR, 1],
        ['ADVISOR_MILITARY', ADVISOR_MILITARY, 2], ['ADVISOR_FLEET', ADVISOR_FLEET, 3],
        ['ADVISOR_KINGDOM', ADVISOR_KINGDOM, 4], ['ADVISOR_RATINGS', ADVISOR_RATINGS, 5],
        ['ADVISOR_TRADE', ADVISOR_TRADE, 6], ['ADVISOR_POPULATION', ADVISOR_POPULATION, 7],
        ['ADVISOR_HEALTH', ADVISOR_HEALTH, 8], ['ADVISOR_EDUCATION', ADVISOR_EDUCATION, 9],
        ['ADVISOR_ENTERTAINMENT', ADVISOR_ENTERTAINMENT, 10], ['ADVISOR_RELIGION', ADVISOR_RELIGION, 11],
        ['ADVISOR_FINANCIAL', ADVISOR_FINANCIAL, 12], ['ADVISOR_CHIEF', ADVISOR_CHIEF, 13],
        ['ADVISOR_MONUMENTS', ADVISOR_MONUMENTS, 14]
    ]
    for (var i = 0; i < expected.length; i++) {
        if (expected[i][1] !== expected[i][2]) {
            return expected[i][0] + '=' + expected[i][1] + ' expected ' + expected[i][2]
        }
    }
    if (!(ADVISOR_WATER > ADVISOR_MONUMENTS)) {
        return 'remake-only advisors must follow ADVISOR_MONUMENTS'
    }
    for (var adv = ADVISOR_LABOR; adv <= ADVISOR_MONUMENTS; adv++) {
        var found = false
        for (var j = 0; j < advisor_portraits.length; j++) {
            if (advisor_portraits[j].advisor == adv) {
                found = true
            }
        }
        if (!found) {
            return 'advisor ' + adv + ' has no portrait in advisor_portraits'
        }
    }
    return ''
}

function run_test() {
    __log_info_native('[test:489] fleet advisor og')

    var err = test489_check_numbering()
    if (err) {
        return test489_fail(err)
    }
    __log_marker('fleet_advisor_numbering_ok')

    test_ensure_city_session('data/default.map')
    city.set_advisor_available(ADVISOR_MILITARY, 1)
    city.set_advisor_available(ADVISOR_FLEET, 1)
    city.figures.remove_figures(FIGURE_WARSHIP)

    if (!window_advisors_show_advisor(ADVISOR_FLEET)) {
        return test489_fail('fleet advisor did not open')
    }
    __test_pump_frames(5)
    if (!ui.window_is('advisor_fleet_window') || game.last_advisor !== ADVISOR_FLEET) {
        return test489_fail('fleet window not current, last_advisor=' + game.last_advisor)
    }
    if (__fleet_total_warships() !== 0 || __fleet_any_in_service()) {
        return test489_fail('expected an empty navy, warships=' + __fleet_total_warships())
    }
    __log_marker('fleet_advisor_window_ok')

    var ship = __test_figure_create(FIGURE_WARSHIP, 10, 10)
    if (!ship) {
        ui.window_city_show()
        return test489_fail('warship create failed')
    }
    __test_pump_frames(2)
    var ok = __fleet_total_warships() === 1
        && __fleet_ship_id(1) === ship
        && __fleet_ship_free(1)
        && !__fleet_ship_in_service(1)
        && !__fleet_requested_by_sea()
    if (!ok) {
        city.figures.remove_figures(FIGURE_WARSHIP)
        ui.window_city_show()
        return test489_fail('warship row mismatch id=' + __fleet_ship_id(1) + ' free=' + __fleet_ship_free(1)
            + ' in_service=' + __fleet_ship_in_service(1))
    }
    // No request waits: OG refuses the toggle and shows "No troops needed" (popup 40).
    var popup = __fleet_ship_toggle_service(1)
    if (popup !== 40 || __fleet_ship_in_service(1) || __fleet_dispatch_now() !== 0) {
        city.figures.remove_figures(FIGURE_WARSHIP)
        ui.window_city_show()
        return test489_fail('service toggle popup=' + popup + ' in_service=' + __fleet_ship_in_service(1))
    }
    __log_marker('fleet_advisor_service_ok')

    city.figures.remove_figures(FIGURE_WARSHIP)
    ui.window_city_show()
    __test_pump_frames(2)
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        '[test-marker] fleet_advisor_numbering_ok',
        '[test-marker] fleet_advisor_window_ok',
        '[test-marker] fleet_advisor_service_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog(markers[i])) {
            __log_info_native('[test:489] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}
