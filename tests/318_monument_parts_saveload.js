// Pyramid and mastaba parts used to write more than their building record holds: the record header overwrote
// the tail of each part (subtype, worker, ramp heights). Every saved block-engine field of every part must
// survive save/load, and no building record may overflow (the runner fails on [record-overflow]).
// Note: game load truncates akhenaten-log.txt, so markers are written after the load.
// Markers:
//   [test-marker] monument_parts_saveload_ok:<parts>

var test318_cases = [
    { type: BUILDING_SMALL_STEPPED_PYRAMID, name: 'stepped' },
    { type: BUILDING_SMALL_MASTABA, name: 'mastaba' }
]

function test318_fail(msg) {
    __log_info_native('[test:318] FAIL: ' + msg)
}

function test318_place(type, cx, cy) {
    if (!__scenario_building_allowed(type)) {
        __scenario_building_allow(type, true)
    }
    var candidates = [{ x: cx, y: cy }, { x: cx - 4, y: cy - 4 }, { x: 40, y: 40 }, { x: 30, y: 30 }]
    for (var i = 0; i < candidates.length; i++) {
        var bid = test_building_place(type, candidates[i].x, candidates[i].y)
        if (bid) {
            return bid
        }
    }
    return 0
}

function test318_states(heads) {
    var out = {}
    for (var h = 0; h < heads.length; h++) {
        var ids = __test_monument_parts(heads[h]).split(',')
        for (var i = 0; i < ids.length; i++) {
            out[ids[i]] = __test_monument_part_state(+ids[i])
        }
    }
    return out
}

function run_test() {
    __log_info_native('[test:318] monument parts saveload')
    test_reload_city_session('data/default.map')
    __test_set_treasury(500000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var heads = []
    for (var c = 0; c < test318_cases.length; c++) {
        var bid = test318_place(test318_cases[c].type, cx - 14 + c * 14, cy)
        if (!bid) {
            test318_fail('could not place ' + test318_cases[c].name)
            __test_signal_ready()
            return
        }
        __test_monument_set_phase(bid, 2)
        __pyramid_start_block_phase(bid)
        new Monument(bid).boost_engine_blocks(3)
        var ids = __test_monument_parts(bid).split(',')
        for (var i = 0; i < ids.length; i++) {
            __test_monument_part_fill(+ids[i], i + c * 50 + 1)
        }
        heads.push(bid)
    }

    var before = test318_states(heads)
    var save_name = 'test_318_monument_parts.svx'
    if (!__game_write_savegame(save_name) || !__game_load_savegame(save_name)) {
        __game_delete_savegame(save_name)
        test318_fail('save/load failed')
        __test_signal_ready()
        return
    }
    var after = test318_states(heads)
    // Writes again after the load so an overflow on write lands in this test's log.
    __game_write_savegame(save_name)
    __game_delete_savegame(save_name)

    var count = 0
    var bad = []
    for (var id in before) {
        count++
        if (before[id] !== after[id]) {
            bad.push(id + ': ' + before[id] + ' -> ' + after[id])
        }
    }
    if (bad.length == 0 && count > 2) {
        __log_marker('monument_parts_saveload_ok:' + count)
    } else {
        test318_fail(count + ' parts, changed: ' + bad.slice(0, 6).join(' | '))
    }
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('monument_parts_saveload_ok:')
}
