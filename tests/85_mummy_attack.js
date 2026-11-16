// FIGURE_MUMMY register + enemy flag; EVENT_TYPE_MUMMY posts 1× msg 496 even with no source building (OG
// city_mummies_start returns early); a mummy from a temple is a soldier target and can be killed.
// The OG source/rise rules: test 552.
// Markers:
//   [test-marker] mummy_registered_ok
//   [test-marker] mummy_event_no_source_ok
//   [test-marker] mummy_soldier_target_ok
//   [test-marker] mummy_soldier_kill_ok

var MESSAGE_MUMMY_ATTACKS = 496

function count_messages_with_id(mm_id) {
    var n = 0
    var total = __city_message_count()
    for (var i = 0; i < total; i++) {
        if (__city_message_mm_text_id(i) == mm_id) {
            n++
        }
    }
    return n
}

function kill_all_mummies() {
    for (var i = 1; i < 2000; i++) {
        if (__figure_is_valid(i) && __figure_get_type(i) == FIGURE_MUMMY) {
            __test_figure_kill(i)
        }
    }
}

function test85_fail(msg) {
    __log_info_native('[test:85] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:85] mummy event + soldier kill')
    test_reload_city_session('data/default.map')

    var probe = test_figure_create(FIGURE_MUMMY, -1, -1)
    if (!probe || !__figure_is_valid(probe) || __figure_get_type(probe) != FIGURE_MUMMY) {
        return test85_fail('FIGURE_MUMMY not registered')
    }
    if (!__test_figure_is_enemy(probe)) {
        return test85_fail('mummy should be is_enemy for soldier targeting')
    }
    __test_figure_kill(probe)
    __log_marker('mummy_registered_ok')
    city.figures.remove_figures(FIGURE_MUMMY)

    var before = count_messages_with_id(MESSAGE_MUMMY_ATTACKS)
    city.create_chain_event({ tag_id: 8501, type: EVENT_TYPE_MUMMY, amount: 2, trigger: EVENT_TRIGGER_ONCE }).execute()
    __test_process_events()
    if (__test_count_figures(FIGURE_MUMMY) != 0 || count_messages_with_id(MESSAGE_MUMMY_ATTACKS) != before + 1) {
        return test85_fail('no source: mummies=' + __test_count_figures(FIGURE_MUMMY)
            + ' messages=' + (count_messages_with_id(MESSAGE_MUMMY_ATTACKS) - before))
    }
    __log_marker('mummy_event_no_source_ok')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    __scenario_building_allow(BUILDING_TEMPLE_RA, true)
    __test_set_treasury(500000)
    var temple = test_building_place(BUILDING_TEMPLE_RA, cx, cy)
    if (!temple) {
        temple = __test_building_create(BUILDING_TEMPLE_RA, cx, cy)
    }
    if (!temple) {
        return test85_fail('no temple')
    }
    var tt = __building_tile(temple)
    for (var i = -3; i <= 6; i++) {
        __test_make_road(tt.x - 1, tt.y + i)
    }
    __test_building_set_road_access(temple, tt.x - 1, tt.y)
    __test_map_routing_update_land()
    var fid = __test_mummy_start_plague(1)
    if (!fid || !__figure_is_valid(fid)) {
        return test85_fail('start_plague from temple failed')
    }
    var tile = __figure_get_tile(fid)
    var target = __test_soldier_combat_target(tile.x, tile.y, 12)
    if (!target || __figure_get_type(target) != FIGURE_MUMMY) {
        return test85_fail('soldier combat target want mummy, got ' + target)
    }
    __log_marker('mummy_soldier_target_ok')

    kill_all_mummies()
    if (__test_count_figures(FIGURE_MUMMY) != 0) {
        return test85_fail('after kill, want 0 live mummies, got ' + __test_count_figures(FIGURE_MUMMY))
    }
    __log_marker('mummy_soldier_kill_ok')

    __test_signal_ready()
}

function check_valid() {
    var markers = ['mummy_registered_ok', 'mummy_event_no_source_ok', 'mummy_soldier_target_ok', 'mummy_soldier_kill_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:85] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}
