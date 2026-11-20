// Mummies vs OG city_disasters.c:331-381 city_mummies_start and plagues.c:182-220 figure_mummy_action:
//   the event posts message 496 and raises one mummy on the road by a random temple / mortuary / pyramid /
//   mausoleum / royal tomb (road within 6 tiles); amount is the cap of mummies, and each victim of a mummy
//   rises as a new mummy on its tile while the cap allows; mummies_max survives a save round trip.
// Markers:
//   [test-marker] mummies_start_at_source_ok
//   [test-marker] mummies_rise_on_victim_ok
//   [test-marker] mummies_cap_ok
//   [test-marker] mummies_saveload_ok

var MESSAGE_MUMMY_ATTACKS = 496

function test416_fail(msg) {
    __log_info_native('[test:416] FAIL: ' + msg)
}

function test416_messages() {
    var n = 0
    var total = __city_message_count()
    for (var i = 0; i < total; i++) {
        if (__city_message_mm_text_id(i) == MESSAGE_MUMMY_ATTACKS) {
            n++
        }
    }
    return n
}

function test416_mummies() {
    var ids = []
    for (var i = 1; i < 2000; i++) {
        if (__figure_is_valid(i) && __figure_get_type(i) == FIGURE_MUMMY) {
            ids.push(i)
        }
    }
    return ids
}

function test416_dist(a, b) {
    var dx = Math.abs(a.x - b.x)
    var dy = Math.abs(a.y - b.y)
    return dx > dy ? dx : dy
}

// The mummy attacks a fresh citizen next to it, the citizen dies, the mummy acts once.
function test416_victim(mummy) {
    var t = __figure_get_tile(mummy)
    var victim = __test_figure_create(FIGURE_IMMIGRANT, t.x, t.y)
    if (!victim || !__test_figure_combat_attack_at(mummy, t.x, t.y)) {
        return null
    }
    __test_figure_kill(victim)
    __test_figure_action_perform(mummy)
    return t
}

function run_test() {
    __log_info_native('[test:416] OG mummies')
    test_reload_city_session('data/default.map')
    __scenario_building_allow(BUILDING_TEMPLE_OSIRIS, true)
    __test_set_treasury(500000)
    city.figures.remove_figures(FIGURE_MUMMY)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var temple = test_building_place(BUILDING_TEMPLE_OSIRIS, cx, cy)
    if (!temple) {
        temple = __test_building_create(BUILDING_TEMPLE_OSIRIS, cx, cy)
    }
    if (!temple) {
        test416_fail('no temple')
        __test_signal_ready()
        return
    }
    var tt = __building_tile(temple)
    var road = { x: tt.x - 1, y: tt.y }
    for (var i = -3; i <= 6; i++) {
        __test_make_road(road.x, road.y + i)
    }
    __test_building_set_road_access(temple, road.x, road.y)
    __test_map_routing_update_land()

    var before = test416_messages()
    city.create_chain_event({ tag_id: 55201, type: EVENT_TYPE_MUMMY, amount: 2, trigger: EVENT_TRIGGER_ONCE }).execute()
    __test_process_events()
    var mummies = test416_mummies()
    if (mummies.length != 1 || __test_plagues_mummies_max() != 2 || test416_messages() != before + 1) {
        test416_fail('start: mummies=' + mummies.length + ' max=' + __test_plagues_mummies_max()
            + ' messages=' + (test416_messages() - before))
        __test_signal_ready()
        return
    }
    var mt = __figure_get_tile(mummies[0])
    if (test416_dist(mt, road) > 6 || !__map_terrain_is(mt, TERRAIN_ROAD)) {
        test416_fail('mummy at ' + mt.x + ',' + mt.y + ' not on the road near the temple')
        __test_signal_ready()
        return
    }
    __log_marker('mummies_start_at_source_ok')

    var vt = test416_victim(mummies[0])
    var after = test416_mummies()
    if (!vt || after.length != 2) {
        test416_fail('rise: victim=' + (vt != null) + ' mummies=' + after.length)
        __test_signal_ready()
        return
    }
    var risen = after[0] == mummies[0] ? after[1] : after[0]
    var rt = __figure_get_tile(risen)
    if (rt.x != vt.x || rt.y != vt.y) {
        test416_fail('risen mummy at ' + rt.x + ',' + rt.y + ' want ' + vt.x + ',' + vt.y)
        __test_signal_ready()
        return
    }
    __log_marker('mummies_rise_on_victim_ok')

    test416_victim(mummies[0])
    if (test416_mummies().length != 2) {
        test416_fail('cap 2: mummies=' + test416_mummies().length)
        __test_signal_ready()
        return
    }
    __log_marker('mummies_cap_ok')

    var save_name = 'test_552_mummies.svx'
    if (__test_save_memory(save_name) && __test_load_memory(save_name) && __test_plagues_mummies_max() == 2) {
        __log_marker('mummies_saveload_ok')
    } else {
        test416_fail('saveload: max=' + __test_plagues_mummies_max())
    }
    __test_drop_memory_save(save_name)
    __test_signal_ready()
}

function check_valid() {
    var markers = ['mummies_start_at_source_ok', 'mummies_rise_on_victim_ok', 'mummies_cap_ok', 'mummies_saveload_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:416] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

function done() {
    city.figures.remove_figures(FIGURE_MUMMY)
}
