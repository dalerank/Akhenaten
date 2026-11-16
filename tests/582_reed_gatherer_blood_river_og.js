// OG figure_reed_gatherer_action: with grown reeds in reach a gatherer heads for them, but while the river of blood
// sweeps a gatherer looking for reeds dies instead.
// Marker: [test-marker] reed_gatherer_blood_river_ok

var __test582_ok = false

function test582_fail(msg) {
    __log_info_native('[test:582] FAIL ' + msg)
    __test_signal_ready()
}

function test582_searching_gatherer(bid, x, y) {
    var fid = test_figure_create(FIGURE_REED_GATHERER, x, y)
    if (fid) {
        test_figure_set_home(fid, bid)
        __test_figure_set_action(fid, 8) // ACTION_8_REED_GATHERER_RECALCULATE
        __test_figure_set_wait_ticks(fid, 10)
    }
    return fid
}

function run_test() {
    __log_info_native('[test:582] reed gatherer during the river of blood')
    test_ensure_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test_building_place(BUILDING_REED_GATHERER, -1, -1)
    if (!bid) {
        bid = __test_building_create(BUILDING_REED_GATHERER, -1, -1)
    }
    if (!bid) {
        return test582_fail('reed gatherer building failed')
    }
    var t = city.get_building(bid).tile
    // Reeds are cut only inside a 3x3 marsh.
    for (var dy = 0; dy < 3; dy++) {
        for (var dx = 4; dx < 7; dx++) {
            terrain.add({ x: t.x + dx, y: t.y + dy }, TERRAIN_MARSHLAND)
            __test_map_set_vegetation_growth(t.x + dx, t.y + dy, 255)
        }
    }
    __test_map_routing_update_land()

    var calm = test582_searching_gatherer(bid, t.x + 2, t.y + 1)
    if (!calm) {
        return test582_fail('create gatherer failed')
    }
    __test_figure_action_perform(calm)
    if (!__test_figure_is_alive(calm) || __test_figure_get_action(calm) != 9) {
        return test582_fail('without the sweep the gatherer should head for the reeds, action=' + __test_figure_get_action(calm))
    }

    if (__test_blood_river_sweep_active()) {
        return test582_fail('sweep active before the event')
    }

    var ev = city.create_chain_event({ tag_id: 58201, type: EVENT_TYPE_BLOOD_RIVER, amount: 1, trigger: EVENT_TRIGGER_ONCE })
    ev.execute()
    if (!__test_blood_river_sweep_active()) {
        return test582_fail('blood river did not start')
    }
    var fid = test582_searching_gatherer(bid, t.x + 2, t.y + 1)
    if (!fid) {
        return test582_fail('create gatherer failed')
    }
    __test_figure_action_perform(fid)
    if (__test_figure_is_alive(fid)) {
        return test582_fail('gatherer kept looking for reeds during the sweep')
    }

    __log_marker('reed_gatherer_blood_river_ok')
    __test582_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test582_ok && __test_find_inlog('[test-marker] reed_gatherer_blood_river_ok')
}
