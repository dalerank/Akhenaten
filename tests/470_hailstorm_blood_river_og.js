// EVENT_TYPE_HAILSTORM and EVENT_TYPE_BLOOD_RIVER vs OG disaster_events.c:98-114 and
// city_disasters.c city_hailstorm_start / city_blood_river_start:
//   hailstorm: each figure dies on a roll <= 25/50/75, every house loses 15 happiness;
//   blood river: house water supply capped by distance to water * 3, happiness -15,
//   a sweep of clamp(amount, 3, 9) * 816 ticks that blocks water coverage.
// Markers:
//   [test-marker] hailstorm_og_ok
//   [test-marker] blood_river_og_ok

function test470_fail(msg) {
    __log_info_native('[test:470] FAIL: ' + msg)
}

function test470_house() {
    var hid = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, -1, -1)
    if (hid) {
        __test_house_set_population(hid, 10)
    }
    return hid
}

function test470_hailstorm() {
    test_reload_city_session('data/default.map')
    var hid = test470_house()
    if (!hid) {
        test470_fail('no house')
        return
    }
    __test_house_set_happiness(hid, 50)
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var ids = []
    for (var i = 0; i < 24; i++) {
        var fid = __test_figure_create(FIGURE_HYENA, cx, cy)
        if (fid) {
            ids.push(fid)
        }
    }
    if (ids.length < 20) {
        test470_fail('created only ' + ids.length + ' figures')
        return
    }

    var ev = city.create_chain_event({ tag_id: 47001, type: EVENT_TYPE_HAILSTORM, amount: 1, trigger: EVENT_TRIGGER_ONCE })
    ev.execute()

    var alive = 0
    for (var j = 0; j < ids.length; j++) {
        if (__test_figure_is_alive(ids[j])) {
            alive++
        }
    }
    var happiness = __test_house_happiness(hid)
    if (alive >= ids.length || alive == 0 || happiness != 35) {
        test470_fail('hailstorm: alive=' + alive + '/' + ids.length + ' happiness=' + happiness + ' (want 35)')
        return
    }
    __log_marker('hailstorm_og_ok')
}

function test470_blood_river() {
    test_reload_city_session('data/default.map')
    var hid = test470_house()
    if (!hid) {
        test470_fail('no house')
        return
    }
    __test_house_set_happiness(hid, 50)
    __test_house_set_water_supply(hid, 255)

    var ev = city.create_chain_event({ tag_id: 47002, type: EVENT_TYPE_BLOOD_RIVER, amount: 1, trigger: EVENT_TRIGGER_ONCE })
    ev.execute()
    var id = __test_event_id_by_tag(47002)
    var sweep = __test_event_sweep_countdown(id)
    var water = __test_house_water_supply(hid)
    var happiness = __test_house_happiness(hid)
    // amount 1 is raised to the OG minimum of 3.
    __log_info_native('[test:470] blood river water supply ' + water)
    if (sweep != 3 * 816 || !__test_blood_river_sweep_active() || water > 255 || happiness != 35) {
        test470_fail('blood river start: sweep=' + sweep + ' active=' + __test_blood_river_sweep_active()
            + ' water=' + water + ' happiness=' + happiness)
        return
    }

    __test_scenario_events_tick(3 * 816 - 1)
    if (!__test_blood_river_sweep_active()) {
        test470_fail('sweep ended early')
        return
    }
    __test_scenario_events_tick(1)
    if (__test_blood_river_sweep_active() || __test_event_sweep_countdown(id) != 0) {
        test470_fail('sweep did not end: ' + __test_event_sweep_countdown(id))
        return
    }
    __log_marker('blood_river_og_ok')
}

function run_test() {
    __log_info_native('[test:470] OG hailstorm and blood river')
    test470_hailstorm()
    test470_blood_river()
    __test_signal_ready()
}

function check_valid() {
    var markers = ['hailstorm_og_ok', 'blood_river_og_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:470] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}
