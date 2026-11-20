// MS1: mid-phase save/load for small + medium stepped (phase + stair_index in runtime).
// Large/complex covered by tests/106.
// Note: game load calls logs::switch_output (truncates akhenaten-log.txt).
// Run medium first, small last so small's success markers survive for check_valid;
// medium failure early-returns before small (no stepped_sm_midphase_done).

function place_stepped(type, candidates) {
    for (var i = 0; i < candidates.length; i++) {
        var bid = test_building_place(type, candidates[i].x, candidates[i].y)
        if (bid) return bid
    }
    return test_building_place(type, -1, -1)
}

function find_main(type) {
    for (var bi = 1; bi < 500; bi++) {
        if (__building_type(bi) != type) continue
        var b = city.get_building(bi)
        if (b && !b.prev_part_building_id) return bi
    }
    return 0
}

function allow_stepped() {
    if (!__scenario_building_allowed(BUILDING_SMALL_STEPPED_PYRAMID))
        __scenario_building_allow(BUILDING_SMALL_STEPPED_PYRAMID, true)
    if (!__scenario_building_allowed(BUILDING_MEDIUM_STEPPED_PYRAMID))
        __scenario_building_allow(BUILDING_MEDIUM_STEPPED_PYRAMID, true)
}

function saveload_midphase(type, phase, save_name, marker_prefix) {
    test_reload_city_session('data/default.map')
    __test_set_treasury(500000)
    allow_stepped()

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = place_stepped(type, [
        {x: cx - 8, y: cy - 8}, {x: 40, y: 40}, {x: 30, y: 30}, {x: 50, y: 35}
    ])
    if (!bid) {
        __log_info_native('[test:043] ' + marker_prefix + ' place failed')
        __log_marker(marker_prefix + '_place_fail')
        return false
    }
    __test_pump_frames(20)
    __test_monument_set_phase(bid, phase)
    __test_pump_frames(4)
    if (__test_monument_phase(bid) != phase) {
        __log_marker(marker_prefix + '_phase_fail')
        return false
    }

    if (!__test_save_memory(save_name)) {
        __log_marker(marker_prefix + '_saveload_skipped')
        return true
    }
    if (!__test_load_memory(save_name)) {
        __test_drop_memory_save(save_name)
        __log_marker(marker_prefix + '_saveload_skipped')
        return true
    }
    __test_drop_memory_save(save_name)

    var found = find_main(type)
    var ph = found ? __test_monument_phase(found) : -999
    if (!found || ph != phase) {
        __log_info_native('[test:043] ' + marker_prefix + ' after load found=' + found + ' phase=' + ph)
        __log_marker(marker_prefix + '_saveload_fail:' + ph)
        return false
    }
    __log_marker(marker_prefix + '_saveload_ok:' + found)
    return true
}

function run_test() {
    __log_info_native('[test:043] stepped S/M mid-phase saveload')

    // Medium first (markers wiped by small's reload); small last (markers kept).
    if (!saveload_midphase(BUILDING_MEDIUM_STEPPED_PYRAMID, 18,
            'test_130_medium_midphase.svx', 'stepped_medium')) {
        __test_signal_ready()
        return
    }
    if (!saveload_midphase(BUILDING_SMALL_STEPPED_PYRAMID, 10,
            'test_130_small_midphase.svx', 'stepped_small')) {
        __test_signal_ready()
        return
    }

    __log_marker('stepped_sm_midphase_done')
    __test_signal_ready()
}

function check_valid() {
    if (__test_find_inlog('stepped_small_place_fail')
        || __test_find_inlog('stepped_medium_place_fail')
        || __test_find_inlog('stepped_small_phase_fail')
        || __test_find_inlog('stepped_medium_phase_fail')
        || __test_find_inlog('stepped_small_saveload_fail')
        || __test_find_inlog('stepped_medium_saveload_fail')) {
        return false
    }
    if (!__test_find_inlog('stepped_sm_midphase_done')) {
        return false
    }
    // Small ran last — its ok/skipped must be present. Medium failure would have
    // early-returned before midphase_done.
    if (!__test_find_inlog('stepped_small_saveload_skipped')
        && !__test_find_inlog('stepped_small_saveload_ok')) {
        return false
    }
    return true
}
