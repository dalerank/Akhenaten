// OG style material: true stone pyramid → stone; mudbrick → bricks.

function test283_fail(msg) {
    __log_info_native('[test:283] ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:283] laborer style material by pyramid style')
    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_SMALL_PYRAMID)) {
        __scenario_building_allow(BUILDING_SMALL_PYRAMID, true)
    }
    if (!__scenario_building_allowed(BUILDING_SMALL_MUDBRICK_PYRAMID)) {
        __scenario_building_allow(BUILDING_SMALL_MUDBRICK_PYRAMID, true)
    }

    __test_set_treasury(500000)
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    var stone_bid = 0
    var mud_bid = 0
    var candidates = [
        {x: cx - 8, y: cy - 8}, {x: cx, y: cy}, {x: 40, y: 40}, {x: 30, y: 30}, {x: 50, y: 50}
    ]
    for (var i = 0; i < candidates.length && !stone_bid; i++) {
        stone_bid = test_building_place(BUILDING_SMALL_PYRAMID, candidates[i].x, candidates[i].y)
    }
    for (var j = 0; j < candidates.length && !mud_bid; j++) {
        mud_bid = test_building_place(BUILDING_SMALL_MUDBRICK_PYRAMID, candidates[j].x + 12, candidates[j].y)
    }
    if (!stone_bid || !mud_bid) {
        return test283_fail('place pyramids failed stone=' + stone_bid + ' mud=' + mud_bid)
    }

    var stone_mat = __worker_block_material_for(stone_bid, 0) | 0
    var mud_mat = __worker_block_material_for(mud_bid, 0) | 0
    if (stone_mat != RESOURCE_STONE) {
        return test283_fail('true pyramid want RESOURCE_STONE got ' + stone_mat)
    }
    if (mud_mat != RESOURCE_BRICKS) {
        return test283_fail('mudbrick pyramid want RESOURCE_BRICKS got ' + mud_mat)
    }
    __log_marker('laborer_style_material_ok')
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] laborer_style_material_ok')
}
